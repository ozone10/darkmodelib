// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work from the win32-darkmode project:
 *  https://github.com/ysc3839/win32-darkmode
 *  which is covered by the MIT License.
 *  See LICENSE-win32-darkmode for more information.
 */


#include "StdAfx.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

extern bool g_darkModeSupported;
extern bool g_darkModeEnabled;

#include "DarkModeHook.h"

#include "ModuleHelper.h"

#include <uxtheme.h>
#include <vsstyle.h>

#if defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 0)
#include <mutex>
#include <unordered_set>
#endif

#if !defined(_DARKMODELIB_EXTERNAL_IATHOOK)
#include "IatHook.h"
#else
extern PIMAGE_THUNK_DATA FindAddressByName(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, const char* funcName);
extern PIMAGE_THUNK_DATA FindAddressByOrdinal(void* moduleBase, PIMAGE_THUNK_DATA impName, PIMAGE_THUNK_DATA impAddr, uint16_t ordinal);
extern PIMAGE_THUNK_DATA FindIatThunkInModule(void* moduleBase, const char* dllName, const char* funcName);
extern PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, const char* funcName);
extern PIMAGE_THUNK_DATA FindDelayLoadThunkInModule(void* moduleBase, const char* dllName, uint16_t ordinal);
#endif

using fnGetSysColor = auto (WINAPI*)(int nIndex) -> DWORD;

template <typename P>
static auto ReplaceFunction(IMAGE_THUNK_DATA* addr, const P& newFunction) -> P
{
	DWORD oldProtect = 0;
	if (VirtualProtect(addr, sizeof(IMAGE_THUNK_DATA), PAGE_READWRITE, &oldProtect) == FALSE)
	{
		return nullptr;
	}

	const uintptr_t oldFunction = addr->u1.Function;
	addr->u1.Function = reinterpret_cast<uintptr_t>(newFunction);
	VirtualProtect(addr, sizeof(IMAGE_THUNK_DATA), oldProtect, &oldProtect);
	return reinterpret_cast<P>(oldFunction);
}

template <typename T>
struct MyFunc
{
	T m_trueFn = nullptr;
	size_t m_ref = 0;
};

#if defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 0)
using fnOpenNcThemeData = auto (WINAPI*)(HWND hWnd, LPCWSTR pszClassList) -> HTHEME; // ordinal 49
static fnOpenNcThemeData pfOpenNcThemeData = nullptr;

bool LoadOpenNcThemeData(const HMODULE& hUxtheme)
{
	return loadFn(hUxtheme, pfOpenNcThemeData, 49);
}

#if defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 1)
// limit dark scroll bar to specific windows and their children
static std::unordered_set<HWND> g_darkScrollBarWindows;
static std::mutex g_darkScrollBarMutex;

void EnableDarkScrollBarForWindowAndChildren(HWND hWnd)
{
	const std::lock_guard<std::mutex> lock(g_darkScrollBarMutex);
	g_darkScrollBarWindows.insert(hWnd);
}

static bool IsWindowOrParentUsingDarkScrollBar(HWND hWnd)
{
	HWND hRoot = GetAncestor(hWnd, GA_ROOT);

	const std::lock_guard<std::mutex> lock(g_darkScrollBarMutex);
	auto hasElement = [](const auto& container, HWND hWndToCheck) -> bool {
#if (defined(_MSC_VER) && (_MSVC_LANG >= 202002L)) || (__cplusplus >= 202002L)
		return container.contains(hWndToCheck);
#else
		return container.count(hWndToCheck) != 0;
#endif
		};

	if (hasElement(g_darkScrollBarWindows, hWnd))
	{
		return true;
	}
	return (hWnd != hRoot && hasElement(g_darkScrollBarWindows, hRoot));
}
#endif // defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 1)

static HTHEME WINAPI MyOpenNcThemeData(HWND hWnd, LPCWSTR pszClassList)
{
	static constexpr std::wstring_view scrollBarClassName = WC_SCROLLBAR;
	if (scrollBarClassName == pszClassList)
	{
#if defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 1)
		if (IsWindowOrParentUsingDarkScrollBar(hWnd))
#endif
		{
			hWnd = nullptr;
			pszClassList = L"Explorer::ScrollBar";
		}
	}
	return pfOpenNcThemeData(hWnd, pszClassList);
}

void FixDarkScrollBar()
{
	const ModuleHandle moduleComctl(L"comctl32.dll");
	if (moduleComctl.isLoaded())
	{
		auto* addr = FindDelayLoadThunkInModule(moduleComctl.get(), "uxtheme.dll", 49); // OpenNcThemeData
		if (addr != nullptr) // && pfOpenNcThemeData != nullptr) // checked in InitDarkMode
		{
			ReplaceFunction<fnOpenNcThemeData>(addr, MyOpenNcThemeData);
		}
	}
}
#endif // defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 0)

// Hooking GetSysColor for combo box ex' list box and list view's gridlines


static MyFunc<fnGetSysColor> g_myGetSysColor{};

static COLORREF g_clrWindow = RGB(32, 32, 32);
static COLORREF g_clrText = RGB(224, 224, 224);
static COLORREF g_clrTGridlines = RGB(100, 100, 100);

void SetMySysColor(int nIndex, COLORREF clr)
{
	switch (nIndex)
	{
		case COLOR_WINDOW:
		{
			g_clrWindow = clr;
			break;
		}

		case COLOR_WINDOWTEXT:
		{
			g_clrText = clr;
			break;
		}

		case COLOR_BTNFACE:
		{
			g_clrTGridlines = clr;
			break;
		}

		default:
		{
			break;
		}
	}
}

static DWORD WINAPI MyGetSysColor(int nIndex)
{
	if (!g_darkModeEnabled)
	{
		return GetSysColor(nIndex);
	}

	switch (nIndex)
	{
		case COLOR_WINDOW:
		{
			return g_clrWindow;
		}

		case COLOR_WINDOWTEXT:
		{
			return g_clrText;
		}

		case COLOR_BTNFACE:
		{
			return g_clrTGridlines;
		}

		default:
		{
			return GetSysColor(nIndex);
		}
	}
}

bool HookSysColor()
{
	const ModuleHandle moduleComctl(L"comctl32.dll");
	if (!moduleComctl.isLoaded())
	{
		return false;
	}

	if (g_myGetSysColor.m_trueFn == nullptr && g_myGetSysColor.m_ref == 0)
	{
		auto* addr = FindIatThunkInModule(moduleComctl.get(), "user32.dll", "GetSysColor");
		if (addr != nullptr)
		{
			g_myGetSysColor.m_trueFn = ReplaceFunction<fnGetSysColor>(addr, MyGetSysColor);
		}
	}

	if (g_myGetSysColor.m_trueFn != nullptr)
	{
		++g_myGetSysColor.m_ref;
		return true;
	}
	return false;
}

void UnhookSysColor()
{
	const ModuleHandle moduleComctl(L"comctl32.dll");
	if (!moduleComctl.isLoaded())
	{
		return;
	}

	if (g_myGetSysColor.m_ref > 0)
	{
		--g_myGetSysColor.m_ref;

		if (g_myGetSysColor.m_trueFn != nullptr && g_myGetSysColor.m_ref == 0)
		{
			auto* addr = FindIatThunkInModule(moduleComctl.get(), "user32.dll", "GetSysColor");
			if (addr != nullptr)
			{
				ReplaceFunction<fnGetSysColor>(addr, g_myGetSysColor.m_trueFn);
				g_myGetSysColor.m_trueFn = nullptr;
			}
		}
	}
}
