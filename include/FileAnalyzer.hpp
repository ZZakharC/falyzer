/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace falyzer {
    // Тип сортировки
    enum class SortType
    {
        NAME,    // По имени
        PERCENT, // По % количеста файлов
        COUNT,   // По количество файлов
        SIZE,    // По размеру
        LINES    // По количество строк
    };

    // Структура настроек
    struct SortSettings
    {
        SortType type = SortType::PERCENT; // Тип сортировки
        bool isBigEnd = 0;                 // Начинать сортировку с малого (0 нет 1 да)
    };

    // Структура для хранения итогов по каждому типу файлов
    struct FileStats
    {
        std::string type;
        int count;
        unsigned long long size;
        int lines;
        double percent;
    };
}

/// @brief Сбор аналитики файлов
/// @param folderStr     Путь к папке
/// @param includeHidden Учитывать ли скрытые файлы
/// @param countLines    Подсчитывать ли строки
/// @param separator     Выводить ли разделитель
/// @param logs          Выводить ли логи
/// @param sortSettings  Настройки сортировки
void analyticsFiles(const std::string &folderStr, bool includeHidden, bool countLines, bool separator, bool logs, falyzer::SortSettings sortSettings);
