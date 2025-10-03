/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include <cstdio>
#include <iostream>
#include <ostream>
#include "../include/FileAnalyzer.hpp"
#include "../include/falyzer.hpp"
#include "../include/locale.hpp"
#include "../include/color_terminal.h"

#define VERSION "Falyzer 1.0.0 lin x86_64"

// Главная функция
int main(int argc, char *argv[])
{
    // Автоматическая установка языка интерфейса
    set_lang("auto");

    // Проверка наличия аргументов
    if (argc < 2)
    {
        std::cerr << locale->usage_text << argv[0] << ' ' << locale->usage << '\n'
                  << argv[0] << locale->for_help << std::endl;
        return 1;
    }

    bool logs = false;                              // Включины логи?
    falyzer::AnalyzerSitting analyzerSitting;       // Настройки анализатора
    falyzer::PrintStatsSittings printStatsSittings; // Настройки вывода

    // Перебор аргументов
    for (int i = 1; i < argc; i++)
    {
        std::string flag = argv[i]; // флаг

        // Вывод помощи
        if (flag == "-h" || flag == "--help")
        {
            std::cout << locale->usage_text << locale->usage << "\n\n"
                      << locale->help << std::endl;
            return 0;
        }
        // Версия
        else if (flag == "-v" || flag == "--version")
        {
            std::cout << VERSION << std::endl;
            return 0;
        }
        
        // Скрытые файлы
        if (flag == "-a") analyzerSitting.includeHidden = true;
        // Подсчёт строк
        else if (flag == "-l") analyzerSitting.countLines = true;
        // Логи
        else if (flag == "--logs") logs = true;
        // Разделитель
        else if (flag == "-s") printStatsSittings.separator = true;
        // Язык
        else if (flag.rfind("--lang=", 0) == 0)
            set_lang(flag.substr(7));
        // Путь к папке для анализа
        else if (flag.rfind("--path=", 0) == 0)
            analyzerSitting.path_folder = flag.substr(7);
        // Сортировка
        else if (flag.rfind("--out=", 0) == 0) 
        { 
            std::string file = flag.substr(6); // обрезаем "--out="
            std::string ext;

            // Установка типа сортировки
            if (ext == "cout" || ext == "console") 
            {
                printStatsSittings.outStats = falyzer::OutputsStats::CONSOLE;
                continue;
            }

            // Позиция расширения
            size_t extPos = file.rfind('.');

            if (extPos != std::string::npos)
                ext   = file.substr(extPos + 1);
            else
            {
                std::cerr << COLOR_RED << locale->err_unknown_out_stats << COLOR_RESET << std::endl;
                return 1; 
            }

            if (ext == "txt") 
                printStatsSittings.outStats = falyzer::OutputsStats::FILE_TEXT;
            else if (ext == "scv") 
                printStatsSittings.outStats = falyzer::OutputsStats::FILE_CSV;
            else if (ext == "yaml") 
                printStatsSittings.outStats = falyzer::OutputsStats::FILE_YAML;
            else if (ext == "json") 
                printStatsSittings.outStats = falyzer::OutputsStats::FILE_JSON;
            else // Неопределено
            {
                std::cerr << COLOR_RED << locale->err_unknown_out_stats << COLOR_RESET << std::endl;
                return 1;
            }

            // Путь к файлу
            printStatsSittings.outStatsFilePath = file;
        }
        // Сортировка
        else if (flag.rfind("--sort=", 0) == 0) 
        { 
            std::string value = flag.substr(7); // обрезаем "--sort="
            
            // Разделение на метод и режим
            std::string method;
            std::string mode;
            size_t dashPos = value.find('-');
            
            if (dashPos != std::string::npos)
            {
                method = value.substr(0, dashPos);
                mode   = value.substr(dashPos + 1);
            } else
            {
                method = value;
                mode   = "0"; // если режим не указан, используем 0 (убывание)
            }

            // Установка типа сортировки
            if (method == "name") 
                analyzerSitting.sortSettings.type = falyzer::SortType::NAME;
            else if (method == "percent") 
                analyzerSitting.sortSettings.type = falyzer::SortType::PERCENT;
            else if (method == "count") 
                analyzerSitting.sortSettings.type = falyzer::SortType::COUNT;
            else if (method == "size")
                analyzerSitting.sortSettings.type = falyzer::SortType::SIZE;
            else if (method == "lines")
                analyzerSitting.sortSettings.type = falyzer::SortType::LINES;
            else // Неопределено
            {
                std::cerr << COLOR_YELLOW << locale->warn_unknown_method << COLOR_RESET << std::endl;
                continue;
            }

            analyzerSitting.sortSettingsStr = method + '-' + mode; // Запись настроек в строку (для логов)

            // Установка режима сортировки
            if (mode == "0")      // Убывание
                analyzerSitting.sortSettings.isBigEnd = false;
            else if (mode == "1") // Возрастание
                analyzerSitting.sortSettings.isBigEnd = true;
            else                  // Неопределено
                std::cerr << COLOR_YELLOW << locale->warn_unknown_mode << COLOR_RESET << std::endl;
        }
    }

    // Проверка настроек
    if (analyzerSitting.sortSettings.type == falyzer::SortType::LINES && !analyzerSitting.countLines)
    {
        std::cerr << COLOR_YELLOW << locale->warn_lines_method << COLOR_RESET;
        analyzerSitting.sortSettings.type = falyzer::SortType::PERCENT;
        analyzerSitting.sortSettings.isBigEnd = 0;
    }

    // Вывод логов
    if (logs)
        std::cout << "Setting:\n"
                  << " path folder: '"  << analyzerSitting.path_folder << "'\n"
                  << " includeHidden: " << analyzerSitting.includeHidden << '\n'
                  << " countLines: "    << analyzerSitting.countLines << '\n'
                  << " separator: "     << printStatsSittings.separator << '\n'
                  << " sortSettings: "  << analyzerSitting.sortSettingsStr << '\n'
                  << " outStats: "      << printStatsSittings.outStatsStr << '\n'
                  << std::endl;

    // Аналитика
    analyticsFiles(analyzerSitting, printStatsSittings, logs);

    return 0;
}
