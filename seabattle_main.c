// optimize up to 52*52 board
// optimize for windows

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

extern void call_cli(int[4], int);

extern void call_engine(int *, int[]);

extern void call_menu(void);

/*
    indexes , player info -> b_white , f_black
    water -> b_blue , f_darkblue
    bursted place -> b_blue , f_darkred
    ship -> b_darkyellow , f_grey
    bursted ship -> b_darkred , f_darkred
    just-attack pos -> b_blue , f_darkblue
*/
/*
    water -> ~
    ship -> 1 .. 9
    bursted place , bursted ship , just-attack pos -> X

    note: in map array
    - bursted place -> x
    - bursted ship -> X (capital)
*/
void main_print_board(int attack_i, int attack_j, int status) {
    int _player = player;
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    if (status == 1) {
        printf("\a");
    }

    system(cls);

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
            else if ((_player != player) && (i == attack_i) && (j_temp == attack_j) && (status == 0)) {
                printf("%s%sX %s", b_blue, f_darkblue, color_reset);
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

int check_end() {
    if (p1.ship_number == 0) {
        system(cls);

        printf("Hey %s, You Lose hahaha :)", p1.name);
        sleep(2);

        return 1;
    }

    if (p2.ship_number == 0) {
        system(cls);

        printf("Hey %s, You Lose hahaha :)", p2.name);
        sleep(2);

        return 1;
    }

    return 0;
}

int main() {
    system("mkdir savefiles");
    system(cls);

    for (int i = 0; i < 9; ++i) {
        p[0]->bursted_ships_number[i] = 0;
        p[1]->bursted_ships_number[i] = 0;
    }

    p[0]->bursting_ship_no = 0;
    p[1]->bursting_ship_no = 0;

    // attacker + pos_of_attack_i + pos_of_attack_j + command -> 4 member
    int cli_result[4] = {0,0,0,0};
    //bursting alert
    int engine_result = 1;

    printf("%s", logo);

    sleep(2);
    system(cls);

    call_menu();

    while (!is_ended) {
        call_cli(cli_result, engine_result);
        call_engine(&engine_result, cli_result);
        main_print_board(cli_result[1], cli_result[2], engine_result);

        sleep(1);

        is_ended = check_end();
    }

    return 0;
}