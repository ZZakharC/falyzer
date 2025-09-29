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
        size /= 1024;  // уменьшаем размер в 1024 раза
        ++i;           // переходим к следующей единице (KB → MB → GB и т.д.)
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
                   bool countLines, bool separator)
{
    // Проверка существования файлов в директории
    if (totalFiles == 0)
    {
        std::cout << "В указанной папке нет файлов.\n";
        return;
    }

    // Получения спец цвета для типа файла
    auto getColor = [](const std::string &type) -> std::string {
        if (type == "Binary" || type == "Object" || type == "Text" ||
            type == "Image" || type == "Video" || type == "Document" || type == "Archive")
            return "\033[1;36m";
        if (type == "Other")
            return "\033[1;90m";
        return "\033[1;33m";
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
        std::cout << "║  Тип файла  ║ Процент ║ Количество ║   Строки   ║   Размер   ║\n";
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╬════════════╣\n";
    }
    else
    {
        std::cout << "╔═════════════╦═════════╦════════════╦════════════╗\n";
        std::cout << "║  Тип файла  ║ Процент ║ Количество ║   Размер   ║\n";
        std::cout << "╠═════════════╬═════════╬════════════╬════════════╣\n";
    }

    // Перебор отсортированных данных о файлах
    for (const auto &[type, percent] : sortedCounts)
    {
        // Получения цвета
        std::string color = getColor(type);
        {
            std::cout << "║ " << color << type << "\033[0;37m "
            << "\033[15G║\033[34m " << std::setw(6) << std::fixed << std::setprecision(2) << percent << "%\033[0m"
            << " ║\033[35m" << std::setw(11) << fileCounts.at(type) << "\033[0m";
            
            if (countLines) // Включен подсчёт строк
                std::cout << " ║\033[90m" << std::setw(11) << (lineCounts.at(type) + 1)<< "\033[0m";
            
            std::cout << " ║" << std::setw(11) << formatSize(sizeCounts.at(type)) << " ║\n";
        }

        if (separator) // Включен разделитель
            std::cout << (countLines ? "╟─────────────╫─────────╫────────────╫────────────╫────────────╢\n"
                                     : "╟─────────────╫─────────╫────────────╫────────────╢\n");
    }

    // Конец таблици
    std::cout << (countLines ? "╚═════════════╩═════════╩════════════╩════════════╩════════════╝\n"
                             : "╚═════════════╩═════════╩════════════╩════════════╝\n");
}
