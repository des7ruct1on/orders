#include "pcspecs.h"
#include <string.h>
void init_hash_table(hash_table* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->elements[i].key[0] = '\0';
        table->elements[i].data = NULL;
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

void insert_element(hash_table* table, const char* key, person* value) {
    unsigned int index = hash(key);

    while (table->elements[index].data != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(table->elements[index].key, key);
    table->elements[index].data = value;
}

person* find_element(hash_table* table, const char* key) {
    unsigned int index = hash(key);

    while (table->elements[index].data != NULL) {
        if (strcmp(table->elements[index].key, key) == 0) {
            return table->elements[index].data;
        }

        index = (index + 1) % TABLE_SIZE;
    }

    return NULL;
}

void erase_element(hash_table* table, const char* key) {
    unsigned int index = hash(key);

    while (table->elements[index].data != NULL) {
        if (strcmp(table->elements[index].key, key) == 0) {
            person* removed_value = table->elements[index].data;

            // Освободить память для удаленного элемента
            destructor_person(removed_value);

            // Установить ключ и значение в NULL для удаленного элемента
            table->elements[index].key[0] = '\0';
            table->elements[index].data = NULL;
            return;
        }

        index = (index + 1) % TABLE_SIZE;
    }
}


void destructor_hash_table(hash_table* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i].data != NULL) {
            destructor_person(table->elements[i].data);
            table->elements[i].data = NULL;
        }
        table->elements[i].key[0] = '\0';
    }
}

person* create_person() {
    person* new_person = malloc(sizeof(person));
    strcpy(new_person->surname, "");
    strcpy(new_person->name, "");
    strcpy(new_person->cpu, "");
    strcpy(new_person->gpu, "");
    strcpy(new_person->os, "");
    new_person->ram = 0;
    new_person->num_drivers = 0;
    new_person->disks = NULL;

    return new_person;

}


char* get_surname(person* p) {
    if (p == NULL)
        return "";
    return p->surname;
}


char* get_name(person* p) {
    if (p == NULL)
        return "";
    return p->name;
}


char* get_cpu(person* p) {
    if (p == NULL)
        return "";
    return p->cpu;
}


char* get_gpu(person* p) {
    if (p == NULL)
        return "";
    return p->gpu;
}


int get_ram(person* p) {
    if (p == NULL)
        return 0;
    return p->ram;
}


char* get_os(person* p) {
    if (p == NULL)
        return "";
    return p->os;
}


int get_amount_disks(person* p) {
    if (p == NULL)
        return 0;
    return p->num_drivers;
}


driver* get_driver(person* p) {
    if (p == NULL) 
        return NULL;
    return p->disks;
}

void print_person(person* p) {
    char* surname = get_surname(p);
    char* name = get_name(p);
    char* cpu = get_cpu(p);
    char* gpu = get_gpu(p);
    int ram = get_ram(p);
    char* os = get_os(p);
    int num_drivers = get_amount_disks(p);
    driver* disks = get_driver(p);
    printf("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
    printf("| Имя: %s %s\n", surname, name);
    printf("| Характеристики компьютера\n");
    printf("| Процессор: %s\n", cpu);
    printf("| Видеокарта: %s\n", gpu);
    printf("| Объем ОЗУ: %d\n", ram);
    printf("| Операционная система: %s\n", os);
    printf("| Количество хранилищ: %d\n", num_drivers);
    for (int i = 0; i < num_drivers; i++) {
        printf("| Диск %d: %s %s %d\n", (i + 1), disks[i].type, disks[i].name, disks[i].amount);
    }
    printf("|=============================|\n");
    
}


void print_table(hash_table* table) {
    printf("|           Имя            |    Процессор    |    Видеокарта    |  ОЗУ  | Операционная система |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i].data != NULL) {
            person* tmp = table->elements[i].data;
            char* surname = get_surname(tmp);
            char* name = get_name(tmp);
            char* cpu = get_cpu(tmp);
            char* gpu = get_gpu(tmp);
            int ram = get_ram(tmp);
            char* os = get_os(tmp);
            printf("| %12s %11s | %15s | %16s | %5d | %20s |\n", surname, name, cpu, gpu, ram, os);

        }
    }
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}


void read_str(person* p, char* str) {
    int offset = 0;
    sscanf(str, "%s %s %s %s %d %s %d%n", p->surname, p->name, p->cpu, p->gpu, &(p->ram), p->os, &(p->num_drivers), &offset);
    str += offset;

    // Выделяем память для массива disks
    int count = p->num_drivers;
    p->disks = malloc(count * sizeof(driver));
    for (int i = 0; i < count; i++) {
        driver tmp;
        sscanf(str, "%s %s %d%n", tmp.type, tmp.name, &(tmp.amount), &offset);
        p->disks[i] = tmp;
        str += offset;
    }
}

