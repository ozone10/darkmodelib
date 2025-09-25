// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */


#pragma once

#include <windows.h>

#include "DarkModeSubclass.h"

namespace dmlib_color
{
	/// Converts 0xRRGGBB to COLORREF (0xBBGGRR) for GDI usage.
	inline constexpr COLORREF HEXRGB(DWORD rrggbb)
	{
		return
			((rrggbb & 0xFF0000) >> 16) |
			((rrggbb & 0x00FF00)) |
			((rrggbb & 0x0000FF) << 16);
	}

	/// Black tone (default)
	inline constexpr DarkMode::Colors kDarkColors{
		dmlib_color::HEXRGB(0x202020),   // background
		dmlib_color::HEXRGB(0x383838),   // ctrlBackground
		dmlib_color::HEXRGB(0x454545),   // hotBackground
		dmlib_color::HEXRGB(0x202020),   // dlgBackground
		dmlib_color::HEXRGB(0xB00000),   // errorBackground
		dmlib_color::HEXRGB(0xE0E0E0),   // textColor
		dmlib_color::HEXRGB(0xC0C0C0),   // darkerTextColor
		dmlib_color::HEXRGB(0x808080),   // disabledTextColor
		dmlib_color::HEXRGB(0xFFFF00),   // linkTextColor
		dmlib_color::HEXRGB(0x646464),   // edgeColor
		dmlib_color::HEXRGB(0x9B9B9B),   // hotEdgeColor
		dmlib_color::HEXRGB(0x484848)    // disabledEdgeColor
	};

	inline constexpr DWORD kOffsetEdge = dmlib_color::HEXRGB(0x1C1C1C);

	/// Red tone
	inline constexpr DWORD kOffsetRed = dmlib_color::HEXRGB(0x100000);
	inline constexpr DarkMode::Colors kDarkRedColors{
		kDarkColors.background + kOffsetRed,
		kDarkColors.ctrlBackground + kOffsetRed,
		kDarkColors.hotBackground + kOffsetRed,
		kDarkColors.dlgBackground + kOffsetRed,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetRed,
		kDarkColors.hotEdge + kOffsetRed,
		kDarkColors.disabledEdge + kOffsetRed
	};

	/// Green tone
	inline constexpr DWORD kOffsetGreen = dmlib_color::HEXRGB(0x001000);
	inline constexpr DarkMode::Colors kDarkGreenColors{
		kDarkColors.background + kOffsetGreen,
		kDarkColors.ctrlBackground + kOffsetGreen,
		kDarkColors.hotBackground + kOffsetGreen,
		kDarkColors.dlgBackground + kOffsetGreen,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetGreen,
		kDarkColors.hotEdge + kOffsetGreen,
		kDarkColors.disabledEdge + kOffsetGreen
	};

	/// Blue tone
	inline constexpr DWORD kOffsetBlue = dmlib_color::HEXRGB(0x000020);
	inline constexpr DarkMode::Colors kDarkBlueColors{
		kDarkColors.background + kOffsetBlue,
		kDarkColors.ctrlBackground + kOffsetBlue,
		kDarkColors.hotBackground + kOffsetBlue,
		kDarkColors.dlgBackground + kOffsetBlue,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetBlue,
		kDarkColors.hotEdge + kOffsetBlue,
		kDarkColors.disabledEdge + kOffsetBlue
	};

	/// Purple tone
	inline constexpr DWORD kOffsetPurple = dmlib_color::HEXRGB(0x100020);
	inline constexpr DarkMode::Colors kDarkPurpleColors{
		kDarkColors.background + kOffsetPurple,
		kDarkColors.ctrlBackground + kOffsetPurple,
		kDarkColors.hotBackground + kOffsetPurple,
		kDarkColors.dlgBackground + kOffsetPurple,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetPurple,
		kDarkColors.hotEdge + kOffsetPurple,
		kDarkColors.disabledEdge + kOffsetPurple
	};

	/// Cyan tone
	inline constexpr DWORD kOffsetCyan = dmlib_color::HEXRGB(0x001020);
	inline constexpr DarkMode::Colors kDarkCyanColors{
		kDarkColors.background + kOffsetCyan,
		kDarkColors.ctrlBackground + kOffsetCyan,
		kDarkColors.hotBackground + kOffsetCyan,
		kDarkColors.dlgBackground + kOffsetCyan,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetCyan,
		kDarkColors.hotEdge + kOffsetCyan,
		kDarkColors.disabledEdge + kOffsetCyan
	};

