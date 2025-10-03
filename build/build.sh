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

# Компилятор
CC="g++" # GCC можно Clang
LD="g++"
FLAGS_CC="-std=c++20"
FLAGS_LD="-std=c++20"
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
    $CC $FLAGS_CC -c "$file" -o "$OBJ_FILE"
    OBJ_FILES="$OBJ_FILES $OBJ_FILE"
done

echo -e "${PURPLE}Линковка -> $PATH_BIN${NC}"
$LD $FLAGS_LD $OBJ_FILES -o $PATH_BIN

# === Старт ===
echo -e "${GREEN}Программа успешно собрана и находится по адресу \"${PATH_BIN}\" ${NC}"
