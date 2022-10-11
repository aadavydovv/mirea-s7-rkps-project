#include <stdarg.h>
#include <stdio.h>
#include "functions.h"

void PRINT(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void INPUT(char* target) {
    fgets(target, 512, stdin);
}