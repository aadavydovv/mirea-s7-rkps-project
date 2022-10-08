#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//@clion_formatter:off
#include <emscripten.h>
EM_JS(void, js_print, (const char* line), { out(UTF8ToString(line)); });
//@clion_formatter:on

char* N_str;
long* S_dim;
int A, B, C, C1;
long F, S2, S3, P, I, S_num, J, X, TE, N_num, V;
unsigned int state_of_xorshift;

long W = 0;
char print_buffer[512] = {0};

void print() {
    js_print(print_buffer);
    emscripten_sleep(20);
}

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
long VAL(char* string) {
    char* endptr;
    long number = strtol(string, &endptr, 10);
    return number;
}

void INPUT_string(char** p_target) {
    const int max_length_of_string = 64;
    int size_of_string = (int) sizeof(char) * max_length_of_string;
    *p_target = malloc(size_of_string);
    fgets(*p_target, size_of_string, stdin);
    strtok(*p_target, "\n");
}

void INPUT_number(long* p_target) {
    char* p_number_as_string;
    INPUT_string(&p_number_as_string);
    *p_target = VAL(p_number_as_string);
}

void (* p_line90)();

void line3440() {
    // 3440
    exit(0);
}

void line3410() {
    // 3410
    sprintf(print_buffer, "YOU WON EXACTLY $ %ld !! NOT BAD !!!", W);
    print();

    // 3440
    line3440();
}

void line3380() {
    // 3380
    sprintf(print_buffer, "YOU DIDN'T WIN ANY MONEY, BUT I'M WILLING TO CALL IT EVEN!!");
    print();

    // 3390
    line3440();
}

void line3360() {
    // 3360
    sprintf(print_buffer, "\nSO YOU WANT TO CASH IN YOUR CHIPS, I SEE!!");
    print();

    // 3370
    if (W > 0) {
        line3410();
    }

    // 3380
    line3380();
}

void line3260() {
    // 3260
    if (W == 0) {
        sprintf(print_buffer, "YOU'RE EVEN!!\n");
        print();
    }

    // 3270
    if (W > 0) {
        sprintf(print_buffer, "YOU'RE AHEAD $ %ld\n", W);
        print();
    }

    // 3280
    if (W < 0) {
        sprintf(print_buffer, "YOU'RE BEHIND $%ld\n", W);
        print();
    }

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
        sprintf(print_buffer, "YOU WIN  %d  TIMES ON: %ld", C1, S2);
        print();
    } else {
        // 2110
        S3 *= -1;

        // 2120
        sprintf(print_buffer, "YOU LOSE ON:  %ld", S2);
        print();
    }

    // 2150
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
    sprintf(print_buffer, "THE LUCKY NUMBERS ARE:  %ld  %ld  %ld", S_dim[1], S_dim[2], S_dim[3]);
    print();

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
    sprintf(print_buffer, "WAGER ON EACH OF THE THREE? ");
    print();

    // 720
    INPUT_number(&F);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&I);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&J);

    // 730
    if (F <= 500 || F >= 1 || I <= 500 || I >= 1 || J <= 500 || J >= 1) {
        line820();
    }

    // 800
    sprintf(print_buffer, "THE HOUSE LIMIT IS FROM $1 TO $500.");
    print();

    // 810
    line710();
}

void line600() {
    sprintf(print_buffer, "WHAT THREE NUMBERS? ");
    print();

    // 610
    INPUT_number(&V);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&P);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&S_num);

    // 620
    if (V <= 6 || V >= 1 || P <= 6 || P >= 1 || S_num <= 6 || S_num >= 1) {
        line710();
    }

    // 690
    sprintf(print_buffer, "YOU CAN ONLY BET ON AN INTEGER FROM ONE TO SIX.");
    print();

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
    sprintf(print_buffer, "WAGER ON BOTH? ");
    print();

    // 470
    INPUT_number(&F);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&I);

    // 480
    if (F <= 500 || F >= 1 || I <= 500 || I >= 1) {
        line550();
    }

    // 530
    sprintf(print_buffer, "THE HOUSE LIMIT IS FROM $1 TO $500.");
    print();

    // 540
    line460();
}

void line370() {
    // 370
    sprintf(print_buffer, "WHAT TWO NUMBERS? ");
    print();

    // 380
    INPUT_number(&V);
    sprintf(print_buffer, "?? ");
    print();
    INPUT_number(&P);

    // 390
    if (V <= 6 || V >= 1 || P <= 6 || P >= 1) {
        line460();
    }

    // 440
    sprintf(print_buffer, "YOU CAN ONLY BET ON AN INTEGER FROM ONE TO SIX.");
    print();

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
    sprintf(print_buffer, "WAGER? ");
    print();

    // 270
    INPUT_number(&F);

    // 280
    if (F <= 500 || F >= 1) {
        line330();
    }

    // 310
    sprintf(print_buffer, "THE HOUSE LIMIT IS FROM $1 TO $500");
    print();

    // 320
    line260();
}

void line190() {
    // 190
    sprintf(print_buffer, "WHAT NUMBER? ");
    print();

    // 200
    INPUT_number(&V);

    // 210
    if (V <= 6 || V >= 1) {
        line260();
    }

    // 240
    sprintf(print_buffer, "YOU CAN ONLY BET ON AN INTEGER FRON ONE TO SIX.");
    print();

    // 250
    line190();
}

void line80() {
    // 80
    sprintf(print_buffer, "YOU CANNOT BET ON LESS THAN ONE OR MORE THAN THREE NUMBERS.");
    print();

    // 90
    p_line90();
}

void line90() {
    // 90
    sprintf(print_buffer, "HOW MANY NUMBERS DO YOU WANT TO BET ON? ");
    print();

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

const char* TAB(unsigned int amount_of_spaces) {
    char* spaces = malloc(sizeof(char) * amount_of_spaces);
    for (int i = 0; i < amount_of_spaces; i++) { spaces[i] = ' '; }
    return spaces;
}

int main() {
    initialize_xorshift();
    p_line90 = line90;

    char tab[27] = {0};

    // 1
    strcpy(tab, TAB(27));
    sprintf(print_buffer, "%sBIG6", tab);
    print();

    // 2
    strcpy(tab, TAB(21));
    sprintf(print_buffer, "%sCREATIVE COMPUTING", tab);
    print();

    // 3
    strcpy(tab, TAB(18));
    sprintf(print_buffer, "%sMORRISTOWN, NEW JERSEY", tab);
    print();

    // 4
    sprintf(print_buffer, "\n\n");
    print();

    // 10
    sprintf(print_buffer, "  THIS PROGRAM IS A DICE WHEEL GAME IN WHICH");
    print();

    // 20
    sprintf(print_buffer, "YOU CAN BET ON ANY NUMBER BETWEEN ONE AND SIX");
    print();

    // 30
    sprintf(print_buffer, "AND UP TO THREE NUMBERS.");
    print();

    // 40
    sprintf(print_buffer, "  THE HOUSE LIMIT IS FROM $1 TO $500!!");
    print();

    // 50
    sprintf(print_buffer, "TO END THIS PROGRAM TYPE THE WORD 'STOP'.");
    print();

    // 60
    sprintf(print_buffer, "GOOD LUCK!");
    print();

    // 65
    sprintf(print_buffer, "\n");
    print();

    // 67
    S_dim = malloc(sizeof(long) * (3 + 1));

    // 70
    p_line90();

    // 80
    line80();
}
