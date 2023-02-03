#include "sb_globdef.h"

void call_save() {
    static int save_number[2] = {1, 1};
    FILE *savefile;
    char path[50] = "savefiles\\sb_savefile";
    char num[5];

#ifdef __linux__
#if __linux__
    path[9] = '/';
#endif
#endif

    sprintf(num, "%d", save_number[player]);
    strcat(path, "-");
    strcat(path, p[player]->name);
    strcat(path, "-");
    strcat(path, num);
    strcat(path, ".bin");

    savefile = fopen(path, "wb");

    if (!savefile) {
        printf(">> file can't be opened");
        sleep(1);
        exit(0);
    }

    fwrite(&p1, sizeof(struct player_info), 1, savefile);
    fwrite(&p2, sizeof(struct player_info), 1, savefile);
    fwrite(&is_ended, sizeof(int), 1, savefile);
    fwrite(&board_size, sizeof(int), 1, savefile);
    fwrite(&player, sizeof(int), 1, savefile);
    fwrite(&last_player, sizeof(int), 1, savefile);
    fwrite(&repair_num, sizeof(int), 1, savefile);
    fwrite(&ship_part_number, sizeof(int), 1, savefile);
    fwrite(board_cpy, sizeof(char[2][52][52]), 1, savefile);

    fclose(savefile);

    ++save_number[player];
}

