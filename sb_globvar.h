#ifndef SEA_BATTLE_SB_GLOBVAR_H
#define SEA_BATTLE_SB_GLOBVAR_H

extern const char *logo;

struct player_info {
    char board[52][52];
    char name[20];
    int ship_number;

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
