/*
    Copyright (C) 2025 Zakhar Shakhanov

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.

*/

#include "../include/locale.hpp"

// Английский
Locale en_locale =
{
    .usage_text = "Usage: ",
    .usage = "--path=<path_to_folder> [keys]",
    .for_help = " -h for help.",
    .help = "\
Keys (flags):\n\
  [-h | --help]             Displays a list of flags.\n\n\
  [-a]                      Includes hidden files in the statistics.\n\n\
  [-l]                      Enables line counting in files (may significantly slow down the program).\n\n\
  [-s]                      Adds separators to the output table.\n\n\
  [--logs]                  Displays logs.\n\n\
  [--lang=<language>]       Sets the interface language.\n\
    Available languages:\n\
      en        English\n\
      fr        Français\n\
      de        Deutsch\n\
      ru        Русский\n\
      es        Español\n\n\
  [--sort=<method>-<mode>]  Configures result sorting. By default, percent-0 is used.\n\
    Methods (<method>):\n\
      name      by file type name (alphabetical)\n\
      percent   by percentage relative to the total number of files\n\
      count     by number of files\n\
      size      by total size of files of this type\n\
      lines     by number of lines (requires the -l flag)\n\n\
    Modes (<mode>):\n\
      0         descending (from larger to smaller)\n\
      1         ascending (from smaller to larger)",
      .warn_unknown_method     = "[WARN] Unknown sort method! Using percent-0 by default.\n",
      .warn_unknown_mode       = "[WARN] Unknown sort mode. Using 0 (descending) by default.\n",
      .warn_lines_method       = "[WARN] Row counting is disabled; sorting is not possible! Using percent-0 by default.\n",
      .err_folder              = "[ERROR] The specified folder does not exist or is not a directory.\n",
      .warn_failed_process     = "[WARN] Failed to process ",
      .no_file_in_folder       = "There are no files in the specified folder.\n",
      .analysis_in_folder_text = "Analysis of files in the folder:",
      .total_files_text        = "Total files in directory:",
      .total_size_files_text   = "Total size of all files:",
      .total_lines_text        = "Total lines in all files:",
      .table_header            = "║  File Type  ║ Percent ║  Quantity  ║    Size    ║",
      .table_header_lines_text = "    Lines   ║",

};
// Русский
Locale ru_locale =
{
    .usage_text = "Использование: ",
    .usage = "--path=<путь_к_папке> [ключи]",
    .for_help = " -h для помощи.",
    .help = "\
Ключи(флаги):\n\
  [-h | --help]              Выводит список флагов.\n\n\
  [-a]                       Включает в статистику скрытые файлы.\n\n\
  [-l]                       Включает счёт строк в файлах (может сильно замедлить программу).\n\n\
  [-s]                       Добавляет разделители в выводимую таблицу.\n\n\
  [--logs]                   Выводит логи.\n\n\
  [--lang=<язык>]            Устанавливает язык интерфейса.\n\
    Доступные язык:\n\
      en        English\n\
      fr        Français\n\
      de        Deutsch\n\
      ru        Русский\n\
      es        Español\n\n\
  [--sort=<метод>-<режим>]   Настройка сортировки результатов. По умолчанию используется `percent-0`.\n\
    Методы сортировки (<метод>):\n\
      name      по имени типа файлов (алфавитно)\n\
      percent   по проценту количества относительно общего числа файлов\n\
      count     по количеству файлов\n\
      size      по общему размеру файлов данного типа\n\
      lines     по числу строк (требует флаг -l)\n\n\
    Режимы сортировки (<режим>):\n\
      0         по убыванию (от большего к меньшему)\n\
      1         по возрастанию (от меньшего к большему)",
      .warn_unknown_method     = "[WARN] Неизвестный метод сортировки! Используется percent-0 по умолчанию.\n",
      .warn_unknown_mode       = "[WARN] Неизвестный режим сортировки. Используется 0 (убывание) по умолчанию.\n",
      .warn_lines_method       = "[WARN] Подсчёт строк отключён их сортировка невозможна! Используется percent-0 по умолчанию.\n",
      .err_folder              = "[ERROR] Указанная папка не существует или это не директория.\n",
      .warn_failed_process     = "[WARN] Не удалось обработать ",
      .no_file_in_folder       = "В указанной папке нет файлов.\n",
      .analysis_in_folder_text = "Анализ файлов в папке:",
      .total_files_text        = "Всего файлов в директории:",
      .total_size_files_text   = "Общий размер всех файлов:",
      .total_lines_text        = "Всего строк во всех файлах:",
      .table_header            = "║  Тип файла  ║ Процент ║ Количество ║   Размер   ║",
      .table_header_lines_text = "   Строки   ║",

};
// Французский
Locale fr_locale =
{
    .usage_text = "Utilisation : ",
    .usage = "--path=<chemin_du_dossier> [options]",
    .for_help = " -h pour obtenir de l'aide.",
    .help = "\
Options (flags):\n\
  [-h | --help]              Affiche la liste des options.\n\n\
  [-a]                       Inclut les fichiers cachés dans les statistiques.\n\n\
  [-l]                       Active le comptage des lignes dans les fichiers (peut ralentir considérablement le programme).\n\n\
  [-s]                       Ajoute des séparateurs au tableau de sortie.\n\n\
  [--logs]                   Affiche les journaux.\n\n\
  [--lang=<langue>]          Définit la langue de l'interface.\n\
    Langues disponibles:\n\
      en        English\n\
      fr        Français\n\
      de        Deutsch\n\
      ru        Русский\n\
      es        Español\n\n\
  [--sort=<méthode>-<mode>]  Configure le tri des résultats. Par défaut, `percent-0` est utilisé.\n\
    Méthodes (<méthode>):\n\
      name      par nom du type de fichier (alphabétique)\n\
      percent   par pourcentage par rapport au nombre total de fichiers\n\
      count     par nombre de fichiers\n\
      size      par taille totale des fichiers de ce type\n\
      lines     par nombre de lignes (requiert l'option -l)\n\n\
    Modes (<mode>):\n\
      0         décroissant (du plus grand au plus petit)\n\
      1         croissant (du plus petit au plus grand)",
    .warn_unknown_method     = "[WARN] Méthode de tri inconnue ! Utilisation de percent-0 par défaut.\n",
    .warn_unknown_mode       = "[WARN] Mode de tri inconnu. Utilisation de 0 (décroissant) par défaut.\n",
    .warn_lines_method       = "[WARN] Le comptage des lignes est désactivé ; le tri n'est pas possible ! Utilisation de percent-0 par défaut.\n",
    .err_folder              = "[ERROR] Le dossier spécifié n'existe pas ou n'est pas un répertoire.\n",
    .warn_failed_process     = "[WARN] Échec du traitement de ",
    .no_file_in_folder       = "Il n'y a aucun fichier dans le dossier spécifié.\n",
    .analysis_in_folder_text = "Analyse des fichiers dans le dossier :",
    .total_files_text        = "Nombre total de fichiers dans le répertoire :",
    .total_size_files_text   = "Taille totale de tous les fichiers :",
    .total_lines_text        = "Nombre total de lignes dans tous les fichiers :",
    .table_header            = en_locale.table_header,
    .table_header_lines_text = en_locale.table_header_lines_text,
};

