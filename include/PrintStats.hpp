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
#include "FileAnalyzer.hpp"
#include "falyzer.hpp"
#include "locale.hpp"

struct Color 
{
    std::string black,  
                red,    
                green,  
                yellow, 
                blue,   
                magenta,
                cyan,   
                white,  
                gray,   
                bold,
                reset;
};

/// @brief Конвертация размера
/// @param bytes Размер в байтах
std::string formatSize(unsigned long long bytes);

/**
 * @brief Вывод анализа файлов в указанной папке в виде таблицы.
 *
 * Функция выводит статистику по файлам: количество, процентное распределение,
 * общий размер, а при необходимости — количество строк. Вывод оформлен в виде таблицы
 * с использованием ANSI-цветов для улучшения читаемости.
 *
 * @param stats              Статистика
 * @param printStatsSittings Настройки вывода статистики
 * @param analyzerSitting    Настройки анализа
 */
void printAnalysis(const falyzer::StatsType &stats,
                   const falyzer::PrintStatsSittings &printStatsSittings,
                   const falyzer::AnalyzerSitting &analyzerSitting);
