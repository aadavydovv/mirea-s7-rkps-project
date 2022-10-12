#include "functions_const.h"

const char* TAB(unsigned int amount_of_spaces) {
    char* spaces = malloc(sizeof(char) * amount_of_spaces);
    for (unsigned int i = 0; i < amount_of_spaces; i++) { spaces[i] = ' '; }
    return spaces;
}

void initialize_xorshift() { state_of_xorshift = time(NULL) ^ (long) &printf; }

unsigned int get_random_number(unsigned int lowest_possible_number,
                               unsigned int highest_possible_number) {
    state_of_xorshift ^= state_of_xorshift << 13;
    state_of_xorshift ^= state_of_xorshift >> 17;
    state_of_xorshift ^= state_of_xorshift << 5;
    return (state_of_xorshift % (highest_possible_number + 1 - lowest_possible_number)) + lowest_possible_number;
}

double RND() {
    return get_random_number(0, 99999999) / 100000000.0;
}

// string to long
long VAL(char* string) {
    char* endptr;
    long number = strtol(string, &endptr, 10);
    return number;
}

void input_string(char** p_target) {
    *p_target = malloc(512);
    input(*p_target);
    strtok(*p_target, "\n");
}

void input_number(long* p_target) {
    char* p_number_as_string;
    input_string(&p_number_as_string);
    *p_target = VAL(p_number_as_string);
}
