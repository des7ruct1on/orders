#include "../headers/abiturient.h"
#include <string.h>

void initHashTable(HashTable* table) {
    for (int i = 0; i < TABLESIZE; i++) {
        table->entries[i].key[0] = '\0';
        table->entries[i].value = NULL;
    }
}

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    unsigned int p = 31;
    unsigned int len = strlen(key);

    for (unsigned int i = 0; i < len; i++) {
        hash = (hash * p) + key[i];
    }

    return hash % TABLESIZE;
}

void insertElement(HashTable* table, const char* key, abiturient* value) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        index = (index + 1) % TABLESIZE;
    }

    strcpy(table->entries[index].key, key);
    table->entries[index].value = value;
}

abiturient* findElement(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            return table->entries[index].value;
        }

        index = (index + 1) % TABLESIZE;
    }

    return NULL;
}

void removeElement(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            abiturient* removedValue = table->entries[index].value;

            // Освободить память для удаленного элемента
            abiturientFree(removedValue);

            // Установить ключ и значение в NULL для удаленного элемента
            table->entries[index].key[0] = '\0';
            table->entries[index].value = NULL;
            return;
        }

        index = (index + 1) % TABLESIZE;
    }
}


void clearHashTable(HashTable* table) {
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturientFree(table->entries[i].value);
            table->entries[i].value = NULL;
        }
        table->entries[i].key[0] = '\0';
    }
}


