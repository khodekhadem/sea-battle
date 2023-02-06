#include "sb_globdef.h"

extern void call_download(void);

int call_dataAvailable(){
    FILE *file;
    int tmp;

#if WIN32
    char *path = "onlineconfig\\online_data.bin";
#elif __linux__
    char *path = "onlineconfig/online_data.bin";
#endif

    sleep(1);

    call_download();

    system(cls);
    printf("please wait ...\n");

    file = fopen(path, "rb");
    if (!file)
    {
        printf(">> file can't be opened");
        sleep(1);
        exit(0);
    }

    fread(&tmp, sizeof(int), 1, file);
    fclose(file);

    if (tmp > file_version)
    {
        return 1;
    }
    else {
        return 0;
    }
}