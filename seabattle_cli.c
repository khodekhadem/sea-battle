#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SPACE 10

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(map, row, col, size) *(map + ((row * size) + col))

#define true_i(i) i + 1
#define true_j(j) j + 1

// return number by char
#define rnbt(ch) ch - 64

// erase to end of line
#define erase_line "\33[K"

// move cursor one line up
#define mv_cur_up "\33[A"

// f:forground - b:background
#define b_blue "\033[104m"
#define f_darkblue "\033[34m"
#define b_white "\033[107m"
#define f_black "\033[30m"
#define f_darkred "\033[31m"
#define f_darkyellow "\033[33m"
#define color_reset "\033[0m"

/*
    error -> f_darkyellow
    pointers -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
    ship -> b_purple , f_grey
*/

/*
    water -> ~
    ship -> 1 .. 9
    exploied place -> X
*/

int* call_cli(int turn, int *arg){
    
}