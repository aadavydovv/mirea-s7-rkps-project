#include "functions_const.h"

const char *TAB(unsigned int amount_of_spaces) {
    char *spaces = malloc(sizeof(char) * (amount_of_spaces + 2));
    for (unsigned int i = 0; i < sizeof(char) * amount_of_spaces; i++) { spaces[i] = ' '; }
    spaces[sizeof(char) * amount_of_spaces] = '\0';
    spaces[sizeof(char) * (amount_of_spaces + 1)] = '\0';
    return spaces;
}

// string to long
long VAL(char *string) {
    char *endptr;
    long number = strtol(string, &endptr, 10);
    return number;
}

void input_string(char **p_target) {
    *p_target = malloc(512);
    input(*p_target);
    strtok(*p_target, "\n");
}

void input_number(long *p_target) {
    char *p_number_as_string;
    input_string(&p_number_as_string);
    *p_target = VAL(p_number_as_string);
}
