#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct element {
    int col;
    int number;
    int next_index;
} element;


bool check_diag(element* arr, int* indexes, int k) {
    int col = 1;
    for(int i = 0; i < k; i++) {
        element tmp = arr[i];
        if (tmp.next_index != 0 && tmp.col != col) {
            return false;
        }
        col++;
    }
    return true;
    
}

void task(element* arr, int* arr_index, int k, int size_col) {
    int need_rows[size_col];
    int index = 0;
    for (int i = 0; i < size_col; i++) {
        need_rows[i] = 0;
    }
    //printf("1\n");
    for (int i = 0; i < size_col; i++) {
        if (arr_index[i] != 0) {
            //printf("2\n");
            int tmp_sum = 0;
            element tmp;
            do {
                if (index == k) {
                    break;
                }
                tmp = arr[index];
                //printf("elem: %d, next_index: %d\n", tmp.number, tmp.next_index);
                tmp_sum += tmp.number;
                index++;
                if (tmp.next_index == 0 || tmp.next_index == -1) {
                    break;
                }
            } while (true);
            //printf("3\n");
            need_rows[i] = tmp_sum;
            tmp_sum = 0;
        }
    }
    int tmp_max = 0;
    for (int i = 0; i < size_col; i++) {
        if (tmp_max < need_rows[i]) {
            tmp_max = need_rows[i];
        }
    }
    for (int i = 0; i < size_col; i++) {
        if (tmp_max == need_rows[i]) {
            printf("Строка %d, сумма элементов = %d\n", (i + 1), tmp_max);
        }
    }

}

void print_matrix(element* arr, int* arr_index, int size_col, int size_row, int k) {
    int col = 1;
    int row = 1;
    int index1 = 0;
    int index2 = 0;
    int num_elements = size_col * size_row;
    if (!check_diag(arr, arr_index, k)) {
        for (int i = 0; i < num_elements; i++) {
            element tmp;
            if (index1 == k) {
                tmp = arr[index1 - 1];
            } else {
               tmp = arr[index1]; 
            }
            int ind = arr_index[index2];
            if (tmp.col == col && ind == row && index1 != k) {
                printf("%d ", tmp.number);
                index1++;
                //index2++; 
            } else {
                printf("0 ");
            }
            col++;
            if (col == size_row + 1) {
                row++;
                index2++; 
                col = 1;
                printf("\n");
            }

        }
    } else {
        bool printed = false;
        for (int i = 0; i < num_elements; i++) {
            element tmp;
            if (index1 == k) {
                tmp = arr[index1 - 1];
            } else {
               tmp = arr[index1]; 
            }
            int ind = arr_index[index2];
            if (tmp.col == col && ind == row && printed == false && index1 != k) {
                printf("%d ", tmp.number);
                index1++;
                printed = true;
            } else {
                printf("0 ");
            }
            col++;
            if (col == size_row + 1) {
                row++;
                index2++; 
                col = 1;
                printed = false;
                printf("\n");
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл!\n");
        return 1;
    }

    int size_col = -1; // размер колонны
    int size_row = -1; // размер строки
    fscanf(file, "%d %d", &size_col, &size_row);

    int index_row[size_col];
    for (int i = 0; i < size_col; i++) {
        index_row[i] = 0; // Инициализация нулями
    }

    int k = 0;
    int scan_num = -1;
    bool is_null_row = true;
    int col = 1;
    int row = 1;
    int i = 0;
    bool scanned = false;
    while (fscanf(file, "%d", &scan_num) != EOF) {
        if (scan_num != 0) {
            k++;
            if(scanned == false) {
                index_row[i] = row;
                i++;
                scanned = true;
            }
            is_null_row = false;
        }
        col++;
        if (col == size_row + 1) {
            row++;
            col = 1;
            if (is_null_row) {
                index_row[i] = 0;
                i++;
            }
            scanned = false;
            is_null_row = true;
        }
    } 
    fseek(file, 0, SEEK_SET);
    col = 1;
    row = 1;
    element array_values[k];
    int index = 0;
    fscanf(file, "%d %d", &size_col, &size_row);
    bool start = false;
    while (fscanf(file, "%d", &scan_num) != EOF) {
        if (start && !is_null_row) {
            array_values[index - 1].next_index = col;
        }
        if (scan_num != 0) {
            is_null_row = false;   
            array_values[index].col = col;
            array_values[index].number = scan_num;
            index++;
        }
        col++;
        if (!start) {
            start = true;
        }
        if (col == size_row + 1) {
            if (!is_null_row) {
                array_values[index - 1].next_index = 0;
            }
            row++;
            col = 1;
            is_null_row = true;
        }
    }
    array_values[index - 1].next_index = -1;
    fclose(file);
    printf("Исходная матрица\n");
    print_matrix(array_values, index_row, size_col, size_row, k);
    printf("\n");
    task(array_values, index_row, k, size_col);

    return 0;
}
