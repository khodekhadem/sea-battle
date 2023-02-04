#include <stdlib.h>

void call_upload(){
#if WIN32
    char *cmd = "ftp -n < ftpc\\ftp-upload";
#elif __linux__
    char *cmd = "ftp -n < ftpc/ftp-upload";
#endif

    system(cmd);
}

void call_download(){
#if WIN32
    char *cmd = "ftp -n < ftpc\\ftp-download";
#elif __linux__
    char *cmd = "ftp -n < ftpc/ftp-download";
#endif

    system(cmd);
}




