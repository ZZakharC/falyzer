/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include <iostream>
#include <ostream>
#include "../include/FileAnalyzer.hpp"
#include "../include/locale.hpp"

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

    std::string path_folder;                   // Путь к папке
    bool includeHidden = false,                // Считывать скрытые файлы?
         countLines = false,                   // Считать строки?
         logs = false,                         // ВЫводить логи?
         separator = false;                    // Выводить таблице с разделителем?
    falyzer::SortSettings sortSettings;        // Настройки сортировки
    std::string sortSettingsStr = "percent-0"; // Настройки сортировки (строка)

    // Перебор аргументов
    for (int i = 1; i < argc; i++)
    {
        std::string flag = argv[i]; // флаг

        // Вывод помощи
        if (flag=="-h"||flag=="--help")
        {
            std::cout << locale->usage_text << locale->usage << "\n\n"
                      << locale->help << std::endl;
            return 0;
        }
        
        // Скрытые файлы
        if (flag == "-a") includeHidden = true;
        // Подсчёт строк
        else if (flag == "-l") countLines = true;
        // Логи
        else if (flag == "--logs") logs = true;
        // Разделитель
        else if (flag == "-s") separator = true;
        // Язык
        else if (flag.rfind("--lang=", 0) == 0)
            set_lang(flag.substr(7));
        // Путь к папке для анализа
        else if (flag.rfind("--path=", 0) == 0)
            path_folder = flag.substr(7);
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
                sortSettings.type = falyzer::SortType::NAME;
            else if (method == "percent") 
                sortSettings.type = falyzer::SortType::PERCENT;
            else if (method == "count") 
                sortSettings.type = falyzer::SortType::COUNT;
            else if (method == "size")
                sortSettings.type = falyzer::SortType::SIZE;
            else if (method == "lines")
                sortSettings.type = falyzer::SortType::LINES;
            else // Неопределено
            {
                std::cerr << locale->warn_unknown_method;
                continue;
            }

            sortSettingsStr = method + '-' + mode; // Запись настроек в строку (для логов)

            // Установка режима сортировки
            if (mode == "0")      // Убывание
                sortSettings.isBigEnd = false;
            else if (mode == "1") // Возрастание
                sortSettings.isBigEnd = true;
            else                  // Неопределено
                std::cerr << locale->warn_unknown_mode;
        }
    }

    // Проверка настроек
    if (sortSettings.type == falyzer::SortType::LINES && !countLines)
    {
        std::cerr << locale->warn_lines_method;
        sortSettings.type = falyzer::SortType::PERCENT;
        sortSettings.isBigEnd = 0;
    }

    // Вывод логов
    if (logs)
        std::cout << "Setting:\n"
                  << " path folder: '" << path_folder << "'\n"
                  << " includeHidden: " << includeHidden << '\n'
                  << " countLines: " << countLines << '\n'
                  << " separator: " << separator << '\n'
                  << " sortSettings: " << sortSettingsStr << '\n'
                  << std::endl;

    // Аналитика
    analyticsFiles(path_folder, includeHidden, countLines, separator, logs, sortSettings);

    return 0;
}
