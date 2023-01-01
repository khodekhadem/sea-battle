#include "sb_globvar.h"

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

void Rcli_print_board(int selector[][2], int player) {
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    printf("w,a,s,d -> move / e -> enter\n\n");

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
            else if (exist_selector(3, i, j, selector)) {
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

void put_ship(int player, int selector[][2]) {
    static int ship_no = 1;
    static int last_player = 0;

    if (player != last_player) {
        ship_no = 1;
    }

    for (int i = 0; i < 3; i++) {
        p[player]->board[selector[i][0]][selector[i][1]] = num_to_char(ship_no);
    }

    ++ship_no;

    last_player = player;
}

void selector_to_ships_places(int player, int selector[][2]) {
    static int ship_no = 0;
    static int last_player = 0;
    int i;

    if (player != last_player) {
        ship_no = 0;
    }

    for (i = 0; i < 3; ++i) {
        p[player]->ships_places[ship_no][i][0] = selector[i][0];
        p[player]->ships_places[ship_no][i][1] = selector[i][1];
    }

    p[player]->ships_places[ship_no][i][0] = -1;
    p[player]->ships_places[ship_no][i][1] = -1;

    ++ship_no;

    last_player = player;
}

int is_another_ship_available(int player, int selector[][2]) {
    int k = 0;

    for (int i = 0; i < 3; ++i) {
        if (p[player]->board[selector[k][0]][selector[k][1]] != '~') {
            return 1;
        }

        ++k;
    }

    return 0;
}

// 0 -> normal , 1 -> exit
void ship_creator(int player) {
    system(cls);

    //... & ij
    int selector[3][2];

    printf("%s%s%s%s\n\n", b_white, f_black, p[player]->name, color_reset);
    printf("how is your ship? vertical <v> or horizontal <h> : ");

    switch (getch()) {
        case 'v':
            printf("v");
            selector_creator(selector, 3, 1);

            break;

        case 'h':
            printf("h");
            selector_creator(selector, 1, 3);

            break;
    }

    int _continue = 1;

    while (_continue) {
        system(cls);

        Rcli_print_board(selector, player);

        switch (getch()) {
            case UP:
                move_selector('U', selector, 3);

                break;

            case DOWN:
                move_selector('D', selector, 3);

                break;

            case RIGHT:
                move_selector('R', selector, 3);

                break;

            case LEFT:
                move_selector('L', selector, 3);

                break;

            case ENTER:
                if (is_another_ship_available(player, selector)) {
                    continue;
                }

                put_ship(player, selector);
                selector_to_ships_places(player, selector);
                _continue = 0;
                break;
        }
    }

    system(cls);
}

void change_player() {
    system(cls);

    printf("PLEASE change player...");

    sleep(2);
}

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
        printf("%s!!!your number either lower than 1 or grather than 52 --- please write it again%s\n", f_orange,
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
    while (p1.ship_number < 1) {
        printf("%s!!!your number must be bigger than 0%s\n", f_orange,
               color_reset);
        scanf("%d", &p1.ship_number);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }
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

    change_player();

    for (int i = 0; i < p2.ship_number; i++) {
        ship_creator(1);
    }

#ifdef __linux__
#if __linux__
    endwin();
#endif
#endif
}