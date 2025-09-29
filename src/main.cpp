/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include <iostream>
#include "../include/FileAnalyzer.hpp"

using std::cerr;

// Главная функция
int main(int argc, char *argv[])
{
    // Проверка наличия аргументов
    if (argc < 2)
    {
        cerr << "Использование: " << argv[0] << " <путь_к_папке> [-a] [-l] [-s] [--logs]\n";
        return 1;
    }

    bool includeHidden = false, // Считывать скрытые файлы?
         countLines = false,    // Считать строки?
         logs = false,          // ВЫводить логи?
         separator = false;     // Выводить таблице с разделителем?

    // Перебор аргументов
    for (int i = 2; i < argc; i++)
    {
        std::string flag = argv[i]; // флаг

        // Скрытые файлы
        if (flag == "-a") includeHidden = true;
        // Подсчёт строк
        else if (flag == "-l") countLines = true;
        // Логи
        else if (flag == "--logs") logs = true;
        // Разделитель
        else if (flag == "-s") separator = true;
    }

    // Аналитика
    analyticsFiles(argv[1], includeHidden, countLines, separator, logs);

    return 0;
}
