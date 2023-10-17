#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

void print_matrix_vectors(vector* values, vector* index_col, vector* index_row) {
    int size_values, size_col, size_rows;
    size_values = size_vector(values);
    size_col = size_vector(index_col);
    size_rows = size_vector(index_row);
    printf("\nvalues: ");
    for (int i = 0; i < size_values; i++) {
        printf("%d ", print_vector(values, i));
    }
    printf("\ncolumns: ");
    for (int i = 0; i < size_col; i++) {
        printf("%d ", print_vector(index_col, i));
    }
    printf("\nrows: ");
    for (int i = 0; i < size_rows; i++) {
        printf("%d ", print_vector(index_row, i));
    }
    printf("\n");
}

void print_matrix(vector* values, vector* index_col, vector* index_row, int size_col, int size_row) {
    int count = 0;
    int index_help = 0;

    for (int i = 1; i <= size_row; i++) { // начинаем c i=j=1 в соответствии с матем индексами матрицы
        for (int j = 1; j <= size_col; j++) {
            int ind_row = print_vector(index_row, index_help);
            int ind_col = print_vector(index_col, index_help);
            int value = print_vector(values, index_help);
            
            if (i == ind_row && j == ind_col) {
                printf("%d ", value);
                index_help++;
            } else {
                printf("0 ");
            }
            count++;

            if (count % size_col == 0) {
                printf("\n");
            }
        }
    }
}

// функция проверки на диагональность (проверяем i = j)
bool check_diag(vector* row, vector* col) {
    int size = size_vector(row);
    for(int i = 0; i < size; i++) {
        int _row = print_vector(row, i);
        int _col = print_vector(col, i);
        if (_row != _col) {
            return false;
        } else {
            continue;
        }
    }
    return true;
}

