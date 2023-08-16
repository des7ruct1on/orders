#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

void printMatrix(vector* values, vector* indexCol, vector* indexRow, int sizeCol, int sizeRow) {
    int countPrinted = 0;
    int indexVector = 0;

    for (int i = 1; i <= sizeRow; i++) {
        for (int j = 1; j <= sizeCol; j++) {
            int indRow = printVector(indexRow, indexVector);
            int indCol = printVector(indexCol, indexVector);
            int value = printVector(values, indexVector);
            
            if (i == indRow && j == indCol) {
                printf("%d ", value);
                indexVector++;
            } else {
                printf("0 ");
            }
            countPrinted++;

            if (countPrinted % sizeCol == 0) {
                printf("\n");
            }
        }
    }
}

void multiplyMatrixes(vector* values1, vector* indexRow1, vector* indexCol1, vector* values2, vector* indexRow2, vector* indexCol2, int sizeCol1, int sizeRow1, int sizeCol2, int sizeRow2) {
    if (sizeCol1 != sizeRow2) {
        printf("Матрицы невозможно умножить!\n");
        return;
    }
    vector* resValues = malloc(sizeof(vector));//выделяем память под результирующий вектор
    vector* resIndexRow = malloc(sizeof(vector));
    vector* resIndexCol = malloc(sizeof(vector));
    createVector(resValues, 0);
    createVector(resIndexRow, 0);
    createVector(resIndexCol, 0);
    int size1 = sizeVector(values1);
    int size2 = sizeVector(values2);
    int i = 0;
    int sizeRowRes = sizeRow1;//определяем размеры результирующей матрицы
    int sizeColRes = sizeCol2;
    int res = 0;
    bool isLeftVector = false;
    if (sizeCol1 == 1) {//проверка на расположение вектора-столбца слева
        isLeftVector = true;
    }   
    int count = 0;//счетчик для записи
    while (i < size1) {
        if (isLeftVector) {//если вектор слева
            int value1 = printVector(values1, i);
            int indRow1 = printVector(indexRow1, i);
            for (int k = 0; k < size2; k++) {
                int indCol2 = printVector(indexCol2, k);
                int value2 = printVector(values2, k);
                res = value1 * value2;
                resizeVector(resValues, sizeVector(resValues) + 1);
                resizeVector(resIndexCol, sizeVector(resIndexCol) + 1);
                resizeVector(resIndexRow, sizeVector(resIndexRow) + 1);
                writeVector(resValues, count, res);
                writeVector(resIndexCol, count, indCol2);
                writeVector(resIndexRow, count, indRow1);
                count++;
            }
            i++;
        } else {//если вектор справа
            int indCol1 = printVector(indexCol1, i);
            int indRow1 = printVector(indexRow1, i);
            int value1 = printVector(values1, i);
            for (int k = 0; k < size2; k++) {
                int indCol2 = printVector(indexCol2, k);
                int indRow2 = printVector(indexRow2, k);
                if (indCol1 == indRow2) {
                    int value2 = printVector(values2, k);
                    res += value1 * value2;
                    
                    if (k == size2 - 1) {
                        resizeVector(resValues, sizeVector(resValues) + 1);
                        resizeVector(resIndexCol, sizeVector(resIndexCol) + 1);
                        resizeVector(resIndexRow, sizeVector(resIndexRow) + 1);
                        writeVector(resValues, count, res);
                        writeVector(resIndexCol, count, indCol2);
                        writeVector(resIndexRow, count, indRow1);
                        res = 0;
                        count++;
                    }
                }
            }
            i++;
        }
    }
    printf("Результат умножения: \n");
    printMatrix(resValues, resIndexCol, resIndexRow, sizeColRes, sizeRowRes);
    printf("\nЧисло ненулевых элементов: %d\n", sizeVector(resValues));
    destroyVector(resValues);
    destroyVector(resIndexRow);
    destroyVector(resIndexCol);
    free(resValues);
    free(resIndexRow);
    free(resIndexCol);
}




