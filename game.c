#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <ctype.h>

//printing two 2d arr beside each other by pointers
/*
like this

@0123456789         @0123456789
0~~~~~~~~~~         0~~~~~~~~~~
1~~~~~~~~~~         1~~~~~~~~~~
2~~*~~~~~~~         2~~~~~~~~~~
3~~~*~*~~~~         3~~~~~~~~~~
4~~~~~~~~~~         4~~~~~~~~~~
5~~~~~~~~~~         5~~~~~~~~~~
6~~~~~~~~~~         6~~~~~~~~~~
7~~~~~~~~~~         7~~~~~~~~~~
8~~~~~~~~~~         8~~~~~~~~~~
9~~~~~~~~~~         9~~~~~~~~~~

*/
void printer(char *p1,char *p2,int n){
    system("clear");
    system("figlet sea-battle");
    printf("@");
    for(int i=0;i<n;i++){printf("%d",i);}
    printf("         @");
    for(int i=0;i<n;i++){printf("%d",i);}
    printf("\n"); 
    for(int i=0;i<n;i++){
        printf("%d",i);
        for (int j = 0; j < n; j++)
        {
            printf("%c",*p1++);
        }
        printf("         ");
        printf("%d",i);
        
        for (int j = 0; j < n; j++)
        {
            printf("%c",*p2++);
        }
        printf("\n");
    }
}
//filling two 2d array with filler variable
void fill_board(char *p,int n,char filler){
    for(int i=0;i<n;i++){
        for (int j = 0; j < n; j++)
        {
            //boardp1[i][j]='~';
            //boardp2[i][j]='~';
            *p = filler;
            *p++;
            
        }
    }
}
// getting boat locations
void get_boats(char *p,int n,int boatsNumber,char *empt,int player){
    int tmpx,tmpy;
    char tmpc;
    
    if(player==1){printer(p,empt,n);}else{printer(empt,p,n);} //printer //left side board (1) or right side (2)
    
    printf("player%d !! enter %d boat location\nex: 3 4 v or 4 2 h\n",player,boatsNumber);
    
    for(int i=0;i<boatsNumber;i++){

        scanf("%d %d %c",&tmpx,&tmpy,&tmpc);

        //chek if the x and y are proper in the board
        if(tmpx<n && 0<=tmpx  && tmpy<n && 0<=tmpy && (tmpc=='v' || tmpc=='h') && ((tmpc=='h' && tmpy<n-1 && 0<tmpy && *(p+((tmpx)*n)+tmpy+1)!='@' && *(p+((tmpx)*n)+tmpy-1)!='@')||(tmpc=='v' && tmpx<n-1 && 0<tmpx && *(p+((tmpx+1)*n)+tmpy)!='@' && *(p+((tmpx-1)*n)+tmpy)!='@'))){
            
            *(p+(tmpx*n)+tmpy)= '@'; // putting body of the boat
            
            if(tmpc=='v'){ *(p+((tmpx+1)*n)+tmpy)= '@'; *(p+((tmpx-1)*n)+tmpy)= '@'; } //putting the head and tail of the boat vertically
            if(tmpc=='h'){ *(p+((tmpx)*n)+tmpy+1)= '@'; *(p+((tmpx)*n)+tmpy-1)= '@'; } //putting the head and tail of the boat horizentally

            if(player==1){printer(p,empt,n);}else{printer(empt,p,n);} //printer

        }
        //if x and y are not proper ask for them again
        else{
            i--;
            if(player==1){printer(p,empt,n);}else{printer(empt,p,n);}//printer
            printf("wrong input!! try this one agane\n");
            }


    }
    

}




int main(){
    int n,tmpx,tmpy,boatsNumber;
    printf("enter board size:");scanf("%d",&n);
    printf("how many boats do we have? ");scanf("%d",&boatsNumber);
    char boardp1[n][n];
    char boardp2[n][n];
    char boatp1[n][n];
    char boatp2[n][n];
    char emptboard[n][n];
    char tmpc;

    fill_board(&emptboard[0][0],n,'?');
    
    fill_board(&boardp1[0][0],n,'~');
    fill_board(&boatp1[0][0],n,'~');
    
    fill_board(&boardp2[0][0],n,'~');
    fill_board(&boatp2[0][0],n,'~');

    get_boats(&boatp1[0][0],n,boatsNumber,&emptboard[0][0],1);
    

    printf("enter any thing to claer\n");scanf(" %c",&tmpc);system("clear");//pres a key to clear
    get_boats(&boatp2[0][0],n,boatsNumber,&emptboard[0][0],2);

    printer(&boatp1[0][0],&boatp2[0][0],n);














return 0;}
