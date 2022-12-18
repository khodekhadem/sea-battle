const char *logo = "\033[34m\033[101mSEA\033[31m\033[104mBATTLE\033[0m\n\n";

struct player_info {
    char board[52][52];
    char name[20];
    int ship_number;

    //max 9 ship with max 12 part
    int ships_places[9][12][2];
};

int is_ended = 0;

int board_size;
int repair_num;

struct player_info p1;
struct player_info p2;

struct player_info *p[2] = {&p1, &p2};