void pushFront(node** head, value data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void pushBack(node** head, value data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void deleteBack(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->prev->next = NULL;
    free(current);
}

void deleteFront(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    node* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    free(temp);
}

void printList(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%s %d ", current->data.subject, current->data.ball);
        current = current->next;
    }
    printf("\n");
}

void destroyList(node** head) {
    node* current = *head;
    node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int sizeList(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

char* getSurname(abiturient* s) {
    if(s == NULL) {
        return "";
    }
    return s->surname;
}

char* getInitials(abiturient* s) {
    if(s == NULL) {
        return "";
    }
    return s->initials;
}

abiturient* newAbiturient() {
    abiturient* s = malloc(sizeof(abiturient));
    if (s == NULL) {
        return NULL;
    }
    strcpy(s->surname, "");         
    strcpy(s->composition, "");
    strcpy(s->initials, "");
    strcpy(s->medal, "");
    strcpy(s->sex, "");
    s->numExams = 0;
    s->schoolNum = 0;
    s->examStats = NULL;

    return s;
}


void readFromLine(abiturient* s, char* line) {
    char subject[STRSIZE];
    int ball;
    int offset = 0;

    sscanf(line, "%s %s %s %d %s %s %d%n", s->surname, s->initials, s->sex, &(s->schoolNum), s->medal, s->composition, &(s->numExams), &offset);
    line += offset;
    int num = s->numExams;

    // Очищаем существующий список экзаменов
    s->examStats = NULL;
    for (int i = 0; i < num; i++) {
        sscanf(line, "%s %d%n", subject, &ball, &offset);
        value exam;
        strcpy(exam.subject, subject);
        exam.ball = ball;

        // Добавляем новый узел в начало списка
        pushFront(&(s->examStats), exam);

        line += offset;  // Учитываем пробел после каждого экзамена
    }
}




void addAbiturient(const char* filename, char* in, HashTable* table) {
    FILE* newFile = fopen(filename, "a+"); 
    if (newFile == NULL) {
        perror("Error");
        exit(1);
    }
    fseek(newFile, 0, SEEK_END);
    fseek(newFile, -1, SEEK_CUR);
    char lastChar = fgetc(newFile);

    if(lastChar == '\n' || ftell(newFile) == 0) {
        rewind(newFile);
        fprintf(newFile, "%s", in);
    } else {
        rewind(newFile);
        fprintf(newFile, "\n%s", in);
    }

    abiturient* s = newAbiturient();
    readFromLine(s, in);
    char* surname = getSurname(s);
    char* initials = getInitials(s);
    char key[STRSIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    printf("%s", key);
    fclose(newFile);
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insertElement(table, key, s);
}

void addAbiturientBin(const char* filename, char* in, HashTable* table) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    
    abiturient* abit = newAbiturient();
    readFromLine(abit, in); // Преобразование строки в структуру abiturient
    
    char* surname = getSurname(abit);
    char* initials = getInitials(abit);
    char key[STRSIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    
    abiturientWriteBin(abit, file); // Запись абитуриента в бинарный файл
    
    fclose(file);
    
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insertElement(table, key, abit);
}


void removeStudent(const char* file, const char* id, HashTable* table) {
    FILE* fp = fopen(file, "w");
    if (fp == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }
    
    removeElement(table, id);
    
    // Перезаписываем оставшихся абитуриентов в файл
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            abiturientWriteTxt(tmp, fp);
        }
    }
    
    fclose(fp);
}




void removeStudentBin(const char* file, const char* id, HashTable* table) {
    FILE* fp = fopen(file, "wb");
    if (fp == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    removeElement(table, id);

    // Перезаписываем оставшихся абитуриентов в файл
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            abiturientWriteBin(tmp, fp);
        }
    }

    fclose(fp);
}


void printAbiturientChars(abiturient* s) {
    if (s == NULL) {
        return;
    }
    char* surname = getSurname(s);
    char* initials = getInitials(s);
    char* sex = s->sex;
    Item school = s->schoolNum;
    char* medal = s->medal;
    char* comp = s->composition;
    
    printf("|============================================|\n");
    printf("|\tАбитуриент: %s %s                         \n", surname, initials);
    printf("|\tПол: %s                                   \n", sex);
    printf("|\tНомер школы: %d                         \n", school);
    printf("|\tНаличие медали: %s                        \n", medal);
    printf("|\tЗачет по сочинению: %s                    \n", comp);
    
    int numSubjects = sizeList(s->examStats);
    node* tmp = s->examStats;
    int totalBalls = 0;
    for(int i = 0; i < numSubjects; i++) {
        int ball = tmp->data.ball;
        printf("|\tБал по %s: %d                           \n", tmp->data.subject, ball);
        tmp = tmp->next;
        totalBalls += ball;
    }
    printf("|\tСуммарный балл: %d \n", totalBalls);
    printf("|============================================|\n");
}


void abiturientFree(abiturient* s) {
    if (s == NULL) {
        return;
    }

    // Освободить память для связанного списка examStats
    node* current = s->examStats;
    node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // После освобождения связанного списка, можно освободить саму структуру abiturient
    free(s);
}


void printAbiturientStr(HashTable* table) {
    printf("| Фамилия | Инициалы | Пол | Номер школы | Наличие медали | Зачет по сочинению |\n");
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            int numSubjects = sizeList(tmp->examStats);
            printf("| %s | %s | %s | %d | %s | %s |\n", tmp->surname, tmp->initials, tmp->sex, tmp->schoolNum, tmp->medal, tmp->composition);
            node* exam = tmp->examStats;
            for (int j = 0; j < numSubjects; j++) {
                printf("| Экзамен %d: %s, балл - %d \n", (j+1), exam->data.subject, exam->data.ball);
                exam = exam->next;
            }
            printf("-----------------------------------------------------------\n");
        }
    }
}


void writeStrBin(const char* str, FILE* out) {
    int length = strlen(str);
    if (length > MAXSIZE - 1) {
        length = MAXSIZE - 1;  // Ограничиваем длину строки
    }
    fwrite(&length, sizeof(int), 1, out);
    fwrite(str, sizeof(char), length, out);
    char nullChar = '\0';
    fwrite(&nullChar, sizeof(char), 1, out);  // Записываем нулевой символ в конце строки
}

int readStrBin(char* str, FILE* in) {
    int length;
    if (fread(&length, sizeof(int), 1, in) != 1) {
        *str = '\0';  // В случае ошибки чтения, устанавливаем пустую строку
        return 0;     // Возвращаем 0, чтобы указать на ошибку чтения
    }
    if (length > MAXSIZE - 1) {
        length = MAXSIZE - 1;  // Ограничиваем длину строки
    }
    if (length > 0) {
        if (fread(str, sizeof(char), length, in) != length) {
            *str = '\0';  // В случае ошибки чтения, устанавливаем пустую строку
            return 0;     // Возвращаем 0, чтобы указать на ошибку чтения
        }
    }
    str[length] = '\0';  // Добавляем нулевой символ в конце строки
    fseek(in, 1, SEEK_CUR);  // Пропускаем нулевой символ
    return 1;  // Возвращаем 1, чтобы указать на успешное чтение
}

