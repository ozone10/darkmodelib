// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */


#pragma once

#include <windows.h>

#include <dwmapi.h>

#include <memory>

namespace dmlib_subclass
{
	/**
	 * @brief Defines control subclass ID values.
	 */
	enum class SubclassID : unsigned char
	{
		button = 42,
		groupbox,
		upDown,
		tabPaint,
		tabUpDown,
		customBorder,
		comboBox,
		comboBoxEx,
		listView,
		header,
		statusBar,
		progressBar,
		staticText,
		windowEraseBg,
		windowCtlColor,
		windowNotify,
		windowMenuBar,
		windowSettingChange,
		taskDlg
	};

	/**
	 * @brief Attaches a typed subclass procedure with custom data to a window.
	 *
	 * If the subclass ID is not already attached, allocates a `T` instance using the given
	 * `param` and stores it as subclass reference data. Ownership is transferred to the system.
	 *
	 * @tparam T            The user-defined data type associated with the subclass.
	 * @tparam Param        Type used to initialize `T`.
	 * @param hWnd          Window handle.
	 * @param subclassProc  Subclass procedure.
	 * @param subID         Identifier for the subclass instance.
	 * @param param         Constructor argument forwarded to `T`.
	 * @return TRUE on success, FALSE on failure, -1 if subclass already set.
	 */
	template <typename T, typename Param>
	inline auto SetSubclass(HWND hWnd, SUBCLASSPROC subclassProc, SubclassID subID, const Param& param) -> int
	{
		const auto subclassID = static_cast<UINT_PTR>(subID);
		if (::GetWindowSubclass(hWnd, subclassProc, subclassID, nullptr) == FALSE)
		{
			auto pData = std::make_unique<T>(param);
			if (::SetWindowSubclass(hWnd, subclassProc, subclassID, reinterpret_cast<DWORD_PTR>(pData.get())) == TRUE)
			{
				pData.release();
				return TRUE;
			}
			return FALSE;
		}
		return -1;
	}

	/**
	 * @brief Attaches a typed subclass procedure with default-constructed data.
	 *
	 * Same logic as the other overload, but constructs `T` using its default constructor.
	 *
	 * @tparam T            The user-defined data type associated with the subclass.
	 * @param hWnd          Window handle.
	 * @param subclassProc  Subclass procedure.
	 * @param subID         Identifier for the subclass instance.
	 * @return TRUE on success, FALSE on failure, -1 if already subclassed.
	 */
	template <typename T>
	inline auto SetSubclass(HWND hWnd, SUBCLASSPROC subclassProc, SubclassID subID) -> int
	{
		const auto subclassID = static_cast<UINT_PTR>(subID);
		if (::GetWindowSubclass(hWnd, subclassProc, subclassID, nullptr) == FALSE)
		{
			auto pData = std::make_unique<T>();
			if (::SetWindowSubclass(hWnd, subclassProc, subclassID, reinterpret_cast<DWORD_PTR>(pData.get())) == TRUE)
			{
				pData.release();
				return TRUE;
			}
			return FALSE;
		}
		return -1;
	}

	/**
	 * @brief Attaches an untyped subclass (no reference data).
	 *
	 * Sets a subclass with no associated custom data.
	 *
	 * @param hWnd          Window handle.
	 * @param subclassProc  Subclass procedure.
	 * @param subID         Identifier for the subclass instance.
	 * @return TRUE on success, FALSE on failure, -1 if already subclassed.
	 */
	inline int SetSubclass(HWND hWnd, SUBCLASSPROC subclassProc, SubclassID subID)
	{
		const auto subclassID = static_cast<UINT_PTR>(subID);
		if (::GetWindowSubclass(hWnd, subclassProc, subclassID, nullptr) == FALSE)
		{
			return ::SetWindowSubclass(hWnd, subclassProc, subclassID, 0);
		}
		return -1;
	}

	/**
	 * @brief Removes a subclass and deletes associated user data (if provided).
	 *
	 * Retrieves and deletes user-defined `T` data stored in subclass reference
	 * (unless `T = void`, in which case no delete is performed). Then removes the subclass.
	 *
	 * @tparam T            Optional type of reference data to delete.
	 * @param hWnd          Window handle.
	 * @param subclassProc  Subclass procedure.
	 * @param subID         Identifier for the subclass instance.
	 * @return TRUE on success, FALSE on failure, -1 if not present.
	 */
	template <typename T = void>
	inline auto RemoveSubclass(HWND hWnd, SUBCLASSPROC subclassProc, SubclassID subID) -> int
	{
		T* pData = nullptr;
		const auto subclassID = static_cast<UINT_PTR>(subID);
		if (::GetWindowSubclass(hWnd, subclassProc, subclassID, reinterpret_cast<DWORD_PTR*>(&pData)) == TRUE)
		{
			if constexpr (!std::is_void_v<T>)
			{
				if (pData != nullptr)
				{
					delete pData;
					pData = nullptr;
				}
			}
			return ::RemoveWindowSubclass(hWnd, subclassProc, subclassID);
		}
		return -1;
	}
} // namespace dmlib_subclass
