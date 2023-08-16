#include "vector.h"

void createVector(vector* v, int size) { //функция создания вектора
    v->size = size;
    v->value = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        v->value[i] = 0;
    }
}


bool emptyVector(vector* v) { //функция проверки на пустоту
    return v->size == 0;
}

int sizeVector(vector* v) {//функция возвращения размера вектора
    return v->size;
}

int printVector(vector* v, int i) {//функция вывода значения вектора
    if ((i >= 0) && (i < v->size)) {//провека на принадлежность промежутку размера
        return v->value[i];
    } else { //иначе выводим результат не правильный
        return INT_MAX;
    }
}

void writeVector(vector* v, int i, int value) {//функция записи в вектор
    if((i >= 0) && (i < v->size)) {//если значение i принадлежит отрезку вектора
        v->value[i] = value;
    }
}

void resizeVector(vector* v, int size) {//функция изменения размера
    int* new_values = (int*)realloc(v->value, size * sizeof(int));
    v->value = new_values;
    v->size = size;
    for (int i = v->size; i < size; i++) {
        v->value[i] = 0;
    }
}

void destroyVector(vector* v) {//функция очистки вектора 
    v->size = 0;
    free(v->value);
    v->value = NULL;
}
