#include"sb_globdef.h"

#define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))

int tasadofi(int n) {
    return randnum(0,n-1);
}

int brain() {
    int hill = repair_num - p2.repair_used;
    char *enemy_board = &(p1.board[0][0]); // I change p to enemy_board because we have p in global
    int n = board_size;

    int tmp;
    int x;
    int y;

    for (int i = 0; i < n * n; i++) {
        if (*(enemy_board + i) == 'x') {
            enemy_board = (enemy_board + i);
            x = i / n;
            y = (i % n);

            //if(x-1 >=0 && y-1 >=0 && *(enemy_board-n-1) =='~'){return i-n-1;}
            if (x - 1 >= 0 && *(enemy_board - n) == '~') { return i - n; }
            //if(x-1 >=0 && y+1 <=n && *(enemy_board-n+1) =='~'){return i-n+1;}
            if (y - 1 >= 0 && *(enemy_board - 1) == '~') { return i - 1; }
            if (y + 1 <= n && *(enemy_board + 1) == '~') { return i + 1; }
            //if(x+1 <=n && y-1 >=0 && *(enemy_board+n-1) =='~'){return i+n-1;}
            if (x + 1 <= n && *(enemy_board + n) == '~') { return i + n; }
            //if(x+1 <=n && y+1 <=n && *(enemy_board+n+1) =='~'){return i+n+1;}

        }

    }

    while (true) {
        tmp = tasadofi(n * n);
        if (*(enemy_board + tmp) == '~') {
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
    printf("%d %d \n",x,y);
    sleep(1);
    arr[3] = 0;
}

//int main(){
//char chararr[]={'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~',};
//printf("%d",brain(&chararr[0],5));
//return 0;}
