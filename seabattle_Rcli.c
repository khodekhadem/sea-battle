#include <stdio.h>
#include <stdlib.h>
#include "sb_globvar.h"

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

#define num_to_char(num) (num + 48)

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

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define ENTER 'e'

/*
    error -> f_darkyellow
    pointers -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
    ship -> b_magenta , f_grey
    exploied ship -> b_darkred
    selector ship -> b_black
*/
/*
    water -> ~

    ship -> 1 .. 9
    exploied place -> X
*/

void board_creator(char board[][52]) {
    // water
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j] = '~';
        }
    }
}

int exist_selector_ship(int i, int j, int ship_pos[][2]) {
    for (int k = 0; k < 3; k++) {
        if ((ship_pos[k][0] == i) && (ship_pos[k][1] == j)) {
            return 1;
        }
    }

    return 0;
}

void print_board(int ship[][2], int player) {
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    printf("%s\n\n", p[player]->name);

    printf("%s%s   %s",b_white, f_black, color_reset);

    for (int i = 0; i < board_size; i++) {
        printf("%s%s%c %s", b_white, f_black, characters[i], color_reset);
    }

    printf("\n");

    for (int i = 0; i < board_size; i++) {
        for (int j = -1; j < board_size; j++) {
            if (j == -1) {
                printf("%s%s%2d %s", b_white, f_black, i + 1, color_reset);
            }
            else if (exist_selector_ship(i, j, ship)) {
                printf("%s  %s", b_black, color_reset);
            }
            else {
                if (p[player]->board[i][j] == '~') {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else {
                    printf("%s%s%c %s", b_magenta, f_grey, p[player]->board[i][j], color_reset);
                }
            }
        }

        printf("\n");
    }
}

void ship_pos_creator(int ship_pos[][2], int i, int j) {
    int k = 0;

    for (int i_temp = 0; i_temp < i; i_temp++) {
        for (int j_temp = 0; j_temp < j; j_temp++) {
            ++k;

            ship_pos[k][0] = i_temp;
            ship_pos[k][1] = j_temp;
        }
    }
}

void move_selector_ship(char mode, int ship_pos[][2]) {
    switch (mode) {
        case 'U':
            for (int i = 0; i < 3; i++) {
                if (ship_pos[i][0] - 1 == -1) {
                    return;
                }
            }
            for (int i = 0; i < 3; i++) {
                --ship_pos[i][0];
            }

            break;

        case 'D':
            for (int i = 0; i < 3; i++) {
                if (ship_pos[i][0] + 1 == board_size) {
                    return;
                }
            }
            for (int i = 0; i < 3; i++) {
                ++ship_pos[i][0];
            }

            break;

        case 'R':
            for (int i = 0; i < 3; i++) {
                if (ship_pos[i][1] + 1 == board_size) {
                    return;
                }
            }
            for (int i = 0; i < 3; i++) {
                ++ship_pos[i][1];
            }

            break;

        case 'L':
            for (int i = 0; i < 3; i++) {
                if (ship_pos[i][1] - 1 == -1) {
                    return;
                }
            }
            for (int i = 0; i < 3; i++) {
                --ship_pos[i][1];
            }

            break;
    }
}

void put_ship(int player, int ship_pos[][2]) {
    static int ship_no = 1;

    for (int i = 0; i < 3; i++) {
        p[player]->board[ship_pos[i][0]][ship_pos[i][1]] = num_to_char(ship_no);
    }

    ++ship_no;
}

void ship_pos_to_ships_places(int player, int ship_pos[][2]) {
    static int ship_no = 0;

    for (int i = 0; i < 3; ++i) {
        p[player]->ships_places[ship_no][i][0] = ship_pos[i][0];
        p[player]->ships_places[ship_no][i][1] = ship_pos[i][1];
    }
}

// 0 -> normal , 1 -> exit
void ship_creator(int player) {
    system(cls);

    //... & ij
    int ship_pos[3][2];
    int _continue = 1;

    printf("how is your ship? vertical <v> or horizontal <h> : ");

    switch (getch()) {
        case 'v':
            printf("v");
            ship_pos_creator(ship_pos, 3, 1);

            break;

        case 'h':
            printf("h");
            ship_pos_creator(ship_pos, 1, 3);

            break;
    }

    system(cls);

    while (_continue) {
        system(cls);

        print_board(ship_pos, player);

        switch (getch()) {
            case UP:
                move_selector_ship('U', ship_pos);

                break;

            case DOWN:
                move_selector_ship('D', ship_pos);

                break;

            case RIGHT:
                move_selector_ship('R', ship_pos);

                break;

            case LEFT:
                move_selector_ship('L', ship_pos);

                break;

            case ENTER:
                put_ship(player, ship_pos);
                ship_pos_to_ships_places(player, ship_pos);
                _continue = 0;
                break;
        }
    }

    system(cls);
}
#include <unistd.h>

void call_Rcli() {
#ifdef __linux__
#if __linux__
    initscr();
    noecho();
    cbreak();
#endif
#endif

    printf("please write size of map (1 .. 52)\n");

    scanf("%d", &board_size);

    while (board_size < 1 || 52 < board_size) {
        printf("%s!!!your number either lower than 1 or grather than 52 --- please write it again%s\n", f_darkyellow,
               color_reset);
        scanf("%d", &board_size);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }

    system(cls);

    printf("write player1 name (max = 19 character) : ");
    scanf("%s", p1.name);
    printf("\nwrite player2 name (max = 19 character) : ");
    scanf("%s", p2.name);

    system(cls);

    printf("write number of ships (max = 9) : ");
    scanf("%d", &p1.ship_number);
    if (p1.ship_number > 9) {
        p1.ship_number %= 9;
        ++p1.ship_number;
    }
    p2.ship_number = p1.ship_number;

    board_creator(p1.board);
    board_creator(p2.board);

    for (int i = 0; i < p1.ship_number; i++) {
        ship_creator(0);
    }

    for (int i = 0; i < p2.ship_number; i++) {
        ship_creator(1);
    }

#ifdef __linux__
#if __linux__
    endwin();
#endif
#endif
}