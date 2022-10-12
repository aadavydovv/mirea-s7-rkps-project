#ifndef CODE_FUNCTIONS_CONST_H
#define CODE_FUNCTIONS_CONST_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "functions_var.h"

static char* N_str;
static long* S_dim;
static int A, B, C, C1;
static long F, S2, S3, P, I, S_num, J, X, TE, N_num, V, W;
static unsigned int state_of_xorshift;
static void (* p_line90)();

void initialize_xorshift();

unsigned int get_random_number(unsigned int lowest_possible_number,
                               unsigned int highest_possible_number);

const char* TAB(unsigned int amount_of_spaces);

double RND();

long VAL(char* string);

void input_string(char** p_target);

void input_number(long* p_target);

#define INPUT(p_target) _Generic((p_target), \
    char**: input_string,       \
    long*: input_number       \
    )(p_target);

#endif //CODE_FUNCTIONS_CONST_H
