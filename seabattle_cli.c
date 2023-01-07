#include "sb_globvar.h"

/*
    indexes , player info -> b_white , f_black
    water -> b_blue , f_darkblue
    bursted place -> b_blue , f_darkred
    ship -> b_darkyellow , f_grey
    bursted ship -> b_darkred , f_darkred
    selector -> b_black
*/
/*
    water -> ~
    ship -> 1 .. 9
    bursted place , bursted ship -> X

    note: in map array
    - bursted place -> x
    - bursted ship -> X (capital)
*/

extern int exist_selector(int, int, int, int(*)[]);

extern void move_selector(char, int(*)[], int);

extern void change_player(void);

void cli_print_board(int selector[][2]) {
    int _player = player;
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    printf("w,a,s,d -> move / e -> enter\n\n");

    printf("%s%splayer name : %s%s\n", b_white, f_black, p[_player]->name, color_reset);

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

    int j_temp;

    for (int i = 0; i < board_size; i++) {
        j_temp = -1;
        _player = player;

        for (int j = -1; j < (2 * board_size) + 2; j++) {
            if (j == -1 || j == board_size + 1) {
                printf("%s%s%2d %s", b_white, f_black, i + 1, color_reset);
            }
            else if (exist_selector(1, i, j_temp, selector) && _player != player) {
                printf("%s  %s", b_black, color_reset);
            }
            else if (j == board_size) {
                for (int k = 0; k < SPACE; ++k) {
                    printf(" ");
                }

                ++_player;
                _player %= 2;

                j_temp = -2;
            }
            else {
                if (p[_player]->board[i][j_temp] == '~') {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else if (p[_player]->board[i][j_temp] == 'X') {
                    printf("%s%sX %s", b_darkred, f_darkred, color_reset);
                }
                else if (p[_player]->board[i][j_temp] == 'x') {
                    printf("%s%sX %s", b_blue, f_darkred, color_reset);
                }

                if (_player == player) {
                    if (p[_player]->board[i][j_temp] > 47 && p[_player]->board[i][j_temp] < 58) {
                        printf("%s%s%c %s", b_darkyellow, f_grey, p[player]->board[i][j], color_reset);
                    }
                }
                else {
                    if (p[_player]->board[i][j_temp] > 47 && p[_player]->board[i][j_temp] < 58) {
                        printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                    }
                }
            }

            ++j_temp;
        }

        printf("\n");
    }
}

//1 : attack
//2 : repair
//3 : save
int proc_selector(int selector[][2]) {
    int _continue = 1;
    int cmd = 0;

    while (_continue) {
        system(cls);

        cli_print_board(selector);

        switch (getch()) {
            case UP:
                move_selector('U', selector, 1);

                break;

            case DOWN:
                move_selector('D', selector, 1);

                break;

            case RIGHT:
                move_selector('R', selector, 1);

                break;

            case LEFT:
                move_selector('L', selector, 1);

                break;

            case ENTER:
                cmd = 1;
                _continue = 0;

                break;
        }
    }

    return cmd;
}

//result : attacker + pos_of_attack_i + pos_of_attack_j + command
void call_cli(int result[4], int burst_alert) {
    int selector[1][2] = {{0, 0}};
    int command;
    int temp;

    if (burst_alert != 1) {
        last_player = player;
        ++player;
        player %= 2;
    }

    if (last_player != player) {
        change_player();
        last_player = player;
    }


    command = proc_selector(selector);

    result[0] = player;
    result[1] = selector[0][0];
    result[2] = selector[0][1];
    result[3] = command;
}