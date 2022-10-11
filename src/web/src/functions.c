#include "functions.h"
#include <emscripten.h>
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

//@clion_formatter:off
EM_JS(void, js_print, (const char* line), { out(UTF8ToString(line)); });
//@clion_formatter:on

void PRINT(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char* print_buffer = malloc(512);
    vsprintf(print_buffer, format, args);

    va_end(args);

    js_print(print_buffer);
    emscripten_sleep(20);
}

void INPUT(char* target, ...) {
    fgets(target, 512, stdin);
}
