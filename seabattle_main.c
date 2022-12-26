// optimize up to 52*52 board
// optimize for windows and linux

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sb_globvar.h"

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

extern void call_Rcli(void);

extern void call_cli(int[], int);

extern void call_engine(int, int[]);

int player = 0;
int last_player = 0;


/*
    indexes , player info -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
    ship -> b_darkyellow , f_grey
    exploied ship -> b_darkred , f_darkred
    just-attack pos -> b_blue , f_darkblue
*/
/*
    water -> ~
    ship -> 1 .. 9
    exploied place , exploied ship , just-attack pos -> X

    note: in map array
    - exploied place -> x
    - exploied ship -> X (capital)
*/
void main_print_board(int attack_i, int attack_j, int status) {
    int _player = player;
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    printf("%s%s%s%s\n", b_white, f_black, p[_player]->name, color_reset);

    //------------------------------------------

    printf("%s%sremain enemy's ships : %d%s\n\n", b_white, f_black, p[(_player + 1) % 2]->ship_number, color_reset);

    //------------------------------------------

    printf("%s%s   %s", b_white, f_black, color_reset);
    for (int j = 0; j < board_size; j++) {
        printf("%s%s%c %s", b_white, f_black, characters[j], color_reset);
    }
    for (int i = 0; i < SPACE; ++i) {
        printf(" ");
    }
    printf("%s%s   %s", b_white, f_black, color_reset);
    for (int j = 0; j < board_size; j++) {
        printf("%s%s%c %s", b_white, f_black, characters[j], color_reset);
    }
    printf("\n");

    //------------------------------------------

    for (int i = 0; i < board_size; i++) {
        for (int j = -1; j < (2 * board_size) + SPACE; j++) {
            if (j == -1 || j == SPACE - 1) {
                printf("%s%s%2d %s", b_white, f_black, i + 1, color_reset);
            }
            else if (j == board_size) {
                for (int k = 0; k < SPACE; ++k) {
                    printf(" ");
                }
            }
            else {
                if (p[_player]->board[i][j] == '~') {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else if (p[_player]->board[i][j] == 'X') {
                    printf("%s%sX %s", b_darkred, f_darkred, color_reset);
                }
                else if (p[_player]->board[i][j] == 'x') {
                    printf("%s%sX %s", b_blue, f_darkred, color_reset);
                }
                else if ((i == attack_i) && (j = attack_j) && (status == 0)) {
                    printf("%s%sX %s", b_blue, f_darkblue, color_reset);
                }

                if (_player == player) {
                    printf("%s%s%c %s", b_darkyellow, f_grey, p[player]->board[i][j], color_reset);
                }

                ++_player;
                _player %= 2;
            }
        }

        printf("\n");
    }
}

int check_end() {
    if (p1.ship_number == 0) {
        system(cls);

        printf("Hey %s, You Lose hahaha :)", p1.name);
        sleep(2);

        return 1;
    }

    if (p1.ship_number == 0) {
        system(cls);

        printf("Hey %s, You Lose hahaha :)", p2.name);
        sleep(2);

        return 1;
    }

    return 0;
}

int main() {
    system(cls);

    for (int i = 0; i < 9; ++i) {
        p[0]->exploied_ships_number[i] = 0;
        p[1]->exploied_ships_number[i] = 0;
    }

    // attacker + pos_of_attack_i + pos_of_attack_j + command -> 4 member
    int cli_result[4];
    //exploision alert + number of exploied ship (not exist => 0) -> 2 member
    int engine_result = 1;

    printf("%s", logo);

    sleep(2);
    system(cls);

    call_Rcli();

    while (!is_ended) {
        call_cli(cli_result, engine_result);
        call_engine(engine_result, cli_result);
        main_print_board(cli_result[1],cli_result[2], engine_result);

        sleep(1);

        is_ended = check_end();
    }

    return 0;
}