#include "student.h"
#include <string.h>

void init_hash_table(hash_table* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->cells[i].key[0] = '\0';
        table->cells[i].data = NULL;
    }
}

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    unsigned int p = 31;
    unsigned int len = strlen(key);

    for (unsigned int i = 0; i < len; i++) {
        hash = (hash * p) + key[i];
    }

    return hash % TABLE_SIZE;
}

void insert_element(hash_table* table, const char* key, student* value) {
    unsigned int index = hash(key);

    while (table->cells[index].data != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(table->cells[index].key, key);
    table->cells[index].data = value;
}

student* find_element(hash_table* table, const char* key) {
    unsigned int index = hash(key);

    while (table->cells[index].data != NULL) {
        if (strcmp(table->cells[index].key, key) == 0) {
            return table->cells[index].data;
        }

        index = (index + 1) % TABLE_SIZE;
    }

    return NULL;
}

void erase_element(hash_table* table, const char* key) {
    unsigned int index = hash(key);

    while (table->cells[index].data != NULL) {
        if (strcmp(table->cells[index].key, key) == 0) {
            student* removed_value = table->cells[index].data;

            // Освободить память для удаленного элемента
            destructor_student(removed_value);
            // Установить ключ и значение в NULL для удаленного элемента
            table->cells[index].key[0] = '\0';
            table->cells[index].data = NULL;
            return;
        }

        index = (index + 1) % TABLE_SIZE;
    }
}


void destructor_hash_table(hash_table* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->cells[i].data != NULL) {
            destructor_student(table->cells[i].data);
            table->cells[i].data = NULL;
        }
        table->cells[i].key[0] = '\0';
    }
}

char* get_surname(student* s) {
    if(s == NULL) {
        return "";
    }
    return s->surname;
}

char* get_initials(student* s) {
    if(s == NULL) {
        return "";
    }
    return s->initials;
}

student* create_student() {
    student* s = malloc(sizeof(student));
    if (s == NULL) {
        return NULL;
    }
    strcpy(s->surname, "");         
    strcpy(s->initials, "");
    strcpy(s->gender, "");
    s->school_num = 0;
    s->class_num = 0;
    s->index = ' ';
    return s;
}

void destructor_student(student* s) {
    if (s == NULL) {
        return;
    }
    free(s);
}

void read_from_str(student* s, char* line) {
    sscanf(line, "%s %s %s %d %c %d", s->surname, s->initials, s->gender, &(s->class_num), &(s->index), &(s->school_num));
}

void write_string_bin(const char* str, FILE* out) {
    int length = strlen(str);
    if (length > MAX_SIZE - 1) {
        length = MAX_SIZE - 1;  // Ограничиваем длину строки
    }
    fwrite(&length, sizeof(int), 1, out);
    fwrite(str, sizeof(char), length, out);
    char nullChar = '\0';
    fwrite(&nullChar, sizeof(char), 1, out);  // Записываем нулевой символ в конце строки
}

int read_string_bin(char* str, FILE* in) {
    int length;
    if (fread(&length, sizeof(int), 1, in) != 1) {
        *str = '\0';  // В случае ошибки чтения, устанавливаем пустую строку
        return 0;     // Возвращаем 0, чтобы указать на ошибку чтения
    }
    if (length > MAX_SIZE - 1) {
        length = MAX_SIZE - 1;  // Ограничиваем длину строки
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

void write_student_txt(student* s, FILE* in) {
    fprintf(in, "%s ", s->surname);
    fprintf(in, "%s ", s->initials);
    fprintf(in, "%s ", s->gender);
    fprintf(in, "%d ", s->class_num);
    fprintf(in, "%c ", s->index);
    fprintf(in, "%d ", s->school_num);
    fprintf(in, "\n");
}

int read_student_bin(student* s, FILE* in) {
    if(!read_string_bin(s->surname, in)) {
        return 0;
    }
    if(!read_string_bin(s->initials, in)) {
        return 0;
    }
    if(!read_string_bin(s->gender, in)) {
        return 0;
    }
    fread(&(s->class_num), sizeof(int), 1, in);
    fread(&(s->index), sizeof(char), 1, in);
    fread(&(s->school_num), sizeof(int), 1, in);
    return !feof(in);
}

void write_student_bin(student* s, FILE* out) {
    write_string_bin(s->surname, out);
    write_string_bin(s->initials, out);
    write_string_bin(s->gender, out);
    fwrite(&(s->class_num), sizeof(int), 1, out);
    fwrite(&(s->index), sizeof(char), 1, out);
    fwrite(&(s->school_num), sizeof(int), 1, out);
}

void print_student(student* s) {
    if (s == NULL) {
        return;
    }
    printf("|============================================|\n");
    printf("|\tШкольник: %s %s\n", s->surname, s->initials);
    printf("|\tКласс: %d-%c\n", s->class_num, s->index);
    printf("|\tНомер школы: %d\n", s->school_num);
    printf("|============================================|\n");
}

void print_table(hash_table* table) {
    printf("|-----------------------------------------------------------------|\n");
    printf("|     Фамилия     |  Инициалы  |    Класс    |      Номер школы   |\n");
    printf("|-----------------------------------------------------------------|\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        student* tmp = table->cells[i].data;
        if (tmp == NULL) {
            continue;
        }
        printf("| %15s | %10s |    %2d-%c     | %18d |\n", tmp->surname, tmp->initials, tmp->class_num, tmp->index, tmp->school_num);
    }
    printf("|-----------------------------------------------------------------|\n");
}

void insert_student(const char* filename, char* in, hash_table* table) {
    student* s = create_student();
    read_from_str(s, in);
    char* surname = get_surname(s);
    char* initials = get_initials(s);
    char key[STR_SIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    if (found_student(table, key)) {
        printf("Пассажир уже в базе данных\n");
        destructor_student(s);
        return;
    }
    FILE* new_file = fopen(filename, "a+"); 
    if (new_file == NULL) {
        perror("Error");
        exit(1);
    }
    fseek(new_file, 0, SEEK_END);
    fseek(new_file, -1, SEEK_CUR);
    char lastChar = fgetc(new_file);

    if(lastChar == '\n' || ftell(new_file) == 0) {
        rewind(new_file);
        fprintf(new_file, "%s", in);
    } else {
        rewind(new_file);
        fprintf(new_file, "\n%s", in);
    }
    fclose(new_file);
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insert_element(table, key, s);
}

void erase_student(const char* filename, const char* key, hash_table* table) {
    if (!found_student(table, key)) {
        printf("Школьниу уже в базе данных\n");
        return;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }
    erase_element(table, key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->cells[i].data != NULL) {
            student* tmp = table->cells[i].data;
            write_student_txt(tmp, file);
        }
    }
    fclose(file);
}


bool found_student(hash_table* table, const char* key) {
    return find_element(table, key) != NULL;
}