	/// Olive tone
	inline constexpr DWORD kOffsetOlive = dmlib_color::HEXRGB(0x101000);
	inline constexpr DarkMode::Colors kDarkOliveColors{
		kDarkColors.background + kOffsetOlive,
		kDarkColors.ctrlBackground + kOffsetOlive,
		kDarkColors.hotBackground + kOffsetOlive,
		kDarkColors.dlgBackground + kOffsetOlive,
		kDarkColors.errorBackground,
		kDarkColors.text,
		kDarkColors.darkerText,
		kDarkColors.disabledText,
		kDarkColors.linkText,
		kDarkColors.edge + kOffsetEdge + kOffsetOlive,
		kDarkColors.hotEdge + kOffsetOlive,
		kDarkColors.disabledEdge + kOffsetOlive
	};

	/// Dark views colors
	inline constexpr DarkMode::ColorsView kDarkColorsView{
		dmlib_color::HEXRGB(0x293134),   // background
		dmlib_color::HEXRGB(0xE0E2E4),   // text
		dmlib_color::HEXRGB(0x646464),   // gridlines
		dmlib_color::HEXRGB(0x202020),   // Header background
		dmlib_color::HEXRGB(0x454545),   // Header hot background
		dmlib_color::HEXRGB(0xC0C0C0),   // header text
		dmlib_color::HEXRGB(0x646464)    // header divider
	};

	/// Light views colors
	inline constexpr DarkMode::ColorsView kLightColorsView{
		dmlib_color::HEXRGB(0xFFFFFF),   // background
		dmlib_color::HEXRGB(0x000000),   // text
		dmlib_color::HEXRGB(0xF0F0F0),   // gridlines
		dmlib_color::HEXRGB(0xFFFFFF),   // header background
		dmlib_color::HEXRGB(0xD9EBF9),   // header hot background
		dmlib_color::HEXRGB(0x000000),   // header text
		dmlib_color::HEXRGB(0xE5E5E5)    // header divider
	};

	DarkMode::Colors getLightColors();

	struct Brushes
	{
		HBRUSH m_background = nullptr;
		HBRUSH m_ctrlBackground = nullptr;
		HBRUSH m_hotBackground = nullptr;
		HBRUSH m_dlgBackground = nullptr;
		HBRUSH m_errorBackground = nullptr;

		HBRUSH m_edge = nullptr;
		HBRUSH m_hotEdge = nullptr;
		HBRUSH m_disabledEdge = nullptr;

		Brushes() = delete;

		explicit Brushes(const DarkMode::Colors& colors) noexcept
			: m_background(::CreateSolidBrush(colors.background))
			, m_ctrlBackground(::CreateSolidBrush(colors.ctrlBackground))
			, m_hotBackground(::CreateSolidBrush(colors.hotBackground))
			, m_dlgBackground(::CreateSolidBrush(colors.dlgBackground))
			, m_errorBackground(::CreateSolidBrush(colors.errorBackground))

			, m_edge(::CreateSolidBrush(colors.edge))
			, m_hotEdge(::CreateSolidBrush(colors.hotEdge))
			, m_disabledEdge(::CreateSolidBrush(colors.disabledEdge))
		{}

		Brushes(const Brushes&) = delete;
		Brushes& operator=(const Brushes&) = delete;

		Brushes(Brushes&&) = delete;
		Brushes& operator=(Brushes&&) = delete;

		~Brushes()
		{
			::DeleteObject(m_background);       m_background = nullptr;
			::DeleteObject(m_ctrlBackground);   m_ctrlBackground = nullptr;
			::DeleteObject(m_hotBackground);    m_hotBackground = nullptr;
			::DeleteObject(m_dlgBackground);    m_dlgBackground = nullptr;
			::DeleteObject(m_errorBackground);  m_errorBackground = nullptr;

			::DeleteObject(m_edge);             m_edge = nullptr;
			::DeleteObject(m_hotEdge);          m_hotEdge = nullptr;
			::DeleteObject(m_disabledEdge);     m_disabledEdge = nullptr;
		}

