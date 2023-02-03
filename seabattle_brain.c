#include"sb_globdef.h"
#include<math.h>

#define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))

int tasadofi(int n) {
    int tmprand = randnum(0,n-1);
    printf("----%d--a-\n\n\n",tmprand);
    return tmprand;
}


int brain() {
    int n = board_size;
    char local_save_board [board_size][board_size];
    char *local_save_board_pointer = &local_save_board[0][0];


    int hill = repair_num - p2.repair_used;
    char p1boardadamizadi[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //if(p1boardadamizadi[i][j]=='%'){continue;}
            p1boardadamizadi[i][j] = p1.board[i][j];
        }
    }
    char *enemy_board = &(p1boardadamizadi[0][0]); // I change p to enemy_board because we have p in global

    for(int i=0;i<n*n;i++){
        if(*(local_save_board_pointer+i) != '%' ){
            *(local_save_board_pointer + i) = *(enemy_board+i);
        }
    }



    int tmp;
    int x;
    int y;
//    for (int i = 0; i <n*n; i++) {
//        printf("%d->%c\n",i,*(enemy_board+i));
//    }
    for (int i = 0; i <n*n; i++) {
//        printf("%c",*(enemy_board+i));
        if (*(enemy_board + i) == 'x') {
//            printf("x found");sleep(3);
            enemy_board = (enemy_board + i);
            local_save_board_pointer = (local_save_board_pointer +i);
            x = i / n;
            y = (i % n);

            //if(x-1 >=0 && y-1 >=0 && *(enemy_board-n-1) =='~'){return i-n-1;}
            if (x - 1 >= 0 && *(enemy_board - n) != 'x' && *(enemy_board-n)!='&') {printf("(  if1%d  )",i-n);return i - n; }
            //if(x-1 >=0 && y+1 <=n && *(enemy_board-n+1) =='~'){return i-n+1;}
            if (y - 1 >= 0 && *(enemy_board - 1) != 'x'&& *(enemy_board-1)!='&') {printf("(if1)"); return i - 1; }
            if (y + 1 <= n && *(enemy_board + 1) != 'x'&& *(enemy_board+1)!='&') {printf("(if1)"); return i + 1; }
            //if(x+1 <=n && y-1 >=0 && *(enemy_board+n-1) =='~'){return i+n-1;}
            if (x + 1 <= n && *(enemy_board + n) != 'x'&& *(enemy_board+n)!='&') {printf("(if1)"); return i + n; }
            //if(x+1 <=n && y+1 <=n && *(enemy_board+n+1) =='~'){return i+n+1;}
            enemy_board = enemy_board - i;
        }

    }

    while (true) {
        printf("in in randomm\n");
        tmp = tasadofi(n * n);
        if (*(enemy_board + tmp) != 'X' && *(enemy_board+tmp) != 'x') {
            return tmp;
        }
    }
}


void call_brain(int arr[]) {
    int tmp = brain();
    int n = board_size;
    int x = tmp / n;
    int y = (tmp % n);
    arr[0] = 1;
    arr[1] = x;
    arr[2] = y;
    printf("%d %d \n",x+1,y+1);
//    sleep(5);
    arr[3] = 0;
}

//int main(){
//char chararr[]={'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~',};
//printf("%d",brain(&chararr[0],5));
//return 0;}
