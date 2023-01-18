#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sb_globdef.h"

int tasadofi(int n){
    #define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))
    srand(time(NULL));
    return randnum(0,n-1);
}













int brain(){
    int hill = repair_num - p2.repair_used;
    char *p = &(p1.board[0][0]) ;
    int n = board_size;

    int tmp;
    int x ;int y;
        for(int i=0;i<n*n;i++){
            printf("%d %c \n",i,*(p+i));
            if(*(p+i) == 'x'){
                    p = (p+i);
                    x=i/n;
                    y=(i%n);
                    printf("%d  %d  %c \n",x,y,*(p-n));
                    //if(x-1 >=0 && y-1 >=0 && *(p-n-1) =='~'){return i-n-1;}
                    if(x-1 >=0 &&            *(p-n)   =='~'){return i-n  ;}
                    //if(x-1 >=0 && y+1 <=n && *(p-n+1) =='~'){return i-n+1;}
                    if(           y-1 >=0 && *(p-1)   =='~'){return i-1  ;}
                    if(           y+1 <=n && *(p+1)   =='~'){return i+1  ;}
                    //if(x+1 <=n && y-1 >=0 && *(p+n-1) =='~'){return i+n-1;}
                    if(x+1 <=n            && *(p+n)   =='~'){return i+n  ;}
                    //if(x+1 <=n && y+1 <=n && *(p+n+1) =='~'){return i+n+1;}

            }

        }
        while(true){
            tmp = tasadofi(n*n);
            if(*(p+tmp) == '~'){return tmp;}

        }


}


void call_brain(int arr[]){
    int tmp = brain();
    int n board_size;
    x=tmp/n;
    y=(tmp%n);
    arr[0] = 1;
    arr[1] = x;
    arr[2] = y;
    arr[3] = 0;

}

//int main(){
//char chararr[]={'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~',};
//printf("%d",brain(&chararr[0],5));
//return 0;}
