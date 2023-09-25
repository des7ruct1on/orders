# Описание
Описание функций
- void initQueue(queue *D) - инициализируем очередь, задаем нулевые указатели и нулевой размер \
- int sizeQueue(queue *D) - возвращает размер очереди \
- bool emptyQueue(queue *D) - проверка на пустоту очереди \
- void pushFront(queue *D, int value) - добавление элемента спереди \
- int popBack(queue *D) - удаление элемента сзади \
- int topBack(queue *D) - функция выводящая значение последнего элемента без его удаления(в принципе нахуй не нужна, я в итоге не воспользовался ею) \
- void deleteQueue(queue *D) - функция очистки всей очереди \
- void printQueue(queue *D) - функция вывода очереди

**Структура**

typedef struct element { \
    int value; //значение \
    struct element *next; //указ на след элемент \
} element;

сверху расписана структура каждого элемента очереди, он ссылается на некст элемент и имеет собственное значение

typedef struct queue { \
    element *first; //первый элемент \
    element *last; //последний элемент \
    int size; //рамзер \
} queue; \

сверху - структура самой очереди, она хранит указатель на первый элемент, последний и размер

mergeSort - функция сортировки вставкой. прям самая типичная сортировка как в википедии

**Makefile**
> тут короче все просто 
>- пишешь сначала `make` и у тебя компилируется вся программа со всем необхимым, 
>- затем ты пишешь `make run` и у тебя запускается программа.
>- также есть и другие команды
>- `make clean` - удаляет все исполняемые файлы, то есть *.out
>- `make cmp` - компилирует указанный файл
>- `make debug` - дебаг

CC = gcc - компилятор \ 
CFLAGS = -std=c99 -Wall -Werror - флаги \ 
DEBUG = gdb - компилятор gdb \
FILEOUT = queue.out -исполняемый файл \
SOURCES = queue.c main.c -файл основной программы(main.c) и файла библиотеки очереди(queue.c)