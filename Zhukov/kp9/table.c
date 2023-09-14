#include "table.h"

void create_vector(vector* v, int size) {//функция создания вектора
    v->size = size;
    v->data = (value*)malloc(size * sizeof(value));
    for (int i = 0; i < size; i++) {//заполняем нулями 
        strcpy(v->data[i].key, "");
        strcpy(v->data[i].string, "");
    }
}

bool empty_vector(vector* v) {//проверка на пустоту
    return v->size == 0;
}

int size_vector(vector* v) {//функция вывода размера вектора
    return v->size;
}

value print_vector(vector* v, int i) {//функция вывода значения вектора
    value empty_value;
    strcpy(empty_value.key, "");
    strcpy(empty_value.string, "");

    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return empty_value;
    }
}

void add_vector(vector* v, int i, value val) {//функция записи в вектор
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

void resize_vector(vector* v, int size) {//функция увеличения размера вектора
    value* new_values = (value*)realloc(v->data, size * sizeof(value));
    v->data = new_values;
    v->size = size;

    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            strcpy(v->data[i].key, "");
            strcpy(v->data[i].string, "");
        }
    }
}

void destroy_vector(vector* v) {//функция удаления вектора
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

void print_table(vector* v) { //функция вывода таблицы
    int size = size_vector(v);
    printf("|=====================================|\n");
    printf("|  Ключ        | Строка               |\n");
    printf("|=====================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = print_vector(v, i);
        printf("| %12s | %-41s \n", tmp.key, tmp.string);
    }
    printf("|=====================================|\n");
}


value binary_search(vector* table, char* key, bool reverse_sorted) {//бинарный поиск
    int left;
    int right;
    int middle;
    value def = { "", "" }; //если ничего не найдется, то вернем пустой объект
    if (reverse_sorted == false) {//если таблица отсортирована по возрастанию
        left = 0;
        right = size_vector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;
            if (strcmp(key, table->data[middle].key) < 0) {
                right = middle - 1;
            } else if (strcmp(key, table->data[middle].key) > 0) {
                left = middle + 1;
            } else if (strcmp(key, table->data[middle].key) == 0) {
                return table->data[middle];
            }
        }
    } else { //если отсортирована по убыванию
        left = 0;
        right = size_vector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;
            if (strcmp(key, table->data[middle].key) > 0) {
                left = middle + 1;
            } else if (strcmp(key, table->data[middle].key) < 0) {
                right = middle - 1;
            } else if (strcmp(key, table->data[middle].key) == 0) {
                return table->data[middle];
            }
        }
    }
    return def;

}

void bubble_sort(vector* v) {//функция пузырьковой сортировки 
    int i, j;
    int n = size_vector(v);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(v->data[j].key, v->data[j + 1].key) > 0) {
                // Обмен значениями
                value temp = v->data[j];
                v->data[j] = v->data[j+1];
                v->data[j+1] = temp;
            }
        }
    }
}

bool check_sort_table(vector* table) { // функция проверки на отсортированность таблицы
    int size = size_vector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = print_vector(table, i);
        value b = print_vector(table, i + 1);

        if (strcmp(a.key, b.key) > 0) { //если нарушен порядок
            return false;
        }
    }

    return true;
}

bool check_sort_table_reverse(vector* table) {// функция проверки на убывание значений таблицы
    int size = size_vector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = print_vector(table, i);
        value b = print_vector(table, i + 1);

        if (strcmp(a.key, b.key) < 0) { // если нарушен порядок
            return false;
        }
    }

    return true;
}
