#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

int plusIndex(int i, int j) { //функция создания индекса элемента матрицы
    int checkLen;
    int len = 0;
    checkLen = j;
    while (checkLen) { //вычисляем длину правого индекса(столбца)
        checkLen /= 10;
        len++;
    }
    return i * pow(10, len) + j;
}

int reverseNumber(int number) { //функция инверсии числа, нужна для проверки при умножении
    int reversedNumber = 0;

    while (number != 0) {
        int remainder = number % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        number /= 10;
    }

    return reversedNumber;
}


void printMatrix(vector* v, vector* vIndex, int sizeRow, int sizeCol) { //функция вывода матрицы
    checkNullElements(v, vIndex);//проверяем на нулевые индексы
    int i = 1;
    int j = 1;
    int check = 0;
    int countNums = sizeRow * sizeCol; //количество элементов
    for (int k = 0; k < countNums; k++) {//цикл пока не вывели все элементы
        if (k % sizeRow == 0) {//если вывели всю строку, то печатаем перенос
            printf("\n");
        }
        if (loadVector(vIndex, check) == plusIndex(i, j)) {//если индекс перебора совпал с индексом не нулевого элемента
            printf("%d\t", loadVector(v, check));//выводим его
            check++;//увеличиваем счетчик вывода таких элементов
        }
        else {
            printf("0\t");//печатаем ноль, так как матрица разряженна
        }
        if (j == sizeRow) {//если столбцы закончилась, то увеличиваем счетчик строк
            j = 0;//обнуляем счетчик столбцов
            i++;
        }
        j++;//увеличиваем счетчик прохода по столбцу
    }
}

void countNotNullElements(vector* values) {
    int count = 0;
    for (int i = 0; i < sizeVector(values); i++) {
        int tmp = loadVector(values, i);
        if (tmp > 0) {
            count++;
        }
    }
    printf("\nКоличество ненулевых элементов: %d\n", count);
}


