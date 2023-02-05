#include "sb_globdef.h"

typedef char Byte;

extern void call_download(void);

int call_dataAvailable(){
    static int turn = 0;
    Byte f_data;
    Byte fold_data;

#if WIN32
    char *cmd = "mv onlineconfig\\online_data.bin onlineconfig\\old_online_data.bin";
    char *path = "onlineconfig\\online_data.bin";
    char *old_path = "onlineconfig\\old_online_data.bin";
#elif __linux__
    char *cmd = "mv onlineconfig/online_data.bin onlineconfig/old_online_data.bin";
    char *path = "onlineconfig/online_data.bin";
    char *old_path = "onlineconfig/old_online_data.bin";
#endif

    do {
        sleep(1);

        call_download();
    } while (!fopen(path,"rb"));

    if (turn == 0) {
        system(cmd);

        call_download();
    }

    FILE *f = fopen(path,"rb");
    FILE *f_old = fopen(old_path,"rb");

    fread(&f_data, sizeof(Byte), 1, f);
    fread(&fold_data, sizeof(Byte), 1, f_old);
    while (!feof(f) && !feof(f_old)){
        if (f_data != fold_data) {
            system(cmd);
            turn = 1;

            system(cls);

            return 0;
        }

        fread(&f_data, sizeof(Byte), 1, f);
        fread(&fold_data, sizeof(Byte), 1, f_old);
    }

    system(cmd);
    turn = 1;

    system(cls);

    return 1;
}