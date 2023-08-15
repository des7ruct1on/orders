#include "aeroflot.h"
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

void insert_element(hash_table* table, const char* key, passenger* value) {
    unsigned int index = hash(key);

    while (table->cells[index].data != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(table->cells[index].key, key);
    table->cells[index].data = value;
}

passenger* find_element(hash_table* table, const char* key) {
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
            passenger* removed_value = table->cells[index].data;

            // Освободить память для удаленного элемента
            destructor_passenger(removed_value);

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
            destructor_passenger(table->cells[i].data);
            table->cells[i].data = NULL;
        }
        table->cells[i].key[0] = '\0';
    }
}

char* get_surname(passenger* p) {
    if(p == NULL) {
        return "";
    }
    return p->surname;
}

char* get_initials(passenger* p) {
    if(p == NULL) {
        return "";
    }
    return p->initials;
}

passenger* create_passenger() {
    passenger* p = malloc(sizeof(passenger));
    if (p == NULL) {
        return NULL;
    }
    strcpy(p->surname, "");         
    strcpy(p->initials, "");
    strcpy(p->destination, "");
    p->items_num = 0;
    p->total_weight = 0;
    p->num_childrens = 0;
    p->transfer = 0;
    p->time.hour = 0;
    p->time.minute = 0;
    return p;
}

void destructor_passenger(passenger* p) {
    if (p == NULL) {
        return;
    }
    free(p);
}

void read_from_str(passenger* p, char* line) {
    sscanf(line, "%s %s %d %d %s %d %d %d %d", p->surname, p->initials, &(p->items_num), &(p->total_weight), p->destination, &(p->time.hour), &(p->time.minute), &(p->transfer), &(p->num_childrens));
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

void write_passenger_txt(passenger* p, FILE* in) {
    fprintf(in, "%s ", p->surname);
    fprintf(in, "%s ", p->initials);
    fprintf(in, "%d ", p->items_num);
    fprintf(in, "%d ", p->total_weight);
    fprintf(in, "%s ", p->destination);
    fprintf(in, "%02d ", p->time.hour);
    fprintf(in, "%02d ", p->time.minute);
    fprintf(in, "%d ", p->transfer);
    fprintf(in, "%d ", p->num_childrens);
    fprintf(in, "\n");
}

int read_passenger_bin(passenger* p, FILE* in) {
    if(!read_string_bin(p->surname, in)) {
        return 0;
    }
    if(!read_string_bin(p->initials, in)) {
        return 0;
    }
    fread(&(p->items_num), sizeof(int), 1, in);
    fread(&(p->total_weight), sizeof(int), 1, in);
    if(!read_string_bin(p->destination, in)) {
        return 0;
    }
    fread(&(p->time.hour), sizeof(int), 1, in);
    fread(&(p->time.minute), sizeof(int), 1, in);
    fread(&(p->transfer), sizeof(int), 1, in);
    fread(&(p->num_childrens), sizeof(int), 1, in);
    return !feof(in);
}

void write_passenger_bin(passenger* p, FILE* out) {
    write_string_bin(p->surname, out);
    write_string_bin(p->initials, out);
    fwrite(&(p->items_num), sizeof(int), 1, out);
    fwrite(&(p->total_weight), sizeof(int), 1, out);
    write_string_bin(p->destination, out);
    fwrite(&(p->time.hour), sizeof(int), 1, out);
    fwrite(&(p->time.minute), sizeof(int), 1, out);
    fwrite(&(p->transfer), sizeof(int), 1, out);
    fwrite(&(p->num_childrens), sizeof(int), 1, out);
}

void print_passenger(passenger* p) {
    if (p == NULL) {
        return;
    }
    char* surname = get_surname(p);
    char* initials = get_initials(p);
    char* destination = p->destination;
    printf("|============================================|\n");
    printf("|\tПассажир: %s %s\n", surname, initials);
    printf("|\tКоличество вещей: %d\n", p->items_num);
    printf("|\tОбщий вес вещей: %d\n", p->total_weight);
    printf("|\tПункт назначения: %s\n", destination);
    printf("|\tВремя вылета: %d:%d\n", p->time.hour, p->time.minute);
    printf("|\tНаличие пересадок: %d\n", p->transfer);
    printf("|\tКоличество детей: %d\n", p->num_childrens);
    printf("|============================================|\n");
}

void print_table(hash_table* table) {
    printf("|-------------------------------------------------------------|\n");
    printf("|   Фамилия  |  Инициалы  | Время вылета |  Пункт назначения  |\n");
    printf("|-------------------------------------------------------------|\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        passenger* tmp = table->cells[i].data;
        if (tmp == NULL) {
            continue;
        }
        printf("| %10s | %10s |    %02d:%02d     | %18s |\n", tmp->surname, tmp->initials, tmp->time.hour, tmp->time.minute, tmp->destination);
    }
    printf("|-------------------------------------------------------------|\n");
}

void insert_passenger(const char* filename, char* in, hash_table* table) {
    passenger* p = create_passenger();
    read_from_str(p, in);
    char* surname = get_surname(p);
    char* initials = get_initials(p);
    char key[STR_SIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    if (found_passenger(table, key)) {
        printf("Пассажир уже в базе данных\n");
        destructor_passenger(p);
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
    //printf("%s", key);
    fclose(new_file);
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insert_element(table, key, p);
}

void erase_passenger(const char* filename, const char* key, hash_table* table) {
    if (!found_passenger(table, key)) {
        printf("Пассажир уже в базе данных\n");
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
            passenger* tmp = table->cells[i].data;
            write_passenger_txt(tmp, file);
        }
    }
    fclose(file);
}


bool found_passenger(hash_table* table, const char* key) {
    return find_element(table, key) != NULL;
}

