/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
*/

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// @brief Конвертация размера
/// @param bytes Размер в байтах
std::string formatSize(unsigned long long bytes);

/**
 * @brief Вывод анализа файлов в указанной папке в виде таблицы.
 *
 * Функция выводит в консоль статистику по файлам: количество, процентное распределение,
 * общий размер, а при необходимости — количество строк. Вывод оформлен в виде таблицы
 * с использованием ANSI-цветов для улучшения читаемости.
 *
 * @param folder       Путь к папке, по которой строится анализ.
 * @param totalFiles   Общее количество файлов в директории.
 * @param totalLines   Общее количество строк во всех файлах (учитывается, если countLines = true).
 * @param totalSize    Суммарный размер всех файлов в байтах.
 * @param sortedCounts Вектор пар {тип файла, процент}, отсортированный по убыванию процента.
 * @param fileCounts   Ассоциативный массив: {тип файла → количество файлов}.
 * @param lineCounts   Ассоциативный массив: {тип файла → количество строк}.
 * @param sizeCounts   Ассоциативный массив: {тип файла → общий размер в байтах}.
 * @param countLines   Флаг: если true — выводить количество строк; если false — без строк.
 * @param separator    Флаг: если true — печатать разделительные линии между строками таблицы.
 */
void printAnalysis(const std::string &folder, const unsigned long totalFiles,
                   const unsigned long totalLines, const unsigned long long totalSize,
                   const std::vector<std::pair<std::string, double>> &sortedCounts,
                   const std::unordered_map<std::string, int> &fileCounts,
                   const std::unordered_map<std::string, int> &lineCounts,
                   const std::unordered_map<std::string, unsigned long long> &sizeCounts,
                   bool countLines, bool separator);
