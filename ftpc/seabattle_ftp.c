#include<stdio.h>
void upload(){
    sytem("ftp -n < ~/sea-battle/ftpc/upload"); 


}
void download(){
    sytem("ftp -n < ~/sea-battle/ftpc/download"); 

}

void cal_upload(){
    upload();
}
void cal_download(){
    download();
}




