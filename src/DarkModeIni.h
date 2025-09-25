// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */


#pragma once

#include <windows.h>

#include <string>

namespace dmlib_ini
{
	[[nodiscard]] std::wstring GetIniPath(const std::wstring& iniFilename);
	[[nodiscard]] bool FileExists(const std::wstring& filePath);
	bool SetClrFromIni(const std::wstring& iniFilePath, const std::wstring& sectionName, const std::wstring& keyName, COLORREF* clr);
} // namespace dmlib_ini
