#include "vector.h"

void createVector(vector* v, int size) { //функция создания вектора
    v->size = size;
    v->value = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        v->value[i] = 0;
    }
}


bool empty(vector* v) { //функция проверки на пустоту
    return v->size == 0;
}

int sizeVector(vector* v) {//функция возвращения размера вектора
    return v->size;
}

int loadVector(vector* v, int i) {//функция вывода значения вектора
    if ((i >= 0) && (i < v->size)) {//провека на принадлежность промежутку размера
        return v->value[i];
    } else { //иначе выводим результат не правильный
        return 99999;
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

bool equal(vector* l, vector* r) {//функция проверки на равенство двух векторов
    if (l->size != r->size) {
        return false;
    } else {
        for (int i = 0; i < l->size; i++) {
            if (l->value[i] != r->value[i]) {
                return false;
            }
        }
        return true;
    }
}


void destroyVector(vector* v) {//функция очистки вектора 
    v->size = 0;
    free(v->value);
    v->value = NULL;
}

void destroyElement(vector* vIndex, vector* v, int i) {//функция перезаписи элемента вектора на 0
    writeVector(v, i, 0);
    
}

void checkNullElements(vector* v, vector* vIndex) {//функция проверки на нулевой элемент
    int i = 0;
    int j = 1;
    for(i = 0; i < sizeVector(vIndex); i++, j++) {
        if(loadVector(vIndex, i) == 0) { //если найден пустой элемент 
            writeVector(vIndex, i, loadVector(vIndex, j));//перезаписываем на место нулевого следующий
            writeVector(v, i, loadVector(v, j));//так же делаем со значением
            writeVector(vIndex, j, 0);//обнуляем взятый
            writeVector(v, j, 0);
        }

    }

}
