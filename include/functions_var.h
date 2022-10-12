#ifndef CODE_FUNCTIONS_VAR_H
#define CODE_FUNCTIONS_VAR_H

#ifdef __ANDROID__
#include <jni.h>
char* path_of_file_output;
char* path_of_file_input;
#endif

void PRINT(const char* format, ...);
void input(char* target);

#endif //CODE_FUNCTIONS_VAR_H
