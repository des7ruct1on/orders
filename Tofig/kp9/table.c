#include "table.h"

void createVector(vector* v, int size) {
    v->size = size;
    v->data = (value*)malloc(size * sizeof(value));
    for (int i = 0; i < size; i++) {
        v->data[i].key = 0;
        strcpy(v->data[i].string, "");
    }
}

bool empty(vector* v) {
    return v->size == 0;
}

int sizeVector(vector* v) {
    return v->size;
}

value loadVector(vector* v, int i) {
    value emptyValue;
    emptyValue.key = 0;
    strcpy(emptyValue.string, "");

    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return emptyValue;
    }
}

void writeVector(vector* v, int i, value val) {
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

void resizeVector(vector* v, int size) {
    value* new_values = (value*)realloc(v->data, size * sizeof(value));
    v->data = new_values;
    v->size = size;

    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            v->data[i].key = 0;
            strcpy(v->data[i].string, "");
        }
    }
}

void destroyVector(vector* v) {
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

void printTable(vector* v) {
    int size = sizeVector(v);
    printf("|============================================|\n");
    printf("|  Ключ        | Значение                          |\n");
    printf("|============================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(v, i);
        printf("| %12d | %-41s \n", tmp.key, tmp.string);
    }
    printf("|============================================|\n");
}

value binarySearch(vector* table, int key) {
    int left = 0;
    int right = sizeVector(table) - 1;
    int middle;
    value def = { 0, "" }; //если ничено не найдем, то вернем пустой объект
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

    return def;

}
void vectorReverse(vector* a, vector* b) { //функция записи реверс вектора
    int size = sizeVector(a);
    int pos = 0;
    for(int i = size - 1; i >= 0; i--) {
        value tmp = loadVector(a, i);
        writeVector(b, pos, tmp);
        pos++;
    }
}

bool checkSortTable(vector* table) { // функция проверки на отсортированность таблицы
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = loadVector(table, i);
        value b = loadVector(table, i + 1);

        if (a.key > b.key) { //если нарушен порядок
            return false;
        }
    }

    return true;
}

bool checkSortTableDescending(vector* table) {// функция проверки на убывание(обратные порядок)
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = loadVector(table, i);
        value b = loadVector(table, i + 1);

        if (a.key < b.key) { // если нарушен порядок
            return false;
        }
    }

    return true;
}

void insertionSort(vector* table) {
    int size = sizeVector(table);

    for (int i = 1; i < size; i++) {
        value key = loadVector(table, i);
        int j = i - 1;

        while (j >= 0 && loadVector(table, j).key > key.key) {
            writeVector(table, j + 1, loadVector(table, j));
            j--;
        }

        writeVector(table, j + 1, key);
    }
}