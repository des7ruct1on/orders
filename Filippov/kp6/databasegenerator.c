#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


char* surname_male[] = {
    "Filippov",
    "Kravchenko",
    "Dragovich",
    "Melnikov",
    "Hlebnikov",
    "Zaitsev",
    "Kazakov",
    "Rudenko",
    "Rodnikov",
    "Bitykov",
    "Bortakovksiy",
    "Azanov",
    "Sergeev",
    "Potenko"
};

char* name_male[] = {
    "Maxim",
    "Ivan",
    "Egor",
    "Fedor",
    "Nikita",
    "Vlad",
    "Nikita",
    "Pavel",
    "Dmitriy"
};

char* name_female[] = {
    "Vera",
    "Dasha",
    "Lotta",
    "Masha",
    "Sasha",
    "Vlada",
    "Gelya",
    "Nika",
    "Nastya"
};

char* surname_female[] = {
    "Filippova",
    "Kravchenko",
    "Dragovich",
    "Melnikova",
    "Hlebnikova",
    "Zaitseva",
    "Kazakova",
    "Rudenko",
    "Rodnikova",
    "Bitykova",
    "Bortakovksiy",
    "Azanova",
    "Sergeeva",
    "Potenko"
};

char* cpu[] = {
    "i7-6700k",
    "i5-6600k",
    "R9-7950x",
    "i3-6100",
    "i5-7400",
    "Ryzen-R5-4500",
    "Ryzen-R7-3700",
    "Ryzen-R3-1200",
    "Ryzen-R9-5900",
    "i9-11900",
    "Mac-M2",
    "Mac-M1-Pro",
    "Mac-M2-Pro",
    "Mac-M1"
};

char* gpu[] = {
    "RTX-2060",
    "RTX-3070",
    "RTX-3090",
    "RTX-3070",
    "RTX-3050",
    "RTX-4070",
    "RTX-4080",
    "RX-7900",
    "RX-6900",
    "RX-6750",
    "RX-580",
    "RX-570",
    "GTX-TITAN-X"
};

char* os[] = {
    "Windows-11",
    "Windows-10",
    "Linux"
};

int ram[] = {
    8,
    16,
    32,
    64,
    128
};

char* type_disk[] = {
    "SSD",
    "HDD",
};

char* name_disk[] = {
    "Kingston",
    "Samsung",
    "WD",
    "HyperX",
    "Toshiba",
    "Intel",
    "Crucial",
    "Seagate",
    "NONAME"
};

int driver_amount[] = {
    128,
    256,
    512,
    1024,
    2048
};





int main(int argc, char *argv[]) {
    srand(time(NULL));  // инициализируем для рандомного заполнения
    int num = atoi(argv[2]);
    FILE* fp = fopen(argv[1], "w");  // открываем файл для записи
    if (argc != 3) {
        printf("Используйте: /generate FILE.txt [количество раз]\n");
        return 1;
    }
    //printf("%d", num);
    for (int i = 0; i < num; i++) {

        char* SURNAME;
        char* NAME;
        if (rand() % 2 == 0) {
            SURNAME = surname_male[rand() % (sizeof(surname_male) / sizeof(surname_male[0]))];
            NAME = name_male[rand() % (sizeof(name_male) / sizeof(name_male[0]))];
        } else {
            SURNAME = surname_female[rand() % (sizeof(surname_female) / sizeof(surname_female[0]))];
            NAME = name_female[rand() % (sizeof(name_female) / sizeof(name_female[0]))];
        }
        char* CPU = cpu[rand() % (sizeof(cpu) / sizeof(cpu[0]))];
        char* GPU;
        char* OS;
        if (strcmp(CPU, "Mac-M1") == 0|| strcmp(CPU, "Mac-M1-Pro") == 0|| strcmp(CPU, "Mac-M2") == 0 || strcmp(CPU, "Mac-M2-Pro") == 0) {
            GPU = "Apple";
            if (rand() % 2 == 0) {
                OS = "macOS-Ventura";
            } else {
                OS = "macOS-Monterey";
            }
        } else {
            GPU = gpu[rand() % (sizeof(gpu) / sizeof(gpu[0]))];
            OS = os[rand() % (sizeof(os) / sizeof(os[0]))];
        }
        int RAM = ram[rand() % (sizeof(ram) / sizeof(ram[0]))];
        char* DISK1 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* TYPE_DISK1 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int AMOUNT_DISK1 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        char* DISK2 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* TYPE_DISK2 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int AMOUNT_DISK2 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        char* DISK3 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* TYPE_DISK3 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int AMOUNT_DISK3 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        

        fprintf(fp, "%s %s %s %s %d %s 3 %s %s %d %s %s %d %s %s %d\n", SURNAME, NAME, CPU, GPU, RAM, OS, TYPE_DISK1, DISK1, AMOUNT_DISK1, TYPE_DISK2, DISK2, AMOUNT_DISK2, TYPE_DISK3, DISK3, AMOUNT_DISK3);   //записываем в файл построчно
        
    }

    fclose(fp);
}