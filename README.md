# Falyzer

![License](https://img.shields.io/badge/License-GPLv3-green)
![C++20](https://img.shields.io/badge/C++-20-red)

**Falyzer** — это гибкий инструмент для анализа файлов различных форматов.  
Он помогает быстро извлекать полезную информацию, автоматизировать обработку и интегрировать результаты в другие системы.

[![Donate](https://img.shields.io/badge/Donate-Поддержать%20проект-007BFF?style=for-the-badge)](https://pay.cloudtips.ru/p/204a4487)

---
![Screenshot](screenshot/a1.png "Screenshot")
![Screenshot](screenshot/a2.png "Screenshot")
![Screenshot](screenshot/a3.png "Screenshot")
![Screenshot](screenshot/a4.png "Screenshot")


## 🖥️Использования
```bash
falyzer <путь_к_папке> [-a] [-l] [-s] [--logs]
```
### Флаги
- `-a` - Учитывает скрытые файлы
- `-l` - Подсчитывает строки в файлах
- `-s` - Добавляет разделители в выводимую таблицу
- `--logs` - выводит логи (файлы которые обрабатывает)

## 🚀 Возможности
- Поддержка разных типов файлов.
- Гибкая настройка анализа под задачи.
- Простое подключение к существующим проектам.
- Расширяемая архитектура (можно добавлять свои модули анализа).

---

## 🛠 Установка
Клонируйте репозиторий:
```bash
git clone https://github.com/ZZakharC/falyzer.git
cd falyzer
