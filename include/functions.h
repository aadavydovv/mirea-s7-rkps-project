#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#ifdef __ANDROID__
char path_of_file_output[256];
char path_of_file_input[256];
#endif

void PRINT(const char* format, ...);
void INPUT(char* target);

#endif //CODE_FUNCTIONS_H
