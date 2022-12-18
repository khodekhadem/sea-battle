#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
#if __linux__
#define cls "clear"
#include <ncurses.h>
#endif
#endif

#ifdef _WIN32
#if _WIN32
#define cls "cls"
#include <conio.h>
#endif
#endif

#define SPACE 10

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(arr, row, col, colN) *(arr + ((row * colN) + col))

// erase to end of line
#define erase_line "\33[K"

// move cursor one line up
#define mv_cur_up "\33[A"

// f:forground - b:background
#define b_blue "\033[104m"
#define f_darkblue "\033[34m"
#define b_white "\033[107m"
#define f_black "\033[30m"
#define f_darkred "\033[31m"
#define f_darkyellow "\033[33m"
#define b_magenta "\033[37m"
#define f_grey "\033[37m"
#define b_black "\033[40m"
#define b_darkred "\033[41m"
#define color_reset "\033[0m"

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define ENTER 'e'

extern int board_size;
extern char p1_name[20];
extern char p2_name[20];
extern char *board1;
extern char *board2;
extern int p1_ship_num;
extern int p2_ship_num;
extern int *ships_pos_p1;
extern int *ships_pos_p2;

/*
    error -> f_darkyellow
    pointers -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
    ship -> b_magenta , f_grey
    exploied ship -> b_darkred
*/
/*
    water -> ~
    ship -> 1 .. 9
    exploied place -> X
*/

void board_creator(char *board)
{
    // water
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            pos(board, i, j, board_size) = '~';
        }
    }
}

void print_board(char *map, int ship[][2], int player)
{
    char characters[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // contains \0

    switch (player)
    {
    case 1:
        printf("%s", p1_name);
        break;

    case 2:
        printf("%s", p2_name);
        break;
    }

    for (int i = 0; i < board_size; i++)
    {
        printf("%s%s%c %s", b_white, f_black, characters[i], color_reset);
    }

    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; i < board_size; j++)
        {
            if (/* condition */)
            {
                /* code */
            }
            else if (/* condition */)
            {
                /* code */
            }
            else
            {
                /* code */
            }
            
        }
    }
}

void ship_pos_to_global()
{
}

void ship_pos_creator(int ship_pos[][2], int i, int j)
{
    int k = 0;

    for (int i_temp = 0; i_temp < i; i_temp++)
    {
        for (int j_temp = 0; i < j; j_temp++)
        {
            ++k;

            ship_pos[k][0] = i_temp;
            ship_pos[k][1] = j_temp;
        }
    }
}

// 0 -> normal , 1 -> exit
int ship_creator(int player)
{
    //... & ij
    int ship_pos[3][2];
    int _continue = 1;
    int _inner_continue = 1;

    printf("how is your ship ? vertical <v> or horizontal <h> : ");

    switch (getchar())
    {
    case 'v':
        ship_pos_creator(ship_pos, 3, 1);

        break;

    case 'h':
        // i & j
        ship_pos_creator(ship_pos, 1, 3);

        break;
    }

    while (_continue)
    {
        if (player == 1)
        {
            print_board(board1, ship_pos, player);
        }
        else
        {
            print_board(board2, ship_pos, player);
        }

        while (_inner_continue)
        {
            switch (getch())
            {
            case UP:

                break;

            case DOWN:

                break;

            case RIGHT:

                break;

            case LEFT:

                break;

            case ENTER:

                break;
            }
        }

        system(cls);
    }
}

void call_Rcli()
{
#ifdef __linux__
#if __linux__
    initscr();
    noecho();
    cbreak();
#endif
#endif

    printf("please write size of map (1 .. 52)\n");

    scanf("%d", &board_size);

    while (board_size < 1 || 52 < board_size)
    {
        printf("%s!!!your number either lower than 1 or grather than 52 --- please write it again%s\n", f_darkyellow, color_reset);
        scanf("%d", &board_size);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }

    system(cls);

    printf("write player1 name (max = 19 character) : ");
    scanf("%s\n", p1_name);
    printf("write player2 name (max = 19 character) : ");
    scanf("%s", p1_name);

    system(cls);

    printf("write number of ships (max = 9) : ");
    scanf("%d",&p1_ship_num);
    p1_ship_num %= 9;
    ++p1_ship_num;
    p2_ship_num = p1_ship_num;

    board_creator(board1);
    board_creator(board2);

    for (int i = 0; i < p1_ship_num; i++)
    {
        ship_creator(1);
    }

    for (int i = 0; i < p2_ship_num; i++)
    {
        ship_creator(2);
    }

#ifdef __linux__
#if __linux__
    endwin();
#endif
#endif
}