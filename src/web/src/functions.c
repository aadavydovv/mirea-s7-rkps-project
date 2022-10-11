#include "functions.h"
#include <emscripten.h>
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

//@clion_formatter:off
EM_JS(void, js_print, (const char* line), {
    output = UTF8ToString(line);
    output = output.replace("\u000B", "");
    output = output.replace("\u0002", "");
    output = output.replace("                  P", "                  ");
    if (output == "\n\n\n\n") {
        output = "\n\n\n"
    } else if (output == "\n\n\n") {
        output = "\n\n"
    } else if (output == "\n\n") {
        output = "\n"
    };
    out(output);
});
//@clion_formatter:on

void PRINT(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char* print_buffer = malloc(512);
    vsprintf(print_buffer, format, args);
    strtok(print_buffer, "\n");

    va_end(args);

    js_print(print_buffer);
    emscripten_sleep(20);
}

void INPUT(char* target) {
    fgets(target, 512, stdin);
}
