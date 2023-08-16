#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


// Константные значения
char* surname_male[] = {
    "Olkhov",
    "Tretyakov",
    "Dragovich",
    "Melnikov",
    "Hlebnikov",
    "Zaitsev",
    "Kazakov",
    "Rudenko",
    "Rodnikov",
    "Alkhimov",
    "Bortakovksiy",
    "Azanov",
    "Sergeev",
    "Blinov"
};

char* name_male[] = {
    "Maxim",
    "Ivan",
    "Viktor",
    "Oleg",
    "Nikita",
    "Vlad",
    "Nikita",
    "Pavel",
    "Kirill"
};

char* name_female[] = {
    "Vera",
    "Dasha",
    "Kris",
    "Masha",
    "Sasha",
    "Vlada",
    "Lesya",
    "Nika",
    "Nastya"
};

char* surname_female[] = {
    "Olkhova",
    "Tretyakova",
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
    "i7-7700",
    "i5-6500",
    "R9-7950x",
    "i3-7100",
    "i5-7400",
    "Ryzen-R5-4500",
    "Ryzen-R7-3700",
    "Ryzen-R3-1200",
    "Ryzen-R9-5900",
    "i9-11900k",
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
    // инициализируем для рандомного заполнения
    srand(time(NULL));  
    int num = atoi(argv[2]);
    FILE* fp = fopen(argv[1], "w");  
    if (argc != 3) {
        printf("Используйте: /generate FILE.txt [количество раз]\n");
        return 1;
    }
    for (int i = 0; i < num; i++) {

        char* _surname;
        char* _name;
        if (rand() % 2 == 0) {
            _surname = surname_male[rand() % (sizeof(surname_male) / sizeof(surname_male[0]))];
            _name = name_male[rand() % (sizeof(name_male) / sizeof(name_male[0]))];
        } else {
            _surname = surname_female[rand() % (sizeof(surname_female) / sizeof(surname_female[0]))];
            _name = name_female[rand() % (sizeof(name_female) / sizeof(name_female[0]))];
        }
        char* _cpu = cpu[rand() % (sizeof(cpu) / sizeof(cpu[0]))];
        char* _gpu;
        char* _os;
        if (strcmp(_cpu, "Mac-M1") == 0|| strcmp(_cpu, "Mac-M1-Pro") == 0|| strcmp(_cpu, "Mac-M2") == 0 || strcmp(_cpu, "Mac-M2-Pro") == 0) {
            _gpu = "Apple";
            if (rand() % 2 == 0) {
                _os = "macOS-Ventura";
            } else {
                _os = "macOS-Monterey";
            }
        } else {
            _gpu = gpu[rand() % (sizeof(gpu) / sizeof(gpu[0]))];
            _os = os[rand() % (sizeof(os) / sizeof(os[0]))];
        }
        int _ram = ram[rand() % (sizeof(ram) / sizeof(ram[0]))];
        char* _disk1 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* _t_disk1 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int _store_disk1 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        char* _disk2 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* _t_disk2 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int _store_disk2 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        char* _disk3 = name_disk[rand() % (sizeof(name_disk) / sizeof(name_disk[0]))];
        char* _t_disk3 = type_disk[rand() % (sizeof(type_disk) / sizeof(type_disk[0]))];
        int _store_disk3 = driver_amount[rand() % (sizeof(driver_amount) / sizeof(driver_amount[0]))];
        
        //записываем в файл построчно данные о каждом пользователе
        fprintf(fp, "%s %s %s %s %d %s 3 %s %s %d %s %s %d %s %s %d\n", _surname, _name, _cpu, _gpu, _ram, _os, _t_disk1, _disk1, _store_disk1, _t_disk2, _disk2, _store_disk2, _t_disk3, _disk3, _store_disk3);   
        
    }

    fclose(fp);
}