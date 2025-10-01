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
    // Проверка существования файлов в директории
    if (totalFiles == 0)
    {
        std::cout << "В указанной папке нет файлов.\n";
        return;
    }

    // Получения спец цвета для типа файла
    auto getColor = [](const std::string &type) -> std::string
    {
        if (type == "Binary" || type == "Object" || type == "Text" ||
            type == "Image" || type == "Video" || type == "Document" || type == "Archive")
            return "\033[1;36m";
        if (type == "Other")
            return "\033[1;90m";
        return "\033[1;33m";
    };

    auto sortIndicator = [](const falyzer::SortSettings &sortSettings)
    {
        char ch = sortSettings.isBigEnd ? '^' : 'v';
        switch (sortSettings.type)
        {
            case falyzer::SortType::NAME:
                std::cout << "\033[13G";
                break;
            case falyzer::SortType::PERCENT:
                std::cout << "\033[24G";
                break;
            case falyzer::SortType::COUNT:
                std::cout << "\033[37G";
                break;
            case falyzer::SortType::SIZE:
                std::cout << "\033[48G";
                break;
            case falyzer::SortType::LINES:
                std::cout << "\033[61G";
                break;
        }
        std::cout << "\033[1;36m" << ch << "\033[0m\n";
    };

    std::cout << "\n\033[37mАнализ файлов в папке: \033[1;35m" << folder << "\033[0;37m\n";
    std::cout << "Всего файлов в директории: \033[1;34m" << totalFiles << "\033[0;37m\n";
    std::cout << "Общий размер всех файлов: \033[1;34m" << formatSize(totalSize) << "\033[0;37m\n";
    if (countLines) // Включен подсчёт строк
        std::cout << "Всего строк во всех файлах: \033[34m" << totalLines << "\033[0;37m\n";
    std::cout << "\n";

    // Заголовок таблицы
    if (countLines) // Включен подсчёт строк
    {
        std::cout << "╔═════════════╦═════════╦════════════╦════════════╦════════════╗\n";
        std::cout << "║  Тип файла  ║ Процент ║ Количество ║   Размер   ║   Строки   ║"; sortIndicator(sortSettings);
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╬════════════╣\n";
    }
    else
    {
        std::cout << "╔═════════════╦═════════╦════════════╦════════════╗\n";
        std::cout << "║  Тип файла  ║ Процент ║ Количество ║   Размер   ║"; sortIndicator(sortSettings);
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╣\n";
    }

    // Перебор отсортированных данных о файлах
    for (const auto &[type, percent] : sortedCounts)
    {
        // Получения цвета
        std::string color = getColor(type);

        // Тип
        std::cout << "║ " << color << type << "\033[0m\033[14G"
        // Процент
        << " ║\033[34m ";
        if (percent < 0.01) // Если 0,00...
            std::cout << " <0.01";
        else                // Минимум 0.01
            std::cout << std::setw(6) << std::fixed << std::setprecision(2) << percent;
        
        std::cout << "%\033[0m"
        // Количество
        << " ║\033[35m" << std::setw(11) << fileCounts.at(type) << "\033[0m"
        // Размер
        << " ║\033[32m" << std::setw(11) << formatSize(sizeCounts.at(type)) << "\033[0m";
            
        // Вывод строк
        if (countLines) // Включен подсчёт строк
            std::cout << " ║\033[90m" << std::setw(11) << (lineCounts.at(type) + 1) << "\033[0m";
        
        std::cout << " ║\n";

        // Вывод разделителя
        if (separator) // Включен разделитель
            std::cout << "╟─────────────╫─────────╫────────────╫────────────" << (countLines ? "╫────────────╢\n" : "╢\n");
    }

    // Конец таблици
    std::cout << "╚═════════════╩═════════╩════════════╩════════════" << (countLines ? "╩════════════╝\n" : "╝\n");
}