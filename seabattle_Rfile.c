#include "sb_globvar.h"
#include <string.h>

void call_Rfile(const char savefile_path[]) {
    FILE *savefile;

    char path[50] = "savefiles\\sb_savefile";
    strcat(path, savefile_path);
    strcat(path, ".bin");

    savefile = fopen(path, "rb");

    if (!savefile) {
        printf(">> your save file doesn't exist");
        sleep(1);
        exit(0);
    }

    fread(&p1, sizeof(struct player_info), 1, savefile);
    fread(&p2, sizeof(struct player_info), 1, savefile);
    fread(&is_ended, sizeof(int), 1, savefile);
    fread(&board_size, sizeof(int), 1, savefile);
    fread(&player, sizeof(int), 1, savefile);
    fread(&last_player, sizeof(int), 1, savefile);

    fclose(savefile);
}