int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Используйте: %s <FILE1> <FILE2>\n", argv[0]);
        return 1;
    }
    int sizeCol1;//размер 1-ого вектора(разреженной матрицы) - столбцы
    int sizeRow1;//размер 1-ого вектора - строки
    int sizeCol2;//размер 2-ого вектора - столбцы
    int sizeRow2;//размер 2-ого вектора - строки
    printf("Вас приветствует программа по обработке разряженных матриц!\n");
    //открытие файлов
    FILE* inputMatrix = fopen(argv[1], "r");//файл, с которым будем работать
    if (inputMatrix == NULL) { // проверка на возможность открытия файла
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    //считываем первый файл
    fscanf(inputMatrix, "%d %d", &sizeRow1, &sizeCol1);//считываем размер из файла
    vector* rowIndexMatrix = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* colIndexMatrix = malloc(sizeof(vector));//выделяем память под вектор значений
    vector* valuesMatrix = malloc(sizeof(vector));//выделяем память под вектор значений
    int indexRow1 = 1;
    int indexColumn1 = 1;
    int indexVector1 = 0;
    createVector(rowIndexMatrix, 0);
    createVector(colIndexMatrix, 0);
    createVector(valuesMatrix, 0);
    while (!feof(inputMatrix)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(inputMatrix, "%d", &scanNum);
        if (scanNum != 0) {
            resizeVector(valuesMatrix, sizeVector(valuesMatrix) + 1);
            writeVector(valuesMatrix, indexVector1, scanNum);
            resizeVector(rowIndexMatrix, sizeVector(rowIndexMatrix) + 1);
            writeVector(rowIndexMatrix, indexVector1, indexRow1);
            resizeVector(colIndexMatrix, sizeVector(colIndexMatrix) + 1);
            writeVector(colIndexMatrix, indexVector1, indexColumn1);
            indexVector1++;
        }
        indexColumn1++;
        if (indexColumn1 == sizeCol1 + 1) {
            indexRow1++;
            indexColumn1 = 1;
        }
    }
    fclose(inputMatrix); //закрываем файл
    
    FILE* inputVector;//файл, с которым будем работать
    inputVector = fopen(argv[2], "r");
    if (inputVector == NULL) { // проверка на возможность открытия файла
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    //считываем второй файл
    fscanf(inputVector, "%d %d", &sizeRow2, &sizeCol2);//считываем размер из файла
    int indexRow2 = 1;
    int indexColumn2 = 1;
    int indexVector2 = 0;
    vector* rowIndexVector = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* colIndexVector = malloc(sizeof(vector));//выделяем память под вектор значений
    vector* valuesVector= malloc(sizeof(vector));//выделяем память под вектор значений
    createVector(rowIndexVector, 0);
    createVector(colIndexVector, 0);
    createVector(valuesVector, 0);
    while (!feof(inputVector)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(inputVector, "%d", &scanNum);
        if (scanNum != 0) {
            resizeVector(valuesVector, sizeVector(valuesVector) + 1);
            writeVector(valuesVector, indexVector2, scanNum);
            resizeVector(rowIndexVector, sizeVector(rowIndexVector) + 1);
            writeVector(rowIndexVector, indexVector2, indexRow2);
            resizeVector(colIndexVector, sizeVector(colIndexVector) + 1);
            writeVector(colIndexVector, indexVector2, indexColumn2);
            indexVector2++;

        }
        indexColumn2++;
        if (indexColumn2 == sizeCol2 + 1) {
            indexRow2++;
            indexColumn2 = 1;
        }
    }
    fclose(inputVector); //закрываем файл
    printf("Матрица из <%s>\n", argv[1]);
    printMatrix(valuesMatrix, colIndexMatrix, rowIndexMatrix, sizeCol1, sizeRow1);
    printf("\n");
    printf("Матрица из <%s>\n", argv[2]);
    printMatrix(valuesVector, colIndexVector, rowIndexVector, sizeCol2, sizeRow2);
    printf("\n");
    multiplyMatrixes(valuesMatrix, rowIndexMatrix, colIndexMatrix, valuesVector, rowIndexVector, colIndexVector, sizeCol1, sizeRow1, sizeCol2, sizeRow2);
    //очистка векторов
    destroyVector(valuesVector);
    destroyVector(rowIndexVector);
    destroyVector(colIndexVector);
    free(valuesVector);
    free(rowIndexVector);
    free(colIndexVector);
    destroyVector(valuesMatrix);
    destroyVector(rowIndexMatrix);
    destroyVector(colIndexMatrix);
    free(valuesMatrix);
    free(rowIndexMatrix);
    free(colIndexMatrix);
    return 0;
}