int abiturientReadTxt(abiturient* s, FILE* in) {
    if (fscanf(in, "%s %s %s %d %s %s", s->surname, s->initials, s->sex, &(s->schoolNum), s->medal, s->composition) != 6)
        return 0;

    if (fscanf(in, "%d", &(s->numExams)) != 1)
        return 0;

    for (int i = 0; i < s->numExams; i++) {
        char subject[MAXSIZE];
        int ball;

        if (fscanf(in, "%s %d", subject, &ball) != 2)
            return 0;

        value exam;
        strcpy(exam.subject, subject);
        exam.ball = ball;
        pushBack(&(s->examStats), exam);
    }

    return 1;
}

void abiturientWriteTxt(abiturient* s, FILE* file) {
    fprintf(file, "%s ", s->surname);
    fprintf(file, "%s ", s->initials);
    fprintf(file, "%s ", s->sex);
    fprintf(file, "%d ", s->schoolNum);
    fprintf(file, "%s ", s->medal);
    fprintf(file, "%s ", s->composition);

    fprintf(file, "%d ", s->numExams);

    node* current = s->examStats;
    while (current != NULL) {
        fprintf(file, "%s %d ", current->data.subject, current->data.ball);
        current = current->next;
    }

    fprintf(file, "\n");
}

void abiturientWriteBin(abiturient* s, FILE* out) {
    // Записываем поля фиксированного размера
    writeStrBin(s->surname, out);
    writeStrBin(s->initials, out);
    writeStrBin(s->sex, out);
    fwrite(&(s->schoolNum), sizeof(Item), 1, out);
    writeStrBin(s->medal, out);
    writeStrBin(s->composition, out);

    // Записываем количество экзаменов
    fwrite(&(s->numExams), sizeof(Item), 1, out);

    // Записываем экзамены
    node* current = s->examStats;
    while (current != NULL) {
        writeStrBin(current->data.subject, out);
        fwrite(&(current->data.ball), sizeof(int), 1, out);
        current = current->next;
    }
}
int abiturientReadBin(abiturient* s, FILE* in) {
    if (!readStrBin(s->surname, in))
        return 0;
    if (!readStrBin(s->initials, in))
        return 0;
    if (!readStrBin(s->sex, in))
        return 0;
    if (fread(&(s->schoolNum), sizeof(Item), 1, in) != 1)
        return 0;
    if (!readStrBin(s->medal, in))
        return 0;
    if (!readStrBin(s->composition, in))
        return 0;
    if (fread(&(s->numExams), sizeof(Item), 1, in) != 1)
        return 0;

    int numExams = s->numExams;
    for (int i = 0; i < numExams; ++i) {
        char subject[MAXSIZE];
        int ball;

        if (!readStrBin(subject, in))
            return 0;
        if (fread(&ball, sizeof(int), 1, in) != 1)
            return 0;

        value exam;
        strcpy(exam.subject, subject);
        exam.ball = ball;
        pushBack(&(s->examStats), exam);
    }
    return 1;
}



void task(HashTable* table) {
    float totalBalls = 0;
    int countAbits = 0;
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            countAbits++;
            int numSubjects = sizeList(tmp->examStats);
            node* exam = tmp->examStats;
            for (int j = 0; j < numSubjects; j++) {
                int ball = exam->data.ball;
                totalBalls += ball;
                exam = exam->next;
            }
        }
    }
    float avgBall = totalBalls / countAbits;
    printf("Средний балл среди всех абитуриентов: %f\n", avgBall);
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            if (strcmp(tmp->medal, "No") == 0) {
                int numSubjects = sizeList(tmp->examStats);
                node* exam = tmp->examStats;
                float balls = 0;
                for (int j = 0; j < numSubjects; j++) {
                    float ball = exam->data.ball;
                    balls += ball;
                    exam = exam->next;
                }
                if (balls > avgBall) {
                    printAbiturientChars(tmp);
                } 
            }
        }
    }
}