#include "sb_globdef.h"

extern int call_dataAvailable(void);

void call_getServer(){
    FILE *serverfile;

#if WIN32
    char *path = "onlineconfig\\online_data.bin";
#elif __linux__
    char *path = "onlineconfig/online_data.bin";
#endif

    while (!call_dataAvailable());

    serverfile = fopen(path, "rb");

    if (!serverfile) {
        printf(">> file can't be opened");
        sleep(1);
        exit(0);
    }

    fread(&p1, sizeof(struct player_info), 1, serverfile);
    fread(&p2, sizeof(struct player_info), 1, serverfile);
    fread(&is_ended, sizeof(int), 1, serverfile);
    fread(&board_size, sizeof(int), 1, serverfile);
    fread(&player, sizeof(int), 1, serverfile);
    fread(&last_player, sizeof(int), 1, serverfile);
    fread(&repair_num, sizeof(int), 1, serverfile);
    fread(&max_part, sizeof(int), 1, serverfile);
    fread(board_cpy, sizeof(char[2][52][52]), 1, serverfile);

    fclose(serverfile);
}