//функция умножения матриц
void multiply_matrixes(vector* row1, vector* col1, vector* val1, vector* row2, vector* col2, vector* val2, int size_col1, int size_row1, int size_col2, int size_row2) {
    if (size_col1 != size_row2) { // проверка на возможность умножения
        printf("Матрицы невозможно умножить!\n");
        return;
    }

    // создаем результирующие векторы
    vector* res_col = malloc(sizeof(vector));
    vector* res_row = malloc(sizeof(vector));
    vector* res_val = malloc(sizeof(vector));
    create_vector(res_col, 0);
    create_vector(res_row, 0);
    create_vector(res_val, 0);

    // размера результ матрицы
    int size_col_res = size_col2;
    int size_row_res = size_row1;

    // тело цикла
    int i = 0;

    // храним нужные строки и столбцы для правильной итерации
    int need_col = 1;
    int need_row = 1;

    // индекс для записи в вектор
    int index = 0;

    // флаг для перехода на след строку
    bool next = false;
    while(true) {
        // условие остановки
        if (i == size_vector(val1) && need_col == size_col2 + 1) {
            break;
        }
        // прошли все колонны
        if (need_col == size_col2 + 1) {
            need_col = 1;
            need_row++;
            i = 0;

        }
        //printf("_____need row: %d, need col: %d\n", need_row, need_col);
        if (next) { // если нужно перейти на некст строку, то снова обнуляем i
            i = 0;
            next = false;
        }

        // вытаскиваем значения первой матрицы
        int _val1 = print_vector(val1, i);
        int _row1 = print_vector(row1, i);
        int _col1 = print_vector(col1, i);
        //printf("val1: %d, col1: %d, row1: %d\n", _val1, _col1, _row1);
        if (_row1 != need_row) { // если вытащили не нужные, то просто скипаем их
            i++;
            continue;
        }
        int _col2;
        int _row2;
        int _val2;
        int _res_col;

        // сумма-результат умножения делаем static, чтоб сохранялась при некст итерации
        static int mult = 0;
        
        // вытаскиваем значения из некст матрицы
        for (int j = 0; j < size_vector(val2); j++) {
            _col2 = print_vector(col2, j);
            _row2 = print_vector(row2, j);
            _val2 = print_vector(val2, j);
            //printf("  val2: %d, col2: %d, row2: %d\n", _val2, _col2, _row2);

            // нашли нужное
            if (_col2 == need_col && _col1 == _row2) { 
                mult += _val1 *  _val2;
                _res_col = _col2;
                //printf("        %d X %d\n", _val1, _val2);
                //i++;
                break;
            }
        }

        // проверка на то, что некст элемент уже из другой строки, тем самым не нужно увеличивать mult
        int tmp_row = print_vector(row1, i + 1);
        
        if (tmp_row != _row1 ) {
            //printf("        new val: %d , row: %d, col: %d\n", mult, _row1, _res_col);
            
            // записываем в матрицу новое НЕнулевое значение
            if (mult != 0) {
                resize_vector(res_col, size_vector(res_col) + 1);
                resize_vector(res_val, size_vector(res_val) + 1);
                resize_vector(res_row, size_vector(res_row) + 1);
                add_vector(res_col, index, _res_col);
                add_vector(res_row, index, _row1);
                add_vector(res_val, index, mult);
                index++;
            }

            //need_row++;
            need_col++;
            //i = 0;
            next = true;
            mult = 0;
        
        }
        i++;


    }
    printf("\n");

    // вывод матрицы
    print_matrix_vectors(res_val, res_col, res_row);
    printf("Матрица-результат:\n");
    print_matrix(res_val, res_col, res_row, size_col_res, size_row_res);

    // проверка на диагональность
    bool diag = check_diag(res_row, res_col);
    if (diag && size_vector(res_val) != 1) {
        printf("Матрица является диагональной\n");
    } else {
        printf("Матрица НЕ является диагональной\n");
    }
    delete_vector(res_val);
    delete_vector(res_col);
    delete_vector(res_row);
    free(res_val);
    free(res_col);
    free(res_row);

} 

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Используйте: %s <FILE1> <FILE2>\n", argv[0]);
        return 1;
    }
    int size_col1;//размер 1-ой матрицы (столбец)
    int size_row1;//размер 1-ой матрицы (строка)
    int size_col2;//размер 2-ой матрицы (столбец)
    int size_row2;//размер 2-ой матрицы (строка)
    printf("Вас приветствует программа по обработке разряженных матриц!\n");
    //открытие файлов
    FILE* input1 = fopen(argv[1], "r");//файл, с которым будем работать

    // проверка на возможность открытия файла
    if (input1 == NULL) { 
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    //считываем первый файл
    fscanf(input1, "%d %d", &size_row1, &size_col1);//считываем размер из файла

    //выделяем память под векторы матрицы
    vector* row_index_matrix = malloc(sizeof(vector));
    vector* col_index_matrix = malloc(sizeof(vector));
    vector* values_matrix = malloc(sizeof(vector));
    int index_row1 = 1;
    int index_col1 = 1;
    int index_help1 = 0;
    create_vector(row_index_matrix, 0);
    create_vector(col_index_matrix, 0);
    create_vector(values_matrix, 0);
    while (!feof(input1)) { //пока файл не пуст
        int num;
        fscanf(input1, "%d", &num);
        if (num != 0) {
            resize_vector(values_matrix, size_vector(values_matrix) + 1);
            add_vector(values_matrix, index_help1, num);
            resize_vector(row_index_matrix, size_vector(row_index_matrix) + 1);
            add_vector(row_index_matrix, index_help1, index_row1);
            resize_vector(col_index_matrix, size_vector(col_index_matrix) + 1);
            add_vector(col_index_matrix, index_help1, index_col1);
            index_help1++;
        }
        index_col1++;
        if (index_col1 == size_col1 + 1) { // конец строки
            index_row1++;
            index_col1 = 1;
        }
    }
    fclose(input1); //закрываем файл
   
    // считываем второй файл
    FILE* input2 = fopen(argv[2], "r"); //файл, с которым будем работать

    // проверка на возможность открытия файла
    if (input2 == NULL) { 
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    //считываем первый файл
    fscanf(input2, "%d %d", &size_row2, &size_col2);//считываем размер из файла

    //выделяем память под векторы матрицы
    vector* row_index_matrix2 = malloc(sizeof(vector));
    vector* col_index_matrix2 = malloc(sizeof(vector));
    vector* values_matrix2 = malloc(sizeof(vector));
    int index_row2 = 1;
    int index_col2 = 1;
    int index_help2 = 0;
    create_vector(row_index_matrix2, 0);
    create_vector(col_index_matrix2, 0);
    create_vector(values_matrix2, 0);
    while (!feof(input2)) { //пока файл не пуст
        int num;
        fscanf(input2, "%d", &num);
        if (num != 0) {
            resize_vector(values_matrix2, size_vector(values_matrix2) + 1);
            add_vector(values_matrix2, index_help2, num);
            resize_vector(row_index_matrix2, size_vector(row_index_matrix2) + 1);
            add_vector(row_index_matrix2, index_help2, index_row2);
            resize_vector(col_index_matrix2, size_vector(col_index_matrix2) + 1);
            add_vector(col_index_matrix2, index_help2, index_col2);
            index_help2++;
        }
        index_col2++;
        if (index_col2 == size_col2 + 1) { // конец строки
            index_row2++;
            index_col2 = 1;
        }
    }
    fclose(input2); //закрываем файл
    print_matrix_vectors(values_matrix, col_index_matrix, row_index_matrix);
    print_matrix_vectors(values_matrix2, col_index_matrix2, row_index_matrix2);
    printf("Матрица из [%s]\n", argv[1]);
    print_matrix(values_matrix, col_index_matrix, row_index_matrix, size_col1, size_row1);
    printf("\n");
    printf("Матрица из [%s]\n", argv[2]);
    print_matrix(values_matrix2, col_index_matrix2, row_index_matrix2, size_col2, size_row2);
    printf("\n");
    multiply_matrixes(row_index_matrix, col_index_matrix, values_matrix, row_index_matrix2, col_index_matrix2, values_matrix2, size_col1, size_row1, size_col2, size_row2);
    //очистка векторов
    delete_vector(values_matrix);
    delete_vector(row_index_matrix);
    delete_vector(col_index_matrix);
    free(values_matrix);
    free(row_index_matrix);
    free(col_index_matrix);
    delete_vector(values_matrix2);
    delete_vector(row_index_matrix2);
    delete_vector(col_index_matrix2);
    free(values_matrix2);
    free(row_index_matrix2);
    free(col_index_matrix2);
    return 0;
}
