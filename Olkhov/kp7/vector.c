#include "vector.h"

//функция создания вектора
void create_vector(vector* v, int size) { 
    v->size = size;
    v->value = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        v->value[i] = 0;
    }
}


//функция проверки на пустоту
bool empty_vector(vector* v) { 
    return v->size == 0;
}

//функция возвращения размера вектора
int size_vector(vector* v) {
    return v->size;
}

//функция вывода значения вектора
int print_vector(vector* v, int i) {
    if ((i >= 0) && (i < v->size)) {
        return v->value[i];
    } else { //иначе выводим неправильный результат (throw)
        return INT_MAX;
    }
}

//функция записи в вектор
void add_vector(vector* v, int i, int value) {
    if((i >= 0) && (i < v->size)) {
        v->value[i] = value;
    }
}

//функция изменения размера
void resize_vector(vector* v, int size) {
    int* new_values = (int*)realloc(v->value, size * sizeof(int));
    v->value = new_values;
    v->size = size;
    for (int i = v->size; i < size; i++) {
        v->value[i] = 0;
    }
}

//функция очистки вектора 
void delete_vector(vector* v) {
    v->size = 0;
    free(v->value);
    v->value = NULL;
}
