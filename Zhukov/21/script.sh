#!/bin/bash

# Проверяем, заданы ли ключевые параметры через аргументы командной строки
if [[ $# -eq 0 ]]; then
    read -p "Введите имя файла: " FILE
    read -p "Введите количество копий: " COUNT
else
    # Разбираем аргументы командной строки
    for arg in "$@"; do
        case "$arg" in
            FILE=*)
                FILE="${arg#*=}"
                ;;
            COUNT=*)
                COUNT="${arg#*=}"
                ;;
        esac
    done
fi

# Проверяем, существует ли указанный файл
if [ ! -e "$FILE" ]; then
    echo "Файл $FILE не существует."
    exit 1
fi

# Проверяем, является ли COUNT числом
if ! [[ "$COUNT" =~ ^[0-9]+$ ]]; then
    echo "COUNT должно быть целым числом."
    exit 1
fi

# Получаем расширение файла (если оно есть)
EXTENSION="${FILE##*.}"
# Получаем имя файла без расширения
BASENAME="${FILE%.*}"

# Функция для генерации нового имени файла
generate_new_filename() {
    local index="$1"
    if [[ "$BASENAME" =~ [0-9]$ ]]; then
        # Если имя файла оканчивается на цифру, добавляем следующую цифру
        new_filename="${BASENAME%[0-9]}$((index+1)).$EXTENSION"
    else
        # Если имя файла не оканчивается на цифру, добавляем следующую букву в алфавите
        new_filename="${BASENAME}_$((index)).$EXTENSION"
    fi
}

# Создаем копии файла
for ((i = 1; i <= COUNT; i++)); do
    generate_new_filename $i
    cp "$FILE" "$new_filename"
    echo "Создана копия $new_filename"
done
