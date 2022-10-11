#include <string.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdarg.h>
#include "functions.h"

void PRINT(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char* path_of_file_output;
    path_of_file_output = va_arg(args, char*);

    FILE* file_output = fopen(path_of_file_output, "a");
    fseek(file_output, -100, SEEK_END);
    vfprintf(file_output, format, args);
    fclose(file_output);
}

void INPUT(char* target, ...) {
    va_list args;
    va_start(args, target);

    char* path_of_file_input;
    path_of_file_input = va_arg(args, char*);

    FILE* file_input;
    long size = 0;
    while (size == 0) {
        file_input = fopen(path_of_file_input, "r");
        fseek(file_input, 0L, SEEK_END);
        size = ftell(file_input);
        fclose(file_input);

        struct timespec ts = {0, 100 * 1000000};
        nanosleep(&ts, &ts);
    }

    file_input = fopen(path_of_file_input, "r");
    char *input_buffer = malloc(512);
    size_t len = 0;
    getline(&input_buffer, &len, file_input);

    PRINT("%s\n", input_buffer);

    file_input = fopen(path_of_file_input, "w");
    fclose(file_input);

    strcpy(target, input_buffer);
}
