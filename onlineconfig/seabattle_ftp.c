#include<stdio.h>
void upload(){
    system("ftp -n < ~/sea-battle/ftpc/ftp-upload"); 


}
void download(){
    system("ftp -n < ~/sea-battle/ftpc/ftp-download"); 

}

void cal_upload(){
    upload();
}
void cal_download(){
    download();
}

int main(){
cal_download();

}



