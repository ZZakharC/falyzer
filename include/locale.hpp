/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#pragma once

#include <string>
#include <algorithm>
#include <clocale>

struct Locale {
    std::string usage_text,
                usage,
                for_help,
                help,
                warn_unknown_method,
                warn_unknown_mode,
                warn_lines_method,
                err_folder,
                warn_failed_process,
                no_file_in_folder,
                analysis_in_folder_text,
                total_files_text,
                total_size_files_text,
                total_lines_text,
                table_header, table_header_lines_text;
};

extern Locale en_locale, // Английский
              fr_locale, // Француский
              de_locale, // Немецкий
              es_locale, // Испанский
              ru_locale; // Русский

extern Locale *locale;   // Текущая локаль

// Установка языка l = локаль (есть auto)
void set_lang(std::string l);