		void updateBrushes(const DarkMode::Colors& colors) noexcept
		{
			::DeleteObject(m_background);
			::DeleteObject(m_ctrlBackground);
			::DeleteObject(m_hotBackground);
			::DeleteObject(m_dlgBackground);
			::DeleteObject(m_errorBackground);

			::DeleteObject(m_edge);
			::DeleteObject(m_hotEdge);
			::DeleteObject(m_disabledEdge);

			m_background = ::CreateSolidBrush(colors.background);
			m_ctrlBackground = ::CreateSolidBrush(colors.ctrlBackground);
			m_hotBackground = ::CreateSolidBrush(colors.hotBackground);
			m_dlgBackground = ::CreateSolidBrush(colors.dlgBackground);
			m_errorBackground = ::CreateSolidBrush(colors.errorBackground);

			m_edge = ::CreateSolidBrush(colors.edge);
			m_hotEdge = ::CreateSolidBrush(colors.hotEdge);
			m_disabledEdge = ::CreateSolidBrush(colors.disabledEdge);
		}
	};

	struct Pens
	{
		HPEN m_darkerText = nullptr;
		HPEN m_edge = nullptr;
		HPEN m_hotEdge = nullptr;
		HPEN m_disabledEdge = nullptr;

		Pens() = delete;

		explicit Pens(const DarkMode::Colors& colors) noexcept
			: m_darkerText(::CreatePen(PS_SOLID, 1, colors.darkerText))
			, m_edge(::CreatePen(PS_SOLID, 1, colors.edge))
			, m_hotEdge(::CreatePen(PS_SOLID, 1, colors.hotEdge))
			, m_disabledEdge(::CreatePen(PS_SOLID, 1, colors.disabledEdge))
		{}

		Pens(const Pens&) = delete;
		Pens& operator=(const Pens&) = delete;

		Pens(Pens&&) = delete;
		Pens& operator=(Pens&&) = delete;

		~Pens()
		{
			::DeleteObject(m_darkerText);    m_darkerText = nullptr;
			::DeleteObject(m_edge);          m_edge = nullptr;
			::DeleteObject(m_hotEdge);       m_hotEdge = nullptr;
			::DeleteObject(m_disabledEdge);  m_disabledEdge = nullptr;
		}

		void updatePens(const DarkMode::Colors& colors) noexcept
		{
			::DeleteObject(m_darkerText);
			::DeleteObject(m_edge);
			::DeleteObject(m_hotEdge);
			::DeleteObject(m_disabledEdge);

			m_darkerText = ::CreatePen(PS_SOLID, 1, colors.darkerText);
			m_edge = ::CreatePen(PS_SOLID, 1, colors.edge);
			m_hotEdge = ::CreatePen(PS_SOLID, 1, colors.hotEdge);
			m_disabledEdge = ::CreatePen(PS_SOLID, 1, colors.disabledEdge);
		}
	};

	class Theme
	{
	public:
		Theme() noexcept
			: m_colors(kDarkColors)
			, m_brushes(kDarkColors)
			, m_pens(kDarkColors)
		{}

		explicit Theme(const DarkMode::Colors& colors) noexcept
			: m_colors(colors)
			, m_brushes(colors)
			, m_pens(colors)
		{}

		void updateTheme() noexcept
		{
			m_brushes.updateBrushes(m_colors);
			m_pens.updatePens(m_colors);
		}

		void updateTheme(DarkMode::Colors colors) noexcept
		{
			m_colors = colors;
			Theme::updateTheme();
		}

		[[nodiscard]] DarkMode::Colors getToneColors() const noexcept
		{
			switch (m_tone)
			{
				case DarkMode::ColorTone::red:
				{
					return kDarkRedColors;
				}

				case DarkMode::ColorTone::green:
				{
					return kDarkGreenColors;
				}

				case DarkMode::ColorTone::blue:
				{
					return kDarkBlueColors;
				}

				case DarkMode::ColorTone::purple:
				{
					return kDarkPurpleColors;
				}

				case DarkMode::ColorTone::cyan:
				{
					return kDarkCyanColors;
				}

				case DarkMode::ColorTone::olive:
				{
					return kDarkOliveColors;
				}

				case DarkMode::ColorTone::black:
				case DarkMode::ColorTone::max:
				{
					break;
				}
			}
			return kDarkColors;
		}

		void setToneColors(DarkMode::ColorTone colorTone) noexcept
		{
			m_tone = colorTone;

			switch (m_tone)
			{
				case DarkMode::ColorTone::red:
				{
					m_colors = kDarkRedColors;
					break;
				}

				case DarkMode::ColorTone::green:
				{
					m_colors = kDarkGreenColors;
					break;
				}

				case DarkMode::ColorTone::blue:
				{
					m_colors = kDarkBlueColors;
					break;
				}

				case DarkMode::ColorTone::purple:
				{
					m_colors = kDarkPurpleColors;
					break;
				}

				case DarkMode::ColorTone::cyan:
				{
					m_colors = kDarkCyanColors;
					break;
				}

				case DarkMode::ColorTone::olive:
				{
					m_colors = kDarkOliveColors;
					break;
				}

				case DarkMode::ColorTone::black:
				case DarkMode::ColorTone::max:
				{
					m_colors = kDarkColors;
					break;
				}
			}

			Theme::updateTheme();
		}

