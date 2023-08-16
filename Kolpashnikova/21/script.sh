#!/bin/bash

# Функция, которая генерирует следующую букву или цифру
generate_next_char() {
    local current_char=$1
    local next_char

    if [[ $current_char =~ [0-8] ]]; then
        next_char=$((current_char + 1))
    elif [[ $current_char = 9 ]]; then
        next_char=a
    elif [[ $current_char = z ]]; then
        next_char=0
    else
        next_char=$(echo "$current_char" | tr "a-y" "b-z")
    fi

    echo "$next_char"
}

# Проверяем, что переданы нужные аргументы
if [[ $# -lt 2 ]]; then
    echo "Использование: $0 <исходный_файл> <число_копий> [начальный_символ]"
    exit 1
fi

source_file=$1
num_copies=$2
start_char=${3:-a}  # Если начальный символ не указан, используем "a"

# Проверяем, что исходный файл существует
if [[ ! -f $source_file ]]; then
    echo "Ошибка: Файл '$source_file' не существует."
    exit 1
fi

# Проверяем, что число копий является положительным числом
if [[ ! $num_copies =~ ^[0-9]+$ || $num_copies -lt 1 ]]; then
    echo "Ошибка: Число копий должно быть положительным целым числом."
    exit 1
fi

# Проверяем, что начальный символ является буквой или цифрой
if [[ ! $start_char =~ ^[a-zA-Z0-9]$ ]]; then
    echo "Ошибка: Начальный символ должен быть буквой (a-z, A-Z) или цифрой (0-9)."
    exit 1
fi

# Получаем расширение исходного файла (если есть)
extension="${source_file##*.}"

# Получаем имя файла без расширения
filename="${source_file%.*}"

# Копируем файл нужное число раз с добавлением букв или цифр
for ((i = 1; i <= num_copies; i++)); do
    copy_file="${filename}_${start_char}"
    [[ -n $extension ]] && copy_file="$copy_file.$extension"
    cp "$source_file" "$copy_file"
    start_char=$(generate_next_char "$start_char")
done
echo "Генерация копий файла завершена."
