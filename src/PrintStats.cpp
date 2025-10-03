/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include "../include/PrintStats.hpp"
#include "../include/color_terminal.h"
#include <ios>
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

#include <fstream>
#include <sstream>

// Вывод анализа файлов в указанной папке в виде таблицы.
void printAnalysis(const falyzer::StatsType &stats,
                   const falyzer::PrintStatsSittings &printStatsSittings,
                   const falyzer::AnalyzerSitting &analyzerSitting)
{
    Color colorsTerm = {COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE, COLOR_GRAY, COLOR_BOLD, COLOR_RESET };
    std::ostream* out = &std::cout; 
    std::ofstream file;

    // Определяем куда писать
    switch (printStatsSittings.outStats)
    {
        // COUT
        case falyzer::OutputsStats::CONSOLE:
            out = &std::cout;
            break;

        // TEXT
        case falyzer::OutputsStats::FILE_TEXT:
            file.open(printStatsSittings.outStatsFilePath);
            colorsTerm = {"", "", "", "", "", "", "", "", "", "", ""};
            if (file.is_open()) out = &file;
            break;

        // JSON
        case falyzer::OutputsStats::FILE_JSON:
        {
            file.open(printStatsSittings.outStatsFilePath);
            if (file.is_open())
            {
                file << "{\n"
                         << "  \"folder\": \"" << analyzerSitting.path_folder << "\",\n"
                         << "  \"total_files\": " << stats.totalFiles << ",\n"
                         << "  \"total_size\": \"" << formatSize(stats.totalSize) << "\",\n";
                if (analyzerSitting.countLines)
                    file << "  \"total_lines\": " << stats.totalLines << ",\n";
                file << "  \"files\": [\n";
                bool first = true;
                for (const auto &[type, percent] : stats.list)
                {
                    if (!first) file << ",\n";
                    file << "    { \"type\": \"" << type << "\", "
                             << "\"percent\": " << percent << ", "
                             << "\"count\": " << stats.fileCounts.at(type) << ", "
                             << "\"size\": \"" << formatSize(stats.sizeCounts.at(type)) << "\"";
                    if (analyzerSitting.countLines)
                        file << ", \"lines\": " << stats.lineCounts.at(type);
                    file << " }";
                    first = false;
                }
                file << "\n  ]\n}\n";
            }
            return;
        }
        
        // CSV
        case falyzer::OutputsStats::FILE_CSV:
        {
            file.open(printStatsSittings.outStatsFilePath);
            if (file.is_open())
            {
                // Заголовок
                file << "folder,total_files,total_size";
                if (analyzerSitting.countLines)
                    file << ",total_lines";
                file << "\n";

                // Общая строка
                file << analyzerSitting.path_folder << ","
                    << stats.totalFiles << ","
                    << formatSize(stats.totalSize);
                if (analyzerSitting.countLines)
                    file << "," << stats.totalLines;
                file << "\n\n";

                // Заголовок для списка файлов по типам
                file << "type,percent,count,size";
                if (analyzerSitting.countLines)
                    file << ",lines";
                file << "\n";

                // Данные по каждому типу
                for (const auto &[type, percent] : stats.list)
                {
                    file << type << ","
                        << percent << ","
                        << stats.fileCounts.at(type) << ","
                        << formatSize(stats.sizeCounts.at(type));
                    if (analyzerSitting.countLines)
                        file << "," << stats.lineCounts.at(type);
                    file << "\n";
                }
            }
            return;
        }

        // YAML
        case falyzer::OutputsStats::FILE_YAML:
        {
            std::ofstream file(printStatsSittings.outStatsFilePath);
            if (file.is_open())
            {
                file << "folder: " << analyzerSitting.path_folder << "\n"
                         << "total_files: " << stats.totalFiles << "\n"
                         << "total_size: " << formatSize(stats.totalSize) << "\n";
                if (analyzerSitting.countLines)
                    file << "total_lines: " << stats.totalLines << "\n";
                file << "files:\n";
                for (const auto &[type, percent] : stats.list)
                {
                    file << "  - type: " << type << "\n"
                             << "    percent: " << percent << "\n"
                             << "    count: " << stats.fileCounts.at(type) << "\n"
                             << "    size: " << formatSize(stats.sizeCounts.at(type)) << "\n";
                    if (analyzerSitting.countLines)
                        file << "    lines: " << stats.lineCounts.at(type) << "\n";
                }
            }
            return;
        }
    }

    // ====== НИЖЕ ТАБЛИЧНЫЙ ВЫВОД ======

    // Получения спец цвета для типа файла
    auto getColor = [](const std::string &type, Color colorsTerm) -> std::string
    {
        if (type == "Binary" || type == "Object" || type == "Text" ||
            type == "Image" || type == "Video" || type == "Document" || type == "Archive")
            return colorsTerm.cyan.data();
        if (type == "Other")
            return colorsTerm.gray;
        return colorsTerm.yellow;
    };

    auto sortIndicator = [&](const falyzer::SortSettings &sortSettings)
    {
        char ch = sortSettings.isBigEnd ? '^' : 'v';
        switch (sortSettings.type)
        {
            case falyzer::SortType::NAME:
                *out << "\033[13G"; break;
            case falyzer::SortType::PERCENT:
                *out << "\033[24G"; break;
            case falyzer::SortType::COUNT:
                *out << (locale == &ru_locale ? "\033[37G" : "\033[36G"); break;
            case falyzer::SortType::SIZE:
                *out << (locale == &ru_locale ? "\033[48G" : "\033[47G"); break;
            case falyzer::SortType::LINES:
                *out << "\033[61G"; break;
        }
        *out << colorsTerm.bold << colorsTerm.cyan << ch << colorsTerm.reset;
    };

    // Общая информация
    *out << '\n'
         << locale->analysis_in_folder_text << ' ' << colorsTerm.bold << colorsTerm.magenta << analyzerSitting.path_folder << '\n' << colorsTerm.reset
         << locale->total_files_text << ' ' << colorsTerm.bold << colorsTerm.blue << stats.totalFiles << '\n' << colorsTerm.reset
         << locale->total_size_files_text << ' ' << colorsTerm.bold << colorsTerm.green << formatSize(stats.totalSize) << '\n' << colorsTerm.reset;
    if (analyzerSitting.countLines)
        *out << locale->total_lines_text << ' ' << colorsTerm.bold << colorsTerm.gray << stats.totalLines << '\n' << colorsTerm.reset;
    *out << "\n";

    // Заголовок таблицы
    if (analyzerSitting.countLines)
    {
        *out << "╔═════════════╦═════════╦════════════╦════════════╦════════════╗\n";
        *out << locale->table_header << locale->table_header_lines_text; 
        if (printStatsSittings.outStats == falyzer::OutputsStats::CONSOLE)
            sortIndicator(analyzerSitting.sortSettings);
        *out << "\n╠═════════════╬═════════╬════════════╬════════════╬════════════╣\n";
    }
    else
    {
        *out << "╔═════════════╦═════════╦════════════╦════════════╗\n";
        *out << locale->table_header; 
        if (printStatsSittings.outStats == falyzer::OutputsStats::CONSOLE)
            sortIndicator(analyzerSitting.sortSettings);
        *out << "\n╠═════════════╬═════════╬════════════╬════════════╣\n";
    }

    // Перебор файлов
    for (const auto &[type, percent] : stats.list)
    {
        std::string color = getColor(type, colorsTerm);

        // Тип
        *out << "║ "
             << colorsTerm.bold << color << std::left << std::setw(11) << type << colorsTerm.reset
             << " ║ " << colorsTerm.blue;

        // Процент
        if (percent < 0.01)
            *out << " <0.01";
        else
            *out << std::right << std::setw(6) << std::fixed << std::setprecision(2) << percent;
        *out << '%' << colorsTerm.reset

        // Количество файлов
             << " ║" << colorsTerm.magenta << std::right << std::setw(11) << stats.fileCounts.at(type) << colorsTerm.reset
        
        // Вес файлов
             << " ║" << colorsTerm.green << std::right << std::setw(11) << formatSize(stats.sizeCounts.at(type)) << colorsTerm.reset;

        // Строки
        if (analyzerSitting.countLines)
            *out << " ║" << colorsTerm.gray << std::right << std::setw(11) << (stats.lineCounts.at(type) + 1) << colorsTerm.reset;

        *out << " ║\n";

        if (printStatsSittings.separator)
            *out << "╟─────────────╫─────────╫────────────╫────────────" 
                 << (analyzerSitting.countLines ? "╫────────────╢\n" : "╢\n");
    }

    *out << "╚═════════════╩═════════╩════════════╩════════════"
         << (analyzerSitting.countLines ? "╩════════════╝\n" : "╝\n");
}
