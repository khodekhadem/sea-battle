#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SPACE 10

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(arr, row, col, colN) *(arr + ((row * colN) + col))

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
#define b_magenta "\033[37m"
#define f_grey "\033[37m"
#define b_black "\033[40m"
#define b_darkred "\033[41m"
#define color_reset "\033[0m"

#ifdef __linux__
#if __linux__
#define cls "clear"
#endif
#endif

#ifdef _WIN32
#if _WIN32
#define cls "cls"
#endif
#endif

/*
    error -> f_darkyellow
    pointers -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
    ship -> b_magenta , f_grey
    exploied ship -> b_darkred
*/
/*
    water -> ~
    ship -> 1 .. 9
    exploied place -> X
*/

// attacker + pos_of_attack + command
int *output;

int *call_cli(int turn, int *arg)
{
    switch (turn)
    {
    case 1:
        break;

    case 0:
        break;
    }

    return output;
}