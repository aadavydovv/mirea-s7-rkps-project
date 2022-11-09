#include <time.h>
#include <stdio.h>
#include "functions_var.h"

static unsigned int state_of_xorshift;

unsigned int get_random_number(unsigned int lowest_possible_number,
                               unsigned int highest_possible_number) {
    state_of_xorshift ^= state_of_xorshift << 13;
    state_of_xorshift ^= state_of_xorshift >> 17;
    state_of_xorshift ^= state_of_xorshift << 5;
    return (state_of_xorshift % (highest_possible_number + 1 - lowest_possible_number)) + lowest_possible_number;
}

void initialize_rng(char **args) { state_of_xorshift = time(NULL) ^ (long) &printf; }

double RND() {
    return get_random_number(0, 99999999) / 100000000.0;
}
