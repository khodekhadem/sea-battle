#include "sb_globdef.h"

extern void call_download(void);

extern int call_dataAvailable(void);

void call_getServer(){
    FILE *serverfile;
    char path[50] = "onlineconfig\\other.bin";

#ifdef __linux__
#if __linux__
    path[9] = '/';
#endif
#endif

    while (!call_dataAvailable());

    call_download();
    
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
    fread(&ship_part_number, sizeof(int), 1, serverfile);
    fread(board_cpy, sizeof(char[2][52][52]), 1, serverfile);

    fclose(serverfile);
}