void write_person_txt(person* p, FILE* file) {
    //print_person(p);
    fprintf(file, "%s ", p->surname);
    fprintf(file, "%s ", p->name);
    fprintf(file, "%s ", p->cpu);
    fprintf(file, "%s ", p->gpu);
    fprintf(file, "%d ", p->ram);
    fprintf(file, "%s ", p->os);
    fprintf(file, "%d ", p->num_drivers);
    driver* drivers = get_driver(p);
    for (int i = 0; i < p->num_drivers; i++) {
        fprintf(file, "%s ", drivers[i].type);
        fprintf(file, "%s ", drivers[i].name);
        fprintf(file, "%d ", drivers[i].amount);
    }
    fprintf(file, "\n");
}

void write_str_bin(const char* str, FILE* out) {
    int length = strlen(str);
    //printf("%s %d\n", str, length);
    if (length > STR_SIZE - 1) {
        length = STR_SIZE - 1;  // Ограничиваем длину строки
    }
    fwrite(&length, sizeof(int), 1, out);
    fwrite(str, sizeof(char), length, out);
    char null_char = '\0';
    fwrite(&null_char, sizeof(char), 1, out);  // Записываем нулевой символ в конце строки
}

int read_str_bin(char* str, FILE* in) {
    int length;
    if (fread(&length, sizeof(int), 1, in) != 1) {
        *str = '\0';  // В случае ошибки чтения, устанавливаем пустую строку
        return 0;     // Возвращаем 0, чтобы указать на ошибку чтения
    }
    //printf("%d\n", length);
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



void write_person_bin(person* p, FILE* out) {
    // Записываем поля фиксированного размера
    
    write_str_bin(p->surname, out);
    write_str_bin(p->name, out);
    write_str_bin(p->cpu, out);
    write_str_bin(p->gpu, out);
    fwrite(&(p->ram), sizeof(int), 1, out);
    write_str_bin(p->os, out);
    fwrite(&(p->num_drivers), sizeof(int), 1, out);


    driver* drivers = get_driver(p);

    for (int i = 0; i < p->num_drivers; i++) {
        write_str_bin(drivers[i].type, out);
        write_str_bin(drivers[i].name, out);
        fwrite(&(drivers[i].amount), sizeof(int), 1, out);
    }
}
int read_bin(person* p, FILE* in) {
    if (!read_str_bin(p->surname, in))
        return 0;
    if (!read_str_bin(p->name, in))
        return 0;
    if (!read_str_bin(p->cpu, in))
        return 0;
    if (!read_str_bin(p->gpu, in))
        return 0;
    if (fread(&(p->ram), sizeof(int), 1, in) != 1)
        return 0;
    if (!read_str_bin(p->os, in))
        return 0;
    if (fread(&(p->num_drivers), sizeof(int), 1, in) != 1)
        return 0;

    int count = p->num_drivers;
    p->disks = malloc(count * sizeof(driver));
    for (int i = 0; i < p->num_drivers; i++) {
        driver tmp;
        if (!read_str_bin(tmp.type, in))
            return 0;
        if (!read_str_bin(tmp.name, in))
            return 0;
        if (fread(&(tmp.amount), sizeof(int), 1, in) != 1)
            return 0;

        p->disks[i] = tmp;

    }
    
    return 1;
}



void insert_person(const char* filename, char* in, hash_table* table) {
    person* p = create_person();
    read_str(p, in);
    // берем данные для формирования ключа
    char* surname = get_surname(p);
    char* name = get_name(p);
    char key[STR_SIZE];

    // создание ключа
    strcpy(key, surname); 
    strcat(key, " "); 
    strcat(key, name); 

    // проверка на необходимость перезаписи файла
    if (found_person(table, key)) {
        printf("Пользователь уже содержится в базе данных\n");
        destructor_person(p);
        return;
    }
    FILE* new_file = fopen(filename, "a+"); 
    if (new_file == NULL) {
        perror("Error");
        exit(1);
    }
    fseek(new_file, 0, SEEK_END);
    fseek(new_file, -1, SEEK_CUR);
    char last_char = fgetc(new_file);

    if(last_char == '\n' || ftell(new_file) == 0) {
        rewind(new_file);
        fprintf(new_file, "%s", in);
    } else {
        rewind(new_file);
        fprintf(new_file, "\n%s", in);
    }
    fclose(new_file);
    printf("%s %s был добавлен в таблицу.\n", surname, name);
    insert_element(table, key, p);
}


void erase_person(const char* filename, const char* key, hash_table* table) {
    if (!found_person(table, key)) {
        printf("Пользователь уже содержится в базе данных\n");
        return;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось открыть файл!\n");
        return;
    }
    erase_element(table, key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i].data != NULL) {
            person* tmp = table->elements[i].data;
            write_person_txt(tmp, file);
        }
    }
    fclose(file);
}


void destructor_person(person* p) {
    if (p == NULL)
        return;
    free(p->disks);
    free(p);
}
bool found_person(hash_table* table, const char* key) {
    return find_element(table, key) != NULL;
}
