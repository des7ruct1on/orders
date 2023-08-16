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
    printf("|  Ключ        | Значение                    |\n");
    printf("|============================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(v, i);
        printf("| %12f | %-41s \n", tmp.key, tmp.string);
    }
    printf("|============================================|\n");
}

void swap(value* x, value* y) {
    value temp = *x;
    *x = *y;
    *y = temp;
}

void sortShake(vector* v) {
    int left = 0;
    int right = v->size - 1;
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;

        for (int i = left; i < right; i++) {
            if (v->data[i].key > v->data[i + 1].key) {
                swap(&v->data[i], &v->data[i + 1]);
                swapped = true;
            }
        }

        right--;

        for (int i = right; i > left; i--) {
            if (v->data[i - 1].key > v->data[i].key) {
                swap(&v->data[i - 1], &v->data[i]);
                swapped = true;
            }
        }

        left++;
    }
}

value binarySearch(vector* table, float key) {
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
