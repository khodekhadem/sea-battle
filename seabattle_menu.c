#include <dirent.h>
#include "sb_globdef.h"

extern void call_Rcli(void);

extern void call_Rcli_gi(void);

extern void call_Rfile(const char *);

extern void call_getServer(void);

extern void call_sendServer(void);

void change_player() {
    system(cls);

    printf("PLEASE change player...");
    fflush(stdout);

    sleep(2);
}

void show_save() {
    DIR *dir;
    struct dirent *dir_content;
    char path[4];
    char filename[100][50];

    dir = opendir("savefiles");

    if (!dir) {
        printf(">> can't open directory");
        sleep(1);
        exit(0);
    }

    printf("select save : (q -> exit)\n\n");
    for (int i = 1; (dir_content = readdir(dir)) != NULL; ++i) {
        if (dir_content->d_name[0] != '.') {
            printf("%d) %s\n", i, dir_content->d_name);
            strcpy(filename[i - 1], dir_content->d_name);
        }
        else {
            --i;
        }
    }

    scanf("%s", path);

    if (path[0] == EXIT) {
        exit(0);
    }

    call_Rfile(filename[strtol(path, (char **)NULL, 10) - 1]);
}

void call_menu() {
    int mode;

    printf("select option : \n\n");
    printf("1) new game\n");
    printf("2) load from save\n");
    printf("3) online\n\n");

    scanf("%d", &mode);

    switch (mode) {
        case 1:
            system(cls);

            printf("select option : \n\n");
            printf("1) with humman\n");
            printf("2) with bot\n\n");

            scanf("%d", &mode);

            switch (mode) {
                case 1:
                    system(cls);

                    is_bot_on = 0;
                    is_online = 0;

                    call_Rcli_gi();
                    call_Rcli();
                    ++player;
                    change_player();
                    call_Rcli();

                    break;

                case 2:
                    system(cls);

                    is_bot_on = 1;
                    is_online = 0;

                    call_Rcli_gi();
                    call_Rcli();
                    ++player;
                    change_player();
                    call_Rcli();

                    break;
            }

            break;

        case 2:
            system(cls);

            printf("select option : \n\n");
            printf("1) with humman\n");
            printf("2) with bot\n\n");

            scanf("%d", &mode);

            switch (mode) {
                case 1:
                    system(cls);

                    is_bot_on = 0;
                    is_online = 0;

                    break;

                case 2:
                    system(cls);

                    is_bot_on = 1;
                    is_online = 0;

                    break;
            }

            show_save();
            break;

        case 3:
            system(cls);

            is_bot_on = 0;
            is_online = 1;

            system(cls);

            printf("select option : \n\n");
            printf("1) create\n");
            printf("2) join\n\n");

            scanf("%d", &mode);

            switch (mode) {
                case 1:
                    player_number = 0;

                    call_Rcli_gi();
                    call_Rcli();
                    ++player;
                    change_player();
                    call_sendServer();
                    call_getServer();

                    break;
                case 2:
                    player_number =1;

                    call_getServer();
                    call_Rcli();
                    call_sendServer();

                    break;
            }

            break;
    }
}