/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include "../include/FileAnalyzer.hpp"
#include "../include/PrintUtils.hpp"

namespace fs = std::filesystem;

// Подсчёт строк
int countFileLines(const fs::path &file)
{
    std::ifstream in(file);      // Открытия файла
    if (!in.is_open()) return 0; // Выход в случае ошибки
    return static_cast<int>(std::count(std::istreambuf_iterator<char>(in),
                                       std::istreambuf_iterator<char>(), '\n'));
}

// Проверка скрытый ли файл
bool isHiddenPath(const fs::path &p) {
    for (const auto &part : p) {
        std::string name = part.string();
        if (name == "." || name == "..") continue;
        if (!name.empty() && name[0] == '.') return true;
    }
    return false;
}

/// Сбор аналитики файлов
void analyticsFiles(const std::string &folderStr, bool includeHidden, bool countLines, bool separator, bool logs, falyzer::SortSettings sortSettings)
{
    fs::path folder(folderStr); // Рабочая директория

    // Проверка директории
    if (!fs::exists(folder) || !fs::is_directory(folder))
    {
        std::cerr << "Ошибка: указанная папка не существует или это не директория.\n";
        return;
    }

    // Список расширений файлов
    static const std::unordered_map<std::string, std::string> extensions = {
        // ЯП
        {".hpp", "C++"}, {".cpp", "C++"}, {".cc", "C++"}, {".cxx", "C++"},
        {".hh", "C++"}, {".hxx", "C++"}, {".c++", "C++"}, {".h++", "C++"},
        {".java", "Java"}, {".html", "HTML"}, {".htm", "HTML"}, {".css", "CSS"},
        {".scss", "CSS"}, {".c", "C"}, {".h", "C"}, {".cs", "C#"}, {".csx", "C#"},
        {".js", "JavaScript"}, {".cjs", "JavaScript"}, {".mjs", "JavaScript"},
        {".sql", "SQL"}, {".tsql", "Transact-SQL"}, {".go", "Go"},
        {".pas", "Delphi"}, {".dpr", "Delphi"}, {".vb", "Visual Basic"},
        {".f90", "Fortran"}, {".f95", "Fortran"}, {".f", "Fortran"}, {".for", "Fortran"},
        {".php", "PHP"}, {".r", "R"}, {".m", "MATLAB"}, {".asm", "Assembly"},
        {".rb", "Ruby"}, {".swift", "Swift"}, {".kt", "Kotlin"}, {".rs", "Rust"},
        {".rlib", "Rust"}, {".hs", "Haskell"}, {".dart", "Dart"}, {".pl", "Perl"},
        {".scala", "Scala"}, {".lua", "Lua"}, {".mm", "Objective-C"}, {".bash", "Bash"},
        {".jl", "Julia"}, {".ts", "TypeScript"}, {".tsx", "TypeScript"},
        {".sol", "Solidity"}, {".sh", "Bash"}, {".ps1", "PowerShell"}, {".s", "Assembly"},
        {".ex", "Elixir"}, {".exs", "Elixir"}, {".py", "Python"}, {".pyt", "Python"},
        {".pyc", "Python"}, {".pyi", "Python"}, {".pyd", "Python"}, {".pyw", "Python"},
            
        /// Не ЯП

        // Обектные
        {".o", "Object"}, {".obj", "Object"}, {".lib", "Object"},
        {".a", "Object"}, {".so", "Object"}, {".dll", "Object"},

        // Бинарные
        {".bin", "Binary"}, {".exe", "Binary"}, {".dat", "Binary"},
        {".img", "Binary"}, {".iso", "Binary"}, {".class", "Binary"},
        {".elf", "Binary"}, {".apk", "Binary"}, {".app", "Binary"},
        {".sys", "Binary"}, {".drv", "Binary"}, {".msi", "Binary"},
        {".binpack", "Binary"}, {".dmg", "Binary"}, {".AppImage", "Binary"}, 

        // Архивы
        {".zip", "Archive"}, {".rar", "Archive"}, {".7z", "Archive"},
        {".tar", "Archive"}, {".gz", "Archive"}, {".bz2", "Archive"}, {".xz", "Archive"},

        // Текст
        {".txt", "Text"}, {".log", "Text"}, {".md", "Text"},
        {".csv", "Text"}, {".tsv", "Text"}, {".json", "Text"},
        {".xml", "Text"}, {".yaml", "Text"}, {".yml", "Text"},
        {".conf", "Text"}, {".ini", "Text"}, {".cfg", "Text"},
            
        // Изображения
        {".jpg", "Image"}, {".jpeg", "Image"}, {".png", "Image"},
        {".gif", "Image"}, {".bmp", "Image"}, {".tif", "Image"},
        {".tiff", "Image"}, {".webp", "Image"}, {".heic", "Image"},
        {".heif", "Image"}, {".avif", "Image"}, {".svg", "Image"},
        {".ai", "Image"}, {".cdr", "Image"}, {".eps", "Image"},
        {".psd", "Image"}, {".xcf", "Image"},{".ico", "Image"},
        {".icns", "Image"}, {".zpif", "Image"},

        // Видео
        {".mp4", "Video"}, {".mkv", "Video"}, {".avi", "Video"},
        {".mov", "Video"}, {".wmv", "Video"}, {".flv", "Video"},
        {".webm", "Video"}, {".mpeg", "Video"}, {".mpg", "Video"},
        {".3gp", "Video"}, {".m4v", "Video"}, {".vob", "Video"},
        {".mts", "Video"}, {".rm", "Video"}, {".rmvb", "Video"},
        {".ogv", "Video"}, {".f4v", "Video"}, {".mxf", "Video"},

        // Документы
        {".doc", "Document"}, {".docx", "Document"}, {".odt", "Document"},
        {".rtf", "Document"}, {".pdf", "Document"}, {".tex", "Document"},
        {".ppt", "Document"}, {".pptx", "Document"}, {".xls", "Document"},
        {".xlsx", "Document"}, {".ods", "Document"}

    };

    std::unordered_map<std::string, int> fileCounts,                // Количество файлов
                                         lineCounts;                // Количество строк
    std::unordered_map<std::string, unsigned long long> sizeCounts; // Размер

    unsigned long totalLines = 0,     // Всего строк
                  totalFiles = 0;     // Всего файлов
    unsigned long long totalSize = 0; // Общий размер всех файлов

    for (auto &entry : fs::recursive_directory_iterator(folder, fs::directory_options::skip_permission_denied))
    {
        try
        {
            if (entry.is_directory()) continue;
            if (!includeHidden && isHiddenPath(entry.path())) continue;
            if (logs) std::cout << entry.path() << std::endl;

            // Расширения файла
            std::string ext = entry.path().extension().string(); // Расширения
            // Приводим к нижнему регистру
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            // Получаем тип
            std::string type = extensions.count(ext) ? extensions.at(ext) : "Other"; // Тип

            // Увелечения общих значений
            totalFiles++;                                               // Количество файлов
            totalSize += fs::file_size(entry.path());                   // Размер
            if (countLines) totalLines += countFileLines(entry.path()); // Строки
            
            // Увелечения индивидуальных значений
            fileCounts[type]++;
            sizeCounts[type] += fs::file_size(entry.path());
            if (countLines) lineCounts[type] += countFileLines(entry.path());
        }
        // Обработка ошибок
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Предупреждение: не удалось обработать " 
                      << entry.path() << " (" << e.what() << ")\n";
            continue;
        }
    }

    // Сортировка
    // Сбор всех данных в вектор
    std::vector<falyzer::FileStats> stats;
    for (const auto &[type, count] : fileCounts) {
        falyzer::FileStats fs;
        fs.type = type;
        fs.count = count;
        fs.size = sizeCounts.count(type) ? sizeCounts.at(type) : 0;
        fs.lines = countLines && lineCounts.count(type) ? lineCounts.at(type) : 0;
        fs.percent = totalFiles > 0 ? (double)count / totalFiles * 100.0 : 0.0;
        stats.push_back(fs);
    }

    // Компаратор для сортировки
    auto cmp = [&](const falyzer::FileStats &a, const falyzer::FileStats &b) {
        auto less = [&](auto x, auto y) { return sortSettings.isBigEnd ? x < y : x > y; };

        switch (sortSettings.type)
        {
            case falyzer::SortType::NAME:
                return less(b.type, a.type);
            case falyzer::SortType::PERCENT:
                return less(a.percent, b.percent);
            case falyzer::SortType::COUNT:
                return less(a.count, b.count);
            case falyzer::SortType::SIZE:
                return less(a.size, b.size);
            case falyzer::SortType::LINES:
                return less(a.lines, b.lines);
        }
        return false;
    };

    std::sort(stats.begin(), stats.end(), cmp);

    // Подготовка данных для вывода (как раньше sortedCounts)
    std::vector<std::pair<std::string, double>> sortedCounts;
    for (const auto &s : stats) {
        sortedCounts.emplace_back(s.type, s.percent);
    }

    // Вывод аналитики
    printAnalysis(folderStr, totalFiles, totalLines, totalSize, sortedCounts, fileCounts, lineCounts, sizeCounts, sortSettings, countLines, separator);
}
