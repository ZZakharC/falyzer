#!/bin/bash
set -e

# Очистка
clear

# Директории
SRC_DIR=./src
BUILD_DIR=./build
BIN_DIR="$BUILD_DIR/bin"
mkdir -p "$BIN_DIR"

# Информация 
VERSION="1.0.0"
NAME="falyzer"

PATH_BIN=$BIN_DIR"/"$NAME

# Цвета
GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[0;95m'
NC='\033[0m' # No Color

# === Компиляция ===
C_FILES=$(find "$SRC_DIR" -name "*.cpp")
OBJ_FILES=""

for file in $C_FILES; do
    BASENAME=$(basename "$file" .cpp)
    OBJ_FILE="$BIN_DIR/$BASENAME.o"
    echo -e "${BLUE}Компиляция: $file -> $OBJ_FILE${NC}"
    g++ -std=c++17 -c "$file" -o "$OBJ_FILE"
    OBJ_FILES="$OBJ_FILES $OBJ_FILE"
done

echo -e "${PURPLE}Линковка -> $PATH_BIN${NC}"
g++ -std=c++20 $OBJ_FILES -o $PATH_BIN

# === Старт ===
echo -e "${GREEN}Программа успешно собрана и находится по адрусу \"${PATH_BIN}\" ${NC}"
