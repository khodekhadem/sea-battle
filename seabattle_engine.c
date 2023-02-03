#include "sb_globdef.h"

/*
    water -> ~
    ship -> 1 .. 9
    bursted place , bursted ship , just-attack pos -> X

    note: in map array
    - bursted place -> x
    - bursted ship -> X (capital)
*/

void burst_place(int defender, int i, int j) {
    // first char to num then change 1 -> 0 and 2 -> 1 and ... for array indexing
    int ship_no = p[defender]->board[i][j] - 48 - 1;
    int all_bursted = 1;
    int k = 0;
    int temp1, temp2;

    p[defender]->board[i][j] = 'x';

    while (p[defender]->ships_places[ship_no][k][0] != -1) {
        temp1 = p[defender]->ships_places[ship_no][k][0];
        temp2 = p[defender]->ships_places[ship_no][k][1];

        if (p[defender]->board[temp1][temp2] != 'x') {
            all_bursted = 0;

            break;
        }

        ++k;
    }

    k = 0;

    if (all_bursted == 1) {
        while (p[defender]->ships_places[ship_no][k][0] != -1) {
            temp1 = p[defender]->ships_places[ship_no][k][0];
            temp2 = p[defender]->ships_places[ship_no][k][1];

            p[defender]->board[temp1][temp2] = 'X';

            ++k;
        }

        --(p[defender]->ship_number);
        ++(p[defender]->bursting_ship_no);
    }
}

int attack_on_ships(int attacker, int i_attack, int j_attack) {
    int defender = attacker + 1;
    defender %= 2;

    //ship available
    if (48 <= p[defender]->board[i_attack][j_attack] && p[defender]->board[i_attack][j_attack] <= 57) {
        burst_place(defender, i_attack, j_attack);
        return 1;
    }
    else if(p[defender]->board[i_attack][j_attack] == '~') {
        p[defender]->board[i_attack][j_attack] = '&';
    }

    return 0;
}

void repair_ship(int repairman, int i_repair, int j_repair) {
    int ship_no;
    char ch[2];

    if (p[repairman]->board[i_repair][j_repair] == 'x') {
        p[repairman]->board[i_repair][j_repair] = board_cpy[repairman][i_repair][j_repair];
    }
    else if (p[repairman]->board[i_repair][j_repair] == 'X') {
        sprintf(ch, "%c", board_cpy[repairman][i_repair][j_repair]);
        ship_no = strtol(ch, NULL, 10);
        --ship_no; // start from 1 to start from 0
        --(p[repairman]->bursting_ship_no);
        ++(p[repairman]->ship_number);

        for (int i = 0; p[repairman]->ships_places[ship_no][i][0] != -1; ++i) {
            p[repairman]->board[p[repairman]->ships_places[ship_no][i][0]][p[repairman]->ships_places[ship_no][i][1]] = 'x';
        }
        p[repairman]->board[i_repair][j_repair] = board_cpy[repairman][i_repair][j_repair];
    }
}

// result : bursting alert
// arg : attacker + pos_of_attack_i + pos_of_attack_j + command -> 4 member
// 0 : attack
// 1 : repair
void call_engine(int *result, int arg[4]) {
    switch (arg[3]) {
        case 0:
            *result = attack_on_ships(arg[0], arg[1], arg[2]);

            break;

        case 1:
            ++(p[arg[0]]->repair_used);
            repair_ship(arg[0], arg[1], arg[2]);
            *result = 0;

            break;
    }
}