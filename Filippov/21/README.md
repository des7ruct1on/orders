# Описание
Скрипт выполняет замену "\" на "/" в путях некоторых файлов с именем Makefile* \
Например был файл `Makefile1`
> C:\Users\username\Documents\file.txt

После запуска скрипта
> bash -x script.sh tmp_catalog

Файл стал таким
> C:/Users/username/Documents/file.txt

**Трассировка** - это запуск скрипта с ключом **-x**

`tmp_catalog` - каталог, с различными файлами, его и нужно запускать вместе со скриптом
`script.sh` - сам скрипт 