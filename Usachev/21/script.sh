#!/bin/bash

# Проверка наличия аргумента "?"
if [ "$1" = "?" ]; then
    echo "Спецификация программы:"
    echo "Удаление всех файлов с указанным суффиксом при наличии файлов с теми же именами, но с другим заданным суффиксом."
    echo "Использование: ./delete_files.sh [KEY=VALUE, ...]"
    echo "Допустимые ключи:"
    echo "  - NAME: Имя файла без суффикса (обязательный)"
    echo "  - DELSUF: Суффикс файлов для удаления (обязательный)"
    echo "  - SAVESUF: Суффикс файлов для сохранения (обязательный)"
    exit 0
fi

# Инициализация переменных суффиксов по умолчанию
NAME=""
DELSUF=""
SAVESUF=""

# Обработка аргументов командной строки
for arg in $(echo "$@" | tr ',' '\n'); do
    IFS='=' read -ra kv <<< "$arg"  # Разделение ключа и значения по символу "="
    key=${kv[0]}
    value=${kv[1]}
    
    case "$key" in
        "NAME") NAME="$value";;
        "DELSUF") DELSUF="$value";;
        "SAVESUF") SAVESUF="$value";;
        *) echo "Недопустимый ключ: $key"; exit 1;;
    esac
done

# Проверка обязательных аргументов
if [ -z "$NAME" ] || [ -z "$DELSUF" ] || [ -z "$SAVESUF" ]; then
    echo "Необходимо указать все обязательные ключи: NAME, DELSUF, SAVESUF"
    exit 1
fi

# Поиск файлов с одинаковым именем, но разными суффиксами
files=("${NAME}.${DELSUF}" "${NAME}.${SAVESUF}")
found=false
for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        found=true
        break
    fi
done

# Проверка наличия файлов с разными суффиксами
if ! "$found"; then
    echo "Не найдены файлы с одинаковым именем, но разными суффиксами"
    exit 0
fi

# Удаление файлов с указанным суффиксом
for file in "${NAME}.${DELSUF}"*; do
    if [ -f "$file" ]; then
        rm "$file"
        echo "Удален файл: $file"
    fi
done
