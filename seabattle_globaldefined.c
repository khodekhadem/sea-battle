#ifdef __linux__
#if __linux__
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#endif
#endif

const char *logo = "\033[34m\033[101mSEA\033[31m\033[104mBATTLE\033[0m\n\n";

struct player_info {
    char board[52][52];
    char name[20];
    int ship_number;
    int bursted_ships_number[9];

    //max 9 ship with max 12 part
    int ships_places[9][12][2];
};

int is_ended = 0;

int board_size;
int repair_num;

int player = 0;
int last_player = 0;

struct player_info p1;
struct player_info p2;

struct player_info *p[2] = {&p1, &p2};

#ifdef __linux__
#if __linux__

// emulate conio.h getch in linux
int getch() {\
    struct termios oldt, newt;\
    int ch;\
    tcgetattr(STDIN_FILENO, &oldt);\
    newt = oldt;\
    newt.c_lflag &= ~(ICANON | ECHO);\
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);\
    ch = getchar();\
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);\
    return ch;\
}

#endif
#endif