		void setToneColors() noexcept
		{
			m_colors = Theme::getToneColors();
			Theme::updateTheme();
		}

		[[nodiscard]] const Brushes& getBrushes() const noexcept
		{
			return m_brushes;
		}

		[[nodiscard]] const Pens& getPens() const noexcept
		{
			return m_pens;
		}

		[[nodiscard]] const DarkMode::ColorTone& getColorTone() const noexcept
		{
			return m_tone;
		}

		DarkMode::Colors m_colors;

	private:
		Brushes m_brushes;
		Pens m_pens;
		DarkMode::ColorTone m_tone = DarkMode::ColorTone::black;
	};

	struct BrushesAndPensView
	{
		HBRUSH m_background = nullptr;
		HBRUSH m_gridlines = nullptr;
		HBRUSH m_headerBackground = nullptr;
		HBRUSH m_headerHotBackground = nullptr;

		HPEN m_headerEdge = nullptr;

		BrushesAndPensView() = delete;

		explicit BrushesAndPensView(const DarkMode::ColorsView& colors) noexcept
			: m_background(::CreateSolidBrush(colors.background))
			, m_gridlines(::CreateSolidBrush(colors.gridlines))
			, m_headerBackground(::CreateSolidBrush(colors.headerBackground))
			, m_headerHotBackground(::CreateSolidBrush(colors.headerHotBackground))

			, m_headerEdge(::CreatePen(PS_SOLID, 1, colors.headerEdge))
		{}

		BrushesAndPensView(const BrushesAndPensView&) = delete;
		BrushesAndPensView& operator=(const BrushesAndPensView&) = delete;

		BrushesAndPensView(BrushesAndPensView&&) = delete;
		BrushesAndPensView& operator=(BrushesAndPensView&&) = delete;

		~BrushesAndPensView()
		{
			::DeleteObject(m_background);           m_background = nullptr;
			::DeleteObject(m_gridlines);            m_gridlines = nullptr;
			::DeleteObject(m_headerBackground);     m_headerBackground = nullptr;
			::DeleteObject(m_headerHotBackground);  m_headerHotBackground = nullptr;

			::DeleteObject(m_headerEdge);           m_headerEdge = nullptr;
		}

		void update(const DarkMode::ColorsView& colors) noexcept
		{
			::DeleteObject(m_background);
			::DeleteObject(m_gridlines);
			::DeleteObject(m_headerBackground);
			::DeleteObject(m_headerHotBackground);

			m_background = ::CreateSolidBrush(colors.background);
			m_gridlines = ::CreateSolidBrush(colors.gridlines);
			m_headerBackground = ::CreateSolidBrush(colors.headerBackground);
			m_headerHotBackground = ::CreateSolidBrush(colors.headerHotBackground);

			::DeleteObject(m_headerEdge);

			m_headerEdge = ::CreatePen(PS_SOLID, 1, colors.headerEdge);
		}
	};

	class ThemeView
	{
	public:
		ThemeView() noexcept
			: m_clrView(kDarkColorsView)
			, m_hbrPnView(kDarkColorsView)
		{}

		explicit ThemeView(const DarkMode::ColorsView& colorsView) noexcept
			: m_clrView(colorsView)
			, m_hbrPnView(colorsView)
		{}

		void updateView() noexcept
		{
			m_hbrPnView.update(m_clrView);
		}

		void updateView(DarkMode::ColorsView colors) noexcept
		{
			m_clrView = colors;
			ThemeView::updateView();
		}

		[[nodiscard]] const BrushesAndPensView& getViewBrushesAndPens() const noexcept
		{
			return m_hbrPnView;
		}

		DarkMode::ColorsView m_clrView;

	private:
		BrushesAndPensView m_hbrPnView;
	};

	inline COLORREF setNewColor(COLORREF* clrOld, COLORREF clrNew)
	{
		const auto clrTmp = *clrOld;
		*clrOld = clrNew;
		return clrTmp;
	}

} // namespace dmlib_color
