#include <dirent.h>
#include "sb_globvar.h"

extern void call_Rcli(void);

extern void call_Rfile(const char *);

void show_save() {
    DIR *dir;
    struct dirent *dir_content;
    char path[10];

    dir = opendir("savefiles");

    if (!dir) {
        printf(">> can't open directory");
    }

    printf("select save : \n\n");
    for (int i = -1; (dir_content = readdir(dir)) != NULL; ++i) {
        if (dir_content->d_name[0] != '.') {
            printf("%d) %s\n", i, dir_content->d_name);
        }
    }

    scanf("%s", path);
    call_Rfile(path);
}

void call_menu() {
    printf("select option : \n\n");
    printf("1) new game\n");
    printf("2) load from save\n\n");

    switch (getchar()) {
        case '1':
            system(cls);

            call_Rcli();
            break;

        case '2':
            system(cls);

            show_save();
            break;
    }
}