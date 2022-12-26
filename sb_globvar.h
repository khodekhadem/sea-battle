#ifndef SEA_BATTLE_SB_GLOBVAR_H
#define SEA_BATTLE_SB_GLOBVAR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(arr, row, col, colN) (*(arr + ((row * colN) + col)))

#define SPACE 10

// erase to end of line
#define erase_line "\33[K"

// move cursor one line up
#define mv_cur_up "\33[A"

// f:forground - b:background
#define f_orange "\033[93m"
#define b_blue "\033[104m"
#define f_darkblue "\033[34m"
#define b_white "\033[107m"
#define f_black "\033[30m"
#define f_darkred "\033[31m"
#define b_darkyellow "\033[43m"
#define b_magenta "\033[37m"
#define f_grey "\033[37m"
#define b_black "\033[40m"
#define b_darkred "\033[41m"
#define color_reset "\033[0m"

#define num_to_char(num) (num + 48)

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define ENTER 'e'
#define EXIT 'q'
#define ATTACK 'e'
#define REPAIR 'r'
#define SAVE 'q'

#ifdef __linux__
#if __linux__
#define cls "clear"
#include <ncurses.h>
#endif
#endif

#ifdef _WIN32
#if _WIN32

#define cls "cls"

#include <conio.h>

#endif
#endif

extern const char *logo;

struct player_info {
    char board[52][52];
    char name[20];
    int ship_number;
    int exploied_ships_number[9];

    //max 9 ship with max 12 part
    int ships_places[9][12][2];
};

extern int is_ended;

extern int board_size;
extern int repair_num;

extern struct player_info p1;
extern struct player_info p2;

extern struct player_info *p[2];

#endif //SEA_BATTLE_SB_GLOBVAR_H
