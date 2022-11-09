#ifndef CODE_FUNCTIONS_CONST_H
#define CODE_FUNCTIONS_CONST_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "functions_var.h"

static char *N_str;
static long *S_dim;
static int A, B, C, C1;
static long F, S2, S3, P, I, S_num, J, X, TE, N_num, V, W;

static void (*p_line90)();

const char *TAB(unsigned int amount_of_spaces);

long VAL(char *string);

void input_string(char **p_target);

void input_number(long *p_target);

#define INPUT(p_target) _Generic((p_target), \
    char**: input_string,       \
    long*: input_number       \
    )(p_target);

#endif //CODE_FUNCTIONS_CONST_H
