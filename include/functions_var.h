#ifndef CODE_FUNCTIONS_VAR_H
#define CODE_FUNCTIONS_VAR_H

#ifdef __ANDROID__
#include <jni.h>
char* path_of_file_output;
char* path_of_file_input;
#endif

void initialize_rng(char **args);

void input(char *target);

void PRINT(const char *format, ...);

double RND();

#endif //CODE_FUNCTIONS_VAR_H
