#include "sb_globdef.h"

/*
    error -> f_orange
    indexes , player info -> b_white , f_black
    water -> b_blue , f_darkblue
    ship -> b_darkyellow , f_grey
    selector -> b_black
*/
/*
    water -> ~
    ship -> 1 .. 9
*/

void copy_2Dchar_array(int row, int coln, char *dest_arr, char *scr_arr) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < coln; ++j) {
            pos(dest_arr, i, j, coln) = pos(scr_arr, i, j, coln);
        }
    }
}

void board_creator(char board[][52]) {
    // water
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j] = '~';
        }
    }
}

int exist_selector(int n, int i, int j, int selector[][2]) {
    for (int k = 0; k < n; k++) {
        if ((selector[k][0] == i) && (selector[k][1] == j)) {
            return 1;
        }
    }

    return 0;
}

void Rcli_print_board(int selector[][2], int len) {
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    printf("w,a,s,d -> move / e -> enter / q -> exit\n\n");

    printf("%s%splayer name : %s%s\n\n", b_white, f_black, p[player]->name, color_reset);

    printf("%s%s   %s", b_white, f_black, color_reset);

    for (int i = 0; i < board_size; i++) {
        printf("%s%s%c %s", b_white, f_black, characters[i], color_reset);
    }

    printf("\n");

    for (int i = 0; i < board_size; i++) {
        for (int j = -1; j < board_size; j++) {
            if (j == -1) {
                printf("%s%s%2d %s", b_white, f_black, i + 1, color_reset);
            }
            else if (exist_selector(len, i, j, selector)) {
                printf("%s  %s", b_black, color_reset);
            }
            else {
                if (p[player]->board[i][j] == '~') {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else {
                    printf("%s%s%c %s", b_darkyellow, f_grey, p[player]->board[i][j], color_reset);
                }
            }
        }

        printf("\n");
    }
}

void selector_creator(int selector[][2], int i, int j) {
    int k = 0;

    for (int i_temp = 0; i_temp < i; i_temp++) {
        for (int j_temp = 0; j_temp < j; j_temp++) {
            selector[k][0] = i_temp;
            selector[k][1] = j_temp;

            ++k;
        }
    }
}

void move_selector(char mode, int selector[][2], int len) {
    switch (mode) {
        case 'U':
            for (int i = 0; i < len; i++) {
                if (selector[i][0] - 1 == -1) {
                    return;
                }
            }
            for (int i = 0; i < len; i++) {
                selector[i][0]--;
            }

            break;

        case 'D':
            for (int i = 0; i < len; i++) {
                if (selector[i][0] + 1 == board_size) {
                    return;
                }
            }
            for (int i = 0; i < len; i++) {
                selector[i][0]++;
            }

            break;

        case 'R':
            for (int i = 0; i < len; i++) {
                if (selector[i][1] + 1 == board_size) {
                    return;
                }
            }
            for (int i = 0; i < len; i++) {
                selector[i][1]++;
            }

            break;

        case 'L':
            for (int i = 0; i < len; i++) {
                if (selector[i][1] - 1 == -1) {
                    return;
                }
            }
            for (int i = 0; i < len; i++) {
                selector[i][1]--;
            }

            break;
    }
}

void put_ship(int selector[][2], int len) {
    static int ship_no = 1;

    if (player != last_player) {
        ship_no = 1;
    }

    for (int i = 0; i < len; i++) {
        p[player]->board[selector[i][0]][selector[i][1]] = num_to_char(ship_no);
    }

    ++ship_no;
}

void selector_to_ships_places(int selector[][2], int len) {
    static int ship_no = 0;
    int i;

    if (player != last_player) {
        ship_no = 0;

        last_player = player;
    }

    for (i = 0; i < len; ++i) {
        p[player]->ships_places[ship_no][i][0] = selector[i][0];
        p[player]->ships_places[ship_no][i][1] = selector[i][1];
    }

    p[player]->ships_places[ship_no][i][0] = -1;
    p[player]->ships_places[ship_no][i][1] = -1;

    ++ship_no;

    ++(p[player]->ship_number);
}

int is_another_ship_available(int selector[][2], int len) {
    int k = 0;

    for (int i = 0; i < len; ++i) {
        if (p[player]->board[selector[k][0]][selector[k][1]] != '~') {
            return 1;
        }

        ++k;
    }

    return 0;
}

int ship_creator() {
    int row, col;
    system(cls);

    //... & ij
    int selector[12][2];

    printf("%s%s%s%s\n\n", b_white, f_black, p[player]->name, color_reset);
    printf("write row and col of your ship (max part = 12) (e.g. 2 3 for 2*3)\n");
    printf("(escape of add ship => enter 0 0) (remain = %d) : ", ship_part_number - p[player]->total_part);

    scanf("%d%d", &row, &col);

    while (1) {
        if ((row == 0 && col == 0) && (p[player]->ship_number == 0)) {
            printf("%s!!!you must at least have 1 ship. write it again.%s\n", f_orange, color_reset);
            scanf("%d%d", &row, &col);

            printf("%s%s", mv_cur_up, erase_line);
            printf("%s%s", mv_cur_up, erase_line);

        }
        else {
            break;
        }
    }

    if (row == 0 && col == 0) {
        return 0;
    }

    while ((row * col) < 1 || (row * col) > 12 || (row > board_size) || (col > board_size) || (row < 1) || (col < 1)) {
        printf("%s!!!your numbers is incorrect. write it again.%s\n", f_orange, color_reset);
        scanf("%d%d", &row, &col);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }
    while ((row * col) + p[player]->total_part > ship_part_number) {
        printf("%s!!!parts over limit%s\n", f_orange, color_reset);
        scanf("%d%d", &row, &col);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }

    selector_creator(selector, row, col);
    p[player]->total_part += row * col;

    while (1) {
        system(cls);

        Rcli_print_board(selector, row * col);

        switch (getch()) {
            case UP:
                move_selector('U', selector, row * col);

                break;

            case DOWN:
                move_selector('D', selector, row * col);

                break;

            case RIGHT:
                move_selector('R', selector, row * col);

                break;

            case LEFT:
                move_selector('L', selector, row * col);

                break;

            case ENTER:
                if (is_another_ship_available(selector, row * col)) {
                    continue;
                }

                put_ship(selector, row * col);
                selector_to_ships_places(selector, row * col);
                system(cls);

                return 1;

            case EXIT:
                exit(0);
        }
    }
}

void call_Rcli() {
    int _continue_selector;

    printf("write player%d name (max = 19 character) : ", player + 1);
    scanf("%s", p[player]->name);

    system(cls);

    board_creator(p[player]->board);

    _continue_selector = 1;
    while (_continue_selector) {
        if (p[player]->total_part == ship_part_number) {
            break;
        }
        _continue_selector = ship_creator();
    }

    copy_2Dchar_array(52, 52, board_cpy[player], p[player]->board);
}