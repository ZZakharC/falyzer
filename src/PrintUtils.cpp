/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include "../include/PrintUtils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

// Конвертация размера
std::string formatSize(unsigned long long bytes)
{
    // Набор единиц измерения: байты, килобайты, мегабайты, гигабайты, терабайты
    const char *units[] = {"B", "KB", "MB", "GB", "TB"}; 
    
    int i = 0;  
    double size = static_cast<double>(bytes);

    // Пока размер >= 1024 и ещё есть единицы больше
    while (size >= 1024 && i < 4)
    {
        size /= 1024;  // уменьшения размера в 1024 раза
        ++i;           // переход к следующей единице 
    }

    // Форматированный вывод с двумя знаками после запятой
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << size << " " << units[i];

    return out.str();
}

// Вывод анализа файлов в указанной папке в виде таблицы.
void printAnalysis(const std::string &folder, const unsigned long totalFiles,
                   const unsigned long totalLines, const unsigned long long totalSize,
                   const std::vector<std::pair<std::string, double>> &sortedCounts,
                   const std::unordered_map<std::string, int> &fileCounts,
                   const std::unordered_map<std::string, int> &lineCounts,
                   const std::unordered_map<std::string, unsigned long long> &sizeCounts,
                   const falyzer::SortSettings sortSettings,
                   bool countLines, bool separator)
{
    // Получения спец цвета для типа файла
    auto getColor = [](const std::string &type) -> std::string
    {
        if (type == "Binary" || type == "Object" || type == "Text" ||
            type == "Image" || type == "Video" || type == "Document" || type == "Archive")
            return COLOR_CYAN;
        if (type == "Other")
            return COLOR_GRAY;
        return COLOR_YELLOW;
    };

    auto sortIndicator = [](const falyzer::SortSettings &sortSettings)
    {
        // Проверка режима сортировки
        char ch = sortSettings.isBigEnd ? '^' : 'v'; // Индикатор

        // Проверка метода сортировки
        switch (sortSettings.type)
        {
            case falyzer::SortType::NAME:    // Названия типа
                std::cout << "\033[13G";
                break;
            case falyzer::SortType::PERCENT: // Процент
                std::cout << "\033[24G";
                break;
            case falyzer::SortType::COUNT:   // Количество
                std::cout << (locale == &ru_locale ? "\033[37G" : "\033[36G"); // Проверка на локаль из-за разной длины слов
                break;
            case falyzer::SortType::SIZE:   // Размер
                std::cout << (locale == &ru_locale ? "\033[48G" : "\033[47G"); // Проверка на локаль из-за разной длины слов
                break;
            case falyzer::SortType::LINES:  // Строки
                std::cout << "\033[61G";
                break;
        }

        // Вывод индикатора
        std::cout << COLOR_BOLD << COLOR_CYAN << ch << '\n' << COLOR_RESET;
    };

    // Вывод общей информации
    std::cout << '\n'
    /// Папка
              << locale->analysis_in_folder_text << ' ' << COLOR_BOLD << COLOR_MAGENTA << folder << '\n' << COLOR_RESET
    /// Количество файлов
              << locale->total_files_text << ' ' << COLOR_BOLD << COLOR_BLUE << totalFiles << '\n' << COLOR_RESET
    /// Размер файлов
              << locale->total_size_files_text << ' ' << COLOR_BOLD << COLOR_GREEN << formatSize(totalSize) << '\n' << COLOR_RESET;
    /// Строки в файлах
    if (countLines) // Включен подсчёт строк
        std::cout << locale->total_lines_text << ' ' << COLOR_BOLD << COLOR_GRAY << totalLines << '\n' << COLOR_RESET;
    std::cout << "\n";

    // Заголовок таблицы
    if (countLines) // Включен подсчёт строк
    {
        std::cout << "╔═════════════╦═════════╦════════════╦════════════╦════════════╗\n";
        std::cout << locale->table_header << locale->table_header_lines_text; sortIndicator(sortSettings);
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╬════════════╣\n";
    }
    else
    {
        std::cout << "╔═════════════╦═════════╦════════════╦════════════╗\n";
        std::cout << locale->table_header; sortIndicator(sortSettings);
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╣\n";
    }

    // Перебор отсортированных данных о файлах
    for (const auto &[type, percent] : sortedCounts)
    {
        // Получения цвета
        std::string color = getColor(type);
        
        // Вывод
        /// Тип файла
        std::cout << "║ "
                  << COLOR_BOLD << color << type << COLOR_RESET
                  << "\033[14G"

        /// Процент
                  << " ║ " << COLOR_BLUE;
        if (percent < 0.01) // Если меньше 0,01
            std::cout << " <0.01";
        else
            std::cout << std::setw(6)
                      << std::fixed << std::setprecision(2)
                      << percent;
        std::cout << '%' << COLOR_RESET

        /// Количество
                  << " ║" << COLOR_MAGENTA
                  << std::setw(11) << fileCounts.at(type)
                  << COLOR_RESET

        /// Размер
                  << " ║" << COLOR_GREEN
                  << std::setw(11) << formatSize(sizeCounts.at(type))
                  << COLOR_RESET;

        /// Строки (если включено)
        if (countLines)
            std::cout << " ║" << COLOR_GRAY
                      << std::setw(11) << (lineCounts.at(type) + 1)
                      << COLOR_RESET;
                
        /// Закрытия строки
        std::cout << " ║\n";

        // Вывод разделителя
        if (separator) // Включен разделитель
            std::cout << "╟─────────────╫─────────╫────────────╫────────────" << (countLines ? "╫────────────╢\n" : "╢\n");
    }

    // Конец таблици
    std::cout << "╚═════════════╩═════════╩════════════╩════════════" << (countLines ? "╩════════════╝\n" : "╝\n");
}