// Немецкий
Locale de_locale =
{
    .usage_text = "Verwendung: ",
    .usage = "--path=<pfad_zum_ordner> [optionen]",
    .for_help = " -h für Hilfe.",
    .help = "\
Optionen (Flags):\n\
  [-h | --help]              Zeigt eine Liste der Optionen an.\n\n\
  [-a]                       Schließt versteckte Dateien in die Statistik ein.\n\n\
  [-l]                       Aktiviert das Zählen von Zeilen in Dateien (kann das Programm erheblich verlangsamen).\n\n\
  [-s]                       Fügt Trenner in die Ausgabetabelle ein.\n\n\
  [--logs]                   Zeigt Protokolle an.\n\n\
  [--lang=<sprache>]         Legt die Sprache der Benutzeroberfläche fest.\n\
    Verfügbare Sprachen:\n\
      en        English\n\
      fr        Français\n\
      de        Deutsch\n\
      ru        Русский\n\
      es        Español\n\n\
  [--sort=<methode>-<modus>] Konfiguriert die Sortierung der Ergebnisse. Standardmäßig wird `percent-0` verwendet.\n\
    Methoden (<methode>):\n\
      name      nach Dateitypname (alphabetisch)\n\
      percent   nach Prozentsatz relativ zur Gesamtzahl der Dateien\n\
      count     nach Anzahl der Dateien\n\
      size      nach Gesamtgröße der Dateien dieses Typs\n\
      lines     nach Zeilenanzahl (benötigt die Option -l)\n\n\
    Modi (<modus>):\n\
      0         absteigend (von größer nach kleiner)\n\
      1         aufsteigend (von kleiner nach größer)",
    .warn_unknown_method     = "[WARN] Unbekannte Sortiermethode! Standardmäßig wird percent-0 verwendet.\n",
    .warn_unknown_mode       = "[WARN] Unbekannter Sortiermodus. Standardmäßig wird 0 (absteigend) verwendet.\n",
    .warn_lines_method       = "[WARN] Zeilenzählen ist deaktiviert; Sortierung nicht möglich! Standardmäßig wird percent-0 verwendet.\n",
    .err_folder              = "[ERROR] Der angegebene Ordner existiert nicht oder ist kein Verzeichnis.\n",
    .warn_failed_process     = "[WARN] Verarbeitung fehlgeschlagen ",
    .no_file_in_folder       = "Im angegebenen Ordner befinden sich keine Dateien.\n",
    .analysis_in_folder_text = "Analyse der Dateien im Ordner:",
    .total_files_text        = "Gesamtanzahl der Dateien im Verzeichnis:",
    .total_size_files_text   = "Gesamtgröße aller Dateien:",
    .total_lines_text        = "Gesamtanzahl der Zeilen in allen Dateien:",
    .table_header            = en_locale.table_header,
    .table_header_lines_text = en_locale.table_header_lines_text,
};

