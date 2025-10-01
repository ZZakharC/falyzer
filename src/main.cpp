/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include <iostream>
#include <ostream>
#include "../include/FileAnalyzer.hpp"

// Главная функция
int main(int argc, char *argv[])
{
    // Проверка наличия аргументов
    if (argc < 2)
    {
        std::cerr << "Использование: " << argv[0] << " <путь_к_папке> [-h | --help] [-a] [-l] [-s] [--logs] [--sort=<метод>-<режим>]\n" 
                  << argv[0] << " -h для помощи." << std::endl;
        return 1;
    }

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

        if (flag=="-h"||flag=="--help")
        {
            std::cout << "Использование: <путь_к_папке> [ключи]\n\n"

            << "Ключи(флаги):\n"
            << "  [-h | --help]              Выводит список флагов.\n\n"
            << "  [-a]                       Включает в статистику скрытые файлы.\n\n"
            << "  [-l]                       Включает счёт строк в файлах (может сильно замедлить программу).\n\n"
            << "  [-s]                       Добавляет разделители в выводимую таблицу.\n\n"
            << "  [--logs]                   Выводит логи.\n\n"
            << "  [--sort=<метод>-<режим>]   Настройка сортировки результатов. По умолчанию используется `percent-0`.\n"

            << "    Методы сортировки (<метод>):\n"
            << "      name      по имени типа файлов (алфавитно)\n"
            << "      percent   по проценту количества относительно общего числа файлов\n"
            << "      count     по количеству файлов\n"
            << "      size      по общему размеру файлов данного типа\n"
            << "      lines     по числу строк (требует флаг -l)\n\n"
   
            << "    Режимы сортировки (<режим>):\n"
            << "      0         по убыванию (от большего к меньшему)\n"
            << "      1         по возрастанию (от меньшего к большему)" << std::endl;

            return 0;
        }
        // Пропуск если первый аргумент не -h. Потому что это либо путь или -h
        else if (i == 1)
            continue;

        // Скрытые файлы
        if (flag == "-a") includeHidden = true;
        // Подсчёт строк
        else if (flag == "-l") countLines = true;
        // Логи
        else if (flag == "--logs") logs = true;
        // Разделитель
        else if (flag == "-s") separator = true;
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
                std::cerr << "[WARN] Неизвестный метод сортировки: " << method 
                        << ". Используется percent-0 по умолчанию.\n";
                continue;
            }

            sortSettingsStr = method + '-' + mode; // Запись настроек в строку (для логов)

            // Установка режима сортировки
            if (mode == "0")      // Убывание
                sortSettings.isBigEnd = false;
            else if (mode == "1") // Возрастание
                sortSettings.isBigEnd = true;
            else                  // Неопределено
                std::cerr << "[WARN] Неизвестный режим сортировки: " << mode 
                        << ". Используется 0 (убывание) по умолчанию.\n";
        }
    }

    // Проверка настроек
    if (sortSettings.type == falyzer::SortType::LINES && !countLines)
    {
        std::cerr << "[WARN] Подсчёт строк отключён их сортировка невозможна! Используется percent-0 по умолчанию.\n";
        sortSettings.type = falyzer::SortType::PERCENT;
        sortSettings.isBigEnd = 0;
    }

    // Вывод логов
    if (logs)
        std::cout << "Setting:\n"
                  << " includeHidden: " << includeHidden << '\n'
                  << " countLines: " << countLines << '\n'
                  << " separator: " << separator << '\n'
                  << " sortSettings: " << sortSettingsStr << '\n'
                  << std::endl;

    // Аналитика
    analyticsFiles(argv[1], includeHidden, countLines, separator, logs, sortSettings);

    return 0;
}
