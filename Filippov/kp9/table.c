#include "table.h"

//функция создания вектора
void create_vector(vector* v, int size) {
    v->size = size;
    v->data = (data*)malloc(size * sizeof(data));
    for (int i = 0; i < size; i++) {
        strcpy(v->data[i].key, "");
        strcpy(v->data[i].string, "");
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

//функция вывода элемента вектора
data get_vector(vector* v, int i) {
    data null_value;
    strcpy(null_value.key, ""); //нулевые значения
    strcpy(null_value.string, "");
    
    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return null_value;
    }
}

//функция добавления в вектор
void add_vector(vector* v, int i, data val) {
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

//функция изменения размера вектора
void resize_vector(vector* v, int size) { 
    data* new_values = (data*)realloc(v->data, size * sizeof(data));
    v->data = new_values;
    v->size = size;

    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            strcpy(v->data[i].key, "");
            strcpy(v->data[i].string, "");
        }
    }
}

//функция очистки вектора 
void destroy_vector(vector* v) {
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

//функция вывода таблицы
void print_table(vector* v) { 
    int size = size_vector(v);
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
    printf("|  Ключ  | Значение                          |\n");
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
    for (int i = 0; i < size; i++) {
        data tmp = get_vector(v, i);
        printf("| %6s | %-33s |\n", tmp.key, tmp.string);
    }
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
}

int cmp_key(data x, data y) {
    return strcmp(x.key, y.key);
}

void swap(data* x, data* y) { //функция свапа указателей 
    data tmp = *x;
    *x = *y;
    *y = tmp;
}

//бинарный поиск
data binary_search(vector* table, char* key, bool reverseSorted) {
    int left;
    int right;
    int middle;
    data def = { "", "" }; //если ничего не найдется, то вернем пустой объект
    if (reverseSorted == false) {//если таблица отсортирована по возрастанию
        left = 0;
        right = size_vector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;
            
            if (strcmp(key, table->data[middle].key) < 0) {
                right = middle - 1;
            } else if (strcmp(key, table->data[middle].key) > 0) {
                left = middle + 1;
            } else {
                return table->data[middle];
            }
        }
    } else { //если отсортирована по убыванию
        left = 0;
        right = size_vector(table) - 1;
        while (left <= right) {
            middle = (left + right) / 2;
            if (strcmp(key, table->data[middle].key) < 0) {
                left = middle + 1;
            } else if (strcmp(key, table->data[middle].key) > 0) {
                right = middle - 1;
            } else {
                return table->data[middle];
            }
        }
    }
    return def;

}

// функция проверки на отсортированность таблицы
bool check_table_sorted(vector* table) { 
    int size = size_vector(table);
    for (int i = 0; i < size - 1; i++) {
        data a = get_vector(table, i);
        data b = get_vector(table, i + 1);

        if (cmp_key(a, b) > 0) { //если нарушен порядок
            return false;
        }
    }

    return true;
}

// функция проверки на обратные порядок
bool check_table_reversed(vector* table) {
    int size = size_vector(table);
    for (int i = 0; i < size - 1; i++) {
        data a = get_vector(table, i);
        data b = get_vector(table, i + 1);

        if (cmp_key(a, b) < 0) { // если нарушен порядок
            return false;
        }
    }

    return true;
}












