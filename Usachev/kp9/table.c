#include "table.h"

void createVector(vector* v, int size) {//функция создания вектора
    v->size = size;
    v->data = (value*)malloc(size * sizeof(value));
    for (int i = 0; i < size; i++) {//заполняем нулями 
        v->data[i].key = 0;
        strcpy(v->data[i].string, "");
    }
}

bool emptyVector(vector* v) {//проверка на пустоту
    return v->size == 0;
}

int sizeVector(vector* v) {//функция вывода размера вектора
    return v->size;
}

value printVector(vector* v, int i) {//функция вывода значения вектора
    value emptyValue;
    emptyValue.key = 0;
    strcpy(emptyValue.string, "");

    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return emptyValue;
    }
}

void writeVector(vector* v, int i, value val) {//функция записи в вектор
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

void resizeVector(vector* v, int size) {//функция увеличения размера вектора
    value* newValues = (value*)realloc(v->data, size * sizeof(value));
    v->data = newValues;
    v->size = size;

    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            v->data[i].key = 0;
            strcpy(v->data[i].string, "");
        }
    }
}

void destroyVector(vector* v) {//функция удаления вектора
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

void printTable(vector* v) { //функция вывода таблицы
    int size = sizeVector(v);
    printf("|=====================================|\n");
    printf("|  Ключ        | Строка               |\n");
    printf("|=====================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = printVector(v, i);
        printf("| %12f | %-41s \n", tmp.key, tmp.string);
    }
    printf("|=====================================|\n");
}


value binarySearch(vector* table, float key, bool reverseSorted) {//бинарный поиск
    int left;
    int right;
    int middle;
    value def = { 0, "" }; //если ничего не найдется, то вернем пустой объект
    if (reverseSorted == false) {//если таблица отсортирована по возрастанию
        left = 0;
        right = sizeVector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;

            if (key < table->data[middle].key) {
                right = middle - 1;
            } else if (key > table->data[middle].key) {
                left = middle + 1;
            } else {
                return table->data[middle];
            }
        }
    } else { //если отсортирована по убыванию
        left = 0;
        right = sizeVector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;
            if (key < table->data[middle].key) {
                left = middle + 1;
            } else if (key > table->data[middle].key) {
                right = middle - 1;
            } else {
                return table->data[middle];
            }
        }
    }
    return def;

}

void bubbleSort(vector* v) {//функция пузырьковой сортировки 
    int i, j;
    int n = sizeVector(v);

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (v->data[j].key > v->data[j+1].key) {
                // Обмен значениями
                value temp = v->data[j];
                v->data[j] = v->data[j+1];
                v->data[j+1] = temp;
            }
        }
    }
}

bool checkSortTable(vector* table) { // функция проверки на отсортированность таблицы
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = printVector(table, i);
        value b = printVector(table, i + 1);

        if (a.key > b.key) { //если нарушен порядок
            return false;
        }
    }

    return true;
}

bool checkSortTableReverse(vector* table) {// функция проверки на убывание значений таблицы
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = printVector(table, i);
        value b = printVector(table, i + 1);

        if (a.key < b.key) { // если нарушен порядок
            return false;
        }
    }

    return true;
}
