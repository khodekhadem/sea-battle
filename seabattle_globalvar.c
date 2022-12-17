const char *logo = "\033[34m\033[101mSEA\033[31m\033[104mBATTLE\033[0m\n\n";

int is_ended = 0;

//2D array
char *board1;
char *board2;

//3D array -> makan keshtihaie bazikonan
short *ships_pos_p1;
short *ships_pos_p2;

char p1_name[20];
char p2_name[20];

int board_size;

int repair_num;
