#!/bin/bash
set -e

NAME="build/bin/falyzer"

# Цвета
GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[0;95m'
NC='\033[0m' # No Color

# === Старт ===
echo -e "${GREEN}-------------------STAR-------------------${NC}"

./$NAME .. --logs --sort=size

echo -e "${GREEN}-------------------END--------------------${NC}"
