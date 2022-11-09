#include <malloc.h>
#include <string.h>
#include "functions_var.h"

static int n_of_random_numbers_set = 0;
static int n_of_random_number = 1;
static int *random_numbers;

double RND() {
    int return_value = random_numbers[(n_of_random_numbers_set * 3) + n_of_random_number];
    if (n_of_random_number == 3) {
        n_of_random_numbers_set++;
        n_of_random_number = 1;
    } else {
        n_of_random_number++;
    }

    return (return_value - 1.0) / 6.0;
}

void initialize_rng(char **args) {
    random_numbers = malloc(128 * sizeof(int));

    FILE *file_of_vintbas_output;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    file_of_vintbas_output = fopen(args[1], "r");
    while ((read = getline(&line, &len, file_of_vintbas_output)) != -1) {
        char *pointer_to_numbers;
        if ((pointer_to_numbers = strstr(line, "THE LUCKY NUMBERS ARE:")) != NULL) {
            pointer_to_numbers = strstr(pointer_to_numbers, ":") + 3;
            random_numbers[(n_of_random_numbers_set * 3) + 1] = (int) pointer_to_numbers[0] - '0';
            random_numbers[(n_of_random_numbers_set * 3) + 2] = (int) pointer_to_numbers[3] - '0';
            random_numbers[(n_of_random_numbers_set * 3) + 3] = (int) pointer_to_numbers[6] - '0';
            n_of_random_numbers_set++;
        }
    }

    fclose(file_of_vintbas_output);
    if (line) free(line);

    n_of_random_numbers_set = 0;
}