// Испанский
Locale es_locale =
{
    .usage_text = "Uso: ",
    .usage = "--path=<ruta_a_la_carpeta> [opciones]",
    .for_help = " -h para ayuda.",
    .help = "\
Opciones (flags):\n\
  [-h | --help]              Muestra una lista de opciones.\n\n\
  [-a]                       Incluye archivos ocultos en las estadísticas.\n\n\
  [-l]                       Habilita el conteo de líneas en los archivos (puede ralentizar significativamente el programa).\n\n\
  [-s]                       Agrega separadores a la tabla de salida.\n\n\
  [--logs]                   Muestra registros.\n\n\
  [--lang=<idioma>]          Establece el idioma de la interfaz.\n\
    Idiomas disponibles:\n\
      en        English\n\
      fr        Français\n\
      de        Deutsch\n\
      ru        Русский\n\
      es        Español\n\n\
  [--sort=<método>-<modo>]   Configura la ordenación de resultados. Por defecto se usa `percent-0`.\n\
    Métodos (<método>):\n\
      name      por nombre del tipo de archivo (alfabético)\n\
      percent   por porcentaje relativo al número total de archivos\n\
      count     por número de archivos\n\
      size      por tamaño total de los archivos de este tipo\n\
      lines     por número de líneas (requiere la opción -l)\n\n\
    Modos (<modo>):\n\
      0         descendente (de mayor a menor)\n\
      1         ascendente (de menor a mayor)",
    .warn_unknown_method     = "[WARN] ¡Método de ordenación desconocido! Usando percent-0 por defecto.\n",
    .warn_unknown_mode       = "[WARN] Modo de ordenación desconocido. Usando 0 (descendente) por defecto.\n",
    .warn_lines_method       = "[WARN] El conteo de líneas está deshabilitado; ¡la ordenación no es posible! Usando percent-0 por defecto.\n",
    .err_folder              = "[ERROR] La carpeta especificada no existe o no es un directorio.\n",
    .warn_failed_process     = "[WARN] No se pudo procesar ",
    .no_file_in_folder       = "No hay archivos en la carpeta especificada.\n",
    .analysis_in_folder_text = "Análisis de archivos en la carpeta:",
    .total_files_text        = "Total de archivos en el directorio:",
    .total_size_files_text   = "Tamaño total de todos los archivos:",
    .total_lines_text        = "Total de líneas en todos los archivos:",
    .table_header            = en_locale.table_header,
    .table_header_lines_text = en_locale.table_header_lines_text,
};

Locale *locale = &en_locale; // Текущая локаль

// Установка языка
void set_lang(std::string l)
{
    // Устанавливаем локаль из переменных окружения
    std::setlocale(LC_ALL, "");
    std::string locale_use; // Локаль
    
    if (l == "auto") // Использовать локаль системы
        locale_use = std::setlocale(LC_ALL, nullptr);
    else
        locale_use = l;

    // Приводим к нижнему регистру
    std::transform(locale_use.begin(), locale_use.end(), locale_use.begin(), 
                   [](unsigned char c){ return std::tolower(c); });

    // Получаем текущую локаль
    if (locale_use.rfind("ru", 0) == 0)
        locale = &ru_locale;
    else if (locale_use.rfind("fr", 0) == 0)
        locale = &fr_locale;
    else if (locale_use.rfind("de", 0) == 0)
        locale = &de_locale;
    else if (locale_use.rfind("es", 0) == 0)
        locale = &es_locale;
    else
        locale = &en_locale;
}