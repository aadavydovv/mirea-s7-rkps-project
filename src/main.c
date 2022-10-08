#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *N_str;
long *S_dim;
int A, B, C, C1;
long F, S2, S3, P, I, S_num, J, X, TE, N_num, V;
long W = 0;

unsigned int state_of_xorshift;

void initialize_xorshift() { state_of_xorshift = time(NULL) ^ (long) &printf; }

static unsigned int get_random_number(unsigned int lowest_possible_number,
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
long VAL(char *string) {
    char *endptr;
    long number = strtol(string, &endptr, 10);
    // if (*endptr != '\0') { ошибка O_O }
    return number;
}

void INPUT_string(char **p_target) {
    const int max_length_of_string = 64;
    int size_of_string = (int) sizeof(char) * max_length_of_string;
    *p_target = malloc(size_of_string);
    fgets(*p_target, size_of_string, stdin);
    strtok(*p_target, "\n");
}

void INPUT_number(long *p_target) {
    char *p_number_as_string;
    INPUT_string(&p_number_as_string);
    *p_target = VAL(p_number_as_string);
}

void (*p_line90)();

void line3440() {
    // 3440
    exit(0);
}

void line3410() {
    // 3410
    printf("YOU WON EXACTLY $ %ld !! NOT BAD !!!\n", W);

    // 3440
    line3440();
}

void line3380() {
    // 3380
    printf("YOU DIDN'T WIN ANY MONEY, BUT I'M WILLING TO CALL IT EVEN!!\n");

    // 3390
    line3440();
}

void line3360() {
    // 3360
    printf("\n\nSO YOU WANT TO CASH IN YOUR CHIPS, I SEE!!\n");

    // 3370
    if (W > 0) {
        line3410();
    }

    // 3380
    line3380();
}

void line3260() {
    // 3260
    if (W == 0) { printf("YOU'RE EVEN!!\n\n"); }

    // 3270
    if (W > 0) { printf("YOU'RE AHEAD $ %ld\n\n", W); }

    // 3280
    if (W < 0) { printf("YOU'RE BEHIND $%ld\n\n", W); }

    p_line90();
}

void line2060() {
    // 2060
    C1 = 0;

    // 2070
    if (S2 == A) { C1 += 1; }

    // 2080
    if (S2 == B) { C1 += 1; }

    // 2090
    if (S2 == C) { C1 += 1; }

    // 2100
    if (C1 > 0) {
        // 2130
        S3 *= C1;

        // 2140
        printf("YOU WIN  %d  TIMES ON: %ld\n", C1, S2);
    } else {
        // 2110
        S3 *= -1;

        // 2120
        printf("YOU LOSE ON:  %ld\n", S2);
    }

    // 2150
    W = 0;
    W += S3;

    // 2160
    // return;
}

void line1870() {
    // 1870
    X = -1;

    // 1880
    A = (int) (6 * RND() + 1);
    B = (int) (6 * RND() + 1);
    C = (int) (6 * RND() + 1);

    // 1890
    S_dim[1] = A;
    S_dim[2] = B;
    S_dim[3] = C;

    // 1900-1940
    for (int Y = 1; Y < 2; Y++) {
        for (X = 1; X < 3 - Y; X++) {
            if (S_dim[X] <= S_dim[X + 1]) { continue; }
            TE = S_dim[X];
            S_dim[X] = S_dim[X + 1];
            S_dim[X + 1] = TE;
        }
    }

    // 1950
    printf("THE LUCKY NUMBERS ARE:  %ld  %ld  %ld\n", S_dim[1], S_dim[2], S_dim[3]);

    // 1960
    // return;
}

void line820() {
    // 820
    line1870();

    // 830
    S2 = V;
    S3 = F;
    line2060();

    // 840
    S2 = P;
    S3 = I;
    line2060();

    // 850
    S2 = S_num;
    S3 = J;
    line2060();

    // 870
    line3260();
}

void line710() {
    printf("WAGER ON EACH OF THE THREE? ");

    // 720
    INPUT_number(&F);
    printf("?? ");
    INPUT_number(&I);
    printf("?? ");
    INPUT_number(&J);

    // 730
    if (F <= 500 || F >= 1 || I <= 500 || I >= 1 || J <= 500 || J >= 1) {
        line820();
    }

    // 800
    printf("THE HOUSE LIMIT IS FROM $1 TO $500.\n");

    // 810
    line710();
}

void line600() {
    printf("WHAT THREE NUMBERS? ");

    // 610
    INPUT_number(&V);
    printf("?? ");
    INPUT_number(&P);
    printf("?? ");
    INPUT_number(&S_num);

    // 620
    if (V <= 6 || V >= 1 || P <= 6 || P >= 1 || S_num <= 6 || S_num >= 1) {
        line710();
    }

    // 690
    printf("YOU CAN ONLY BET ON AN INTEGER FROM ONE TO SIX.\n");

    // 700
    line600();
}

void line550() {
    // 550
    line1870();

    // 560
    S2 = V;
    S3 = F;
    line2060();

    // 570
    S2 = P;
    S3 = I;
    line2060();

    // 590
    line3260();
}

void line460() {
    // 460
    printf("WAGER ON BOTH? ");

    // 470
    INPUT_number(&F);
    printf("?? ");
    INPUT_number(&I);

    // 480
    if (F <= 500 || F >= 1 || I <= 500 || I >= 1) {
        line550();
    }

    // 530
    printf("THE HOUSE LIMIT IS FROM $1 TO $500.\n");

    // 540
    line460();
}

void line370() {
    // 370
    printf("WHAT TWO NUMBERS? ");

    // 380
    INPUT_number(&V);
    printf("?? ");
    INPUT_number(&P);

    // 390
    if (V <= 6 || V >= 1 || P <= 6 || P >= 1) {
        line460();
    }

    // 440
    printf("YOU CAN ONLY BET ON AN INTEGER FROM ONE TO SIX.\n");

    // 450
    line370();
}

void line330() {
    // 330
    line1870();

    // 340
    S2 = V;
    S3 = F;
    line2060();

    // 360
    line3260();
}

void line260() {
    // 260
    printf("WAGER? ");

    // 270
    INPUT_number(&F);

    // 280
    if (F <= 500 || F >= 1) {
        line330();
    }

    // 310
    printf("THE HOUSE LIMIT IS FROM $1 TO $500\n");

    // 320
    line260();
}

void line190() {
    // 190
    printf("WHAT NUMBER? ");

    // 200
    INPUT_number(&V);

    // 210
    if (V <= 6 || V >= 1) {
        line260();
    }

    // 240
    printf("YOU CAN ONLY BET ON AN INTEGER FRON ONE TO SIX.\n");

    // 250
    line190();
}

void line80() {
    // 80
    printf("YOU CANNOT BET ON LESS THAN ONE OR MORE THAN THREE NUMBERS.\n");

    // 90
    p_line90();
}

void line90() {
    // 90
    printf("HOW MANY NUMBERS DO YOU WANT TO BET ON? ");

    // 100
    INPUT_string(&N_str);
    if (strcmp(N_str, "STOP") == 0) {
        line3360();
    }

    // 110
    N_num = VAL(N_str);

    // 120
    if (N_num == 2) {
        line370();
    }

    // 130
    if (N_num == 3) {
        line600();
    }

    // 140
    if (N_num > 3 || N_num < 1) {
        line80();
    }

    // 190
    line190();

    // 260
    line260();

    // 330
    line330();

    // 370
    line370();

    // 460
    line460();

    // 550
    line550();

    // 600
    line600();

    // 710
    line710();

    // 820
    line820();

    // 3260
    line3260();

    // 3350
    // A REMARK!!!1

    // 3360
    line3360();

    // 3380
    line3380();
}

const char *TAB(unsigned int amount_of_spaces) {
    char *spaces = malloc(sizeof(char) * amount_of_spaces);
    for (int i = 0; i < amount_of_spaces; i++) { spaces[i] = ' '; }
    return spaces;
}

int main() {
    initialize_xorshift();
    p_line90 = line90;

    char tab[27];

    // 1
    strcpy(tab, TAB(27));
    printf("%sBIG6\n", tab);

    // 2
    strcpy(tab, TAB(20));
    printf("%sCREATIVE COMPUTING\n", tab);

    // 3
    strcpy(tab, TAB(18));
    printf("%sMORRISTOWN, NEW JERSEY\n", tab);

    // 4
    printf("\n\n\n");

    // 10
    printf("  THIS PROGRAM IS A DICE WHEEL GAME IN WHICH\n");

    // 20
    printf("YOU CAN BET ON ANY NUMBER BETWEEN ONE AND SIX\n");

    // 30
    printf("AND UP TO THREE NUMBERS.\n");

    // 40
    printf("  THE HOUSE LIMIT IS FROM $1 TO $500!!\n");

    // 50
    printf("TO END THIS PROGRAM TYPE THE WORD 'STOP'.\n");

    // 60
    printf("GOOD LUCK!\n");

    // 65
    printf("\n\n");

    // 67
    S_dim = malloc(sizeof(long) * (3 + 1));

    // 70
    p_line90();

    // 80
    line80();
}
