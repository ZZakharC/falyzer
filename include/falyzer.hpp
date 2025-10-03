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

    struct AnalyzerSitting 
    {
        std::string path_folder;                   // Путь к папке
        bool includeHidden = false,                // Считывать скрытые файлы?
             countLines = false;                   // Считать строки?
        falyzer::SortSettings sortSettings;        // Настройки сортировки
        std::string sortSettingsStr = "percent-0"; // Настройки сортировки (строка)
    };

    enum class OutputsStats
    {
        CONSOLE,
        FILE_TEXT,
        FILE_CSV, 
        FILE_JSON, 
        FILE_YAML
    };

    struct PrintStatsSittings 
    {
        bool separator = false;                        // Выводить таблице с разделителем?
        OutputsStats outStats = OutputsStats::CONSOLE; // Вывод статистики
        std::string outStatsStr = "cout(console)";     // Вывод статистики (строка)
        std::string outStatsFilePath;                  // Путь к файлу для вывод статистики
    };

    struct StatsType
    {
        unsigned long totalFiles,                                 // Всего файлов
                      totalLines;                                 // Всего строк
        unsigned long long totalSize;                             // Общий вес
        std::vector<std::pair<std::string, double>> list; // Отсортированный список
        std::unordered_map<std::string, int> fileCounts,          // Количество файлов (о. типа)
                                             lineCounts;          // Количество строк (в файле о. типа)
        std::unordered_map<std::string, unsigned long long> sizeCounts; // Вес файла (о. типа)
    };
}