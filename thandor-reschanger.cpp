
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char DEFAULT_CONFIG_FILE[] = "thandor.dat";
#define OFFSET_HORIZONTAL_RESOLUTION 4
#define OFFSET_VERTICAL_RESOLUTION 8

void clear_input(void) {
    while (getchar() != '\n');
}

int read_int(const char* prompt) {
    int ret;
    printf("%s: ", prompt);
    fflush(stdout);
    while (scanf("%u", &ret) != 1) {
        clear_input();
        printf("Incorrect Input\n%s: ", prompt);
        fflush(stdout);
    }
    clear_input();
    return ret;
}

int reschnager(const char* config_file) {
    uint32_t vertical;
    uint32_t horizontal;
    FILE* thandor_dat;

    puts("Resolution changer for Thandor - Die Invasion\n 2023 by Jan Hofmeier\n");
    thandor_dat = fopen(config_file, "r+b");
    if (thandor_dat == NULL) {
        printf("%s not found.\n", config_file);
        return -1;
    }
    if (fseek(thandor_dat, OFFSET_HORIZONTAL_RESOLUTION, 0) ||
        fread(&horizontal, 4, 1, thandor_dat) != 1 ||
        fseek(thandor_dat, OFFSET_VERTICAL_RESOLUTION, 0) ||
        fread(&vertical, 4, 1, thandor_dat) != 1) {
        printf("Error reading %s\n", config_file);
        return -2;
    }

    printf("Current_resolution: %u x %u\n", horizontal, vertical);
 
    horizontal = read_int("New horizontal resolution");

    vertical = read_int("New vertical resolution");

    if (fseek(thandor_dat, OFFSET_HORIZONTAL_RESOLUTION, 0) ||
        fwrite(&horizontal, 4, 1, thandor_dat) != 1 ||
        fseek(thandor_dat, OFFSET_VERTICAL_RESOLUTION, 0) ||
        fwrite(&vertical, 4, 1, thandor_dat) != 1 ||
        fclose(thandor_dat)) {
        printf("Error writing %s\n", config_file);
        return -3;
    }
    puts("Resolution_successfully changed.");
    return 0;
}


int main(int argc, char* argv[])
{
    char* config_file = DEFAULT_CONFIG_FILE;
    if (argc > 1)
        config_file = argv[1];
    int ret = reschnager(config_file);
    puts("Press Enter to exit");
    fflush(stdout);
    getchar();
    return ret;
}

