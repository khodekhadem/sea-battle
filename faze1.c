#include<stdio.h>
int faz1(int *p,int n){
    printf("@");
    for(int i=0;i<n;i++){printf("%d",i);}
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d",i);
        for (int j = 0; j < n; j++)
        {
            printf("%d",*p);
            *p = *(p+1);
        }
        printf("\n");
    }


}
void printer(char *p,int n){
    printf("@");
    for(int i=0;i<n;i++){printf("%d",i);}
    printf("\n"); 
    for(int i=0;i<n;i++){
        printf("%d",i);
        for (int j = 0; j < n; j++)
        {
            printf("%c",*p++);
        }
        printf("\n");
    }




}

//0 water
//1 boat
//2 damaged boat
//3 singed dot 
int main(){
    int n,tmpx,tmpy;
    scanf("%d",&n);
    char board[n][n];
    
    for(int i=0;i<n;i++){
        for (int j = 0; j < n; j++)
        {
            board[i][j]='~';
        }
    }





    for(int i=0;i<3;i++){
        scanf("%d%d",&tmpx,&tmpy);
        board[tmpx][tmpy]='*';
    }
    printer(&board[0][0],n);
    //faz1(&board[0][0],n);
    














return 0;}