void multiply(vector* vIndex1, vector* vValues1, vector* vIndex2, vector* vValues2, int sizeCol1, int sizeRow1, int sizeCol2, int sizeRow2) {
    vector* resIndex = malloc(sizeof(vector)); //выделяем память на вектор-результат
    vector* resValues = malloc(sizeof(vector));
    createVector(resIndex, 0); //создаем вектор
    createVector(resValues, 0);
    int size1 = sizeVector(vIndex1);
    int size2 = sizeVector(vIndex2);
    int i = 0;
    int j = 0;
    int sizeRowRes;
    int sizeColRes;
    int res = 0;
    bool isLeftVector = false;
    if (sizeRow1 < sizeRow2) { //если вектор-столбец слева -> результатом будет матрица
        sizeRowRes = sizeRow2;
        sizeColRes = sizeCol1;
        isLeftVector = true;
    } else  { //иначе - число
        sizeRowRes = sizeRow2;
        sizeColRes = sizeCol1;
        isLeftVector = false;
    }
    int count = 0; //счетчик для записи в вектор
    while(i < size1 && j < size2) {
        int index1 = loadVector(vIndex1, i); //расщепляем индексы
        int index2 = loadVector(vIndex2, j);
        int indRow1 = index1 / 10;
        int indCol2 = index2 % 10;
        if (isLeftVector) { //если столбец слева
            int value1 = loadVector(vValues1, i);
            for (int k = 0; k < size2; k++) {
                int value2 = loadVector(vValues2, k);
                res = value1 * value2;
                indCol2 = loadVector(vIndex2, k) % 10;
                resizeVector(resValues, sizeVector(resValues) + 1);
                resizeVector(resIndex, sizeVector(resIndex) + 1);
                writeVector(resValues, count, res);
                writeVector(resIndex, count, plusIndex(indRow1, indCol2));
                count++;
            }
            i++;
        } else { //если столбец справа
            int value1 = loadVector(vValues1, i);
            for (int k = 0; k < size2; k++) {
                index2 = loadVector(vIndex2, k);
                if((index1 == index2) || (index1 == reverseNumber(index2))) {
                    res += value1 * loadVector(vValues2, k);
                }
            }
            i++;
            j++;
        }
    }
    
    if (!isLeftVector) { //если вектор-столбец был справа, то нужно записать результат 
        resizeVector(resValues, sizeVector(resValues) + 1);
        resizeVector(resIndex, sizeVector(resIndex) + 1);
        writeVector(resIndex, 0, 11);
        writeVector(resValues, 0, res);
    }
    printf("Результат умножения:\n");
    printMatrix(resValues, resIndex, sizeRowRes, sizeColRes);
    printf("\n");
    countNotNullElements(resValues);
    destroyVector(resIndex); //очищаем память
    destroyVector(resValues);
    free(resIndex);
    free(resValues);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Используйте: %s <filename1> <filename2>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1]; //файл для 1-ого вектора
    const char* filename2 = argv[2]; //файл для 2-ого вектора
    vector* indexMatrix1 = malloc(sizeof(vector));//выделяем память под вектор1 индексов
    vector* valuesMatrix1 = malloc(sizeof(vector));//выделяем память под вектор1 значений
    vector* indexMatrix2 = malloc(sizeof(vector));//выделяем память под вектор2 индексов
    vector* valuesMatrix2 = malloc(sizeof(vector));//выделяем память под вектор2 значений
    int sizeCol1;//размер 1-ого вектора(разреженной матрицы) - столбцы
    int sizeRow1;//размер 1-ого вектора - строки
    int sizeCol2;//размер 2-ого вектора - столбцы
    int sizeRow2;//размер 2-ого вектора - строки
    FILE* input;//файл, с которым будем работать
    FILE* input2;
    printf("Вас приветствует программа по обработке разряженных матриц!\n");
    input = fopen(filename, "r");
    if (input == NULL) { // проверка на возможность открытия файла
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    fscanf(input, "%d %d", &sizeCol1, &sizeRow1);//считываем размер из файла
    //считываем матрицу из файла
    createVector(indexMatrix1, 1);
    createVector(valuesMatrix1, 1);
    int indexRow1 = 1;
    int indexColumn1 = 1;
    int indexVector1 = 0;
    while (!feof(input)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(input, "%d", &scanNum);
        if (scanNum != 0) {
            writeVector(valuesMatrix1, indexVector1, scanNum);
            resizeVector(valuesMatrix1, sizeVector(valuesMatrix1) + 1);
            writeVector(indexMatrix1, indexVector1, plusIndex(indexColumn1, indexRow1));
            resizeVector(indexMatrix1, sizeVector(indexMatrix1) + 1);
            indexVector1++;

        }
        indexRow1++;
        if (indexRow1 == sizeRow1 + 1) {
            indexColumn1++;
            indexRow1 = 1;
        }
    }
    resizeVector(indexMatrix1, sizeVector(indexMatrix1) - 1);
    resizeVector(valuesMatrix1, sizeVector(valuesMatrix1) - 1);
    fclose(input); //закрываем файл
    input2 = fopen(filename2, "r");
    if (input2 == NULL) {
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    fscanf(input2, "%d %d", &sizeCol2, &sizeRow2);//считываем размер из файла
    if ((sizeCol1 != sizeRow2) && (sizeRow1 != sizeCol2)) {
        printf("\nРазмеры не совпадают, умножение не выполнимо!\n");
        return 1;
    }
    //считываем вектор из файла
    createVector(indexMatrix2, 1);
    createVector(valuesMatrix2, 1);
    int indexRow2 = 1;
    int indexColumn2 = 1;
    int indexVector2 = 0;
    while (!feof(input2)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(input2, "%d", &scanNum);
        if (scanNum != 0) {
            writeVector(valuesMatrix2, indexVector2, scanNum);
            resizeVector(valuesMatrix2, sizeVector(valuesMatrix2) + 1);
            writeVector(indexMatrix2, indexVector2, plusIndex(indexColumn2, indexRow2));
            resizeVector(indexMatrix2, sizeVector(indexMatrix2) + 1);
            indexVector2++;

        }
        indexRow2++;
        if (indexRow2 == sizeRow2 + 1) {
            indexColumn2++;
            indexRow2 = 1;
        }
    }
    resizeVector(indexMatrix2, sizeVector(indexMatrix2) - 1);
    resizeVector(valuesMatrix2, sizeVector(valuesMatrix2) - 1);
    fclose(input2); //закрываем файл
    printf("\nИсходная матрица равна:\n");
    printMatrix(valuesMatrix1, indexMatrix1, sizeRow1, sizeCol1);
    printf("\n");
    printf("\nИсходная вектор равен:\n");
    printMatrix(valuesMatrix2, indexMatrix2, sizeRow2, sizeCol2);
    printf("\n");
    multiply(indexMatrix1, valuesMatrix1, indexMatrix2, valuesMatrix2, sizeCol1, sizeRow1, sizeCol2, sizeRow2);
    destroyVector(valuesMatrix1);
    destroyVector(valuesMatrix2);
    destroyVector(indexMatrix1);
    destroyVector(indexMatrix2);
    free(valuesMatrix1);
    free(valuesMatrix2);
    free(indexMatrix1);
    free(indexMatrix2);
    
    return 0;

}

