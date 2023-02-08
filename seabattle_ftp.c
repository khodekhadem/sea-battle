#include <stdlib.h>

void call_upload(){
#if WIN32
    char *cmd = "ftp -s:.\\ftpc\\WINftp-upload.txt";
#elif __linux__
    char *cmd = "pftp -n < ftpc/ftp-upload"; //comment if you dont have pftp
    //char *cmd = "ftp -p -n < ftpc/ftp-upload"; // uncomment if you dont have pftp
#endif

    system(cmd);
}

void call_download(){
#if WIN32
    char *cmd = "ftp -s:.\\ftpc\\WINftp-download.txt";
#elif __linux__
    char *cmd = "pftp -n < ftpc/ftp-download";// uncomment if you dont have pftp

    //char *cmd = "ftp -p -n < ftpc/ftp-download";// uncomment if you dont have pftp

#endif

    system(cmd);
}




