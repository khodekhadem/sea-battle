#include "sb_globvar.h"

void call_save() {
    static int save_number = 1;
    FILE *savefile;
    char path[50] = "savefiles\\sb_savefile";
    char num[5];

    sprintf(num, "%d", save_number);
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

    fclose(savefile);
}

