// it is faze 1
// this game is optimized up to 26*26 map

/*
    in faze 1 we only get 3 point of map and highlight them
    then we print the boarder
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define VER_BORDER '|'
#define HOR_BORDER '-'
#define SPACE 10

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(map, row, col, size) *(map + ((row * size) + col))

#define true_i(i) i + 1
#define true_j(j) j + 1

// return number by char
#define rnbt(ch) ch - 64

// erase to end of line
#define erase_line "\33[K"

// move cursor one line up
#define mv_cur_up "\33[A"

#ifdef __linux__
#if __linux__
// f:forground - b:background
#define b_blue "\033[104m"
#define f_darkblue "\033[34m"
#define b_white "\033[107m"
#define f_black "\033[30m"
#define f_darkred "\033[31m"
#define f_darkyellow "\033[33m"
#define color_reset "\033[0m"
#endif
#endif

#ifdef _WIN32
#if _WIN32
// f:forground - b:background
#define b_blue ""
#define f_darkblue ""
#define b_white ""
#define f_black ""
#define f_darkred ""
#define f_darkyellow ""
#define color_reset ""
#endif
#endif

const char *guide = "\033[34m\033[101mSEA\033[31m\033[104mBATTLE\033[0m\n\n"
                    "Hello.please READ it carefully\n"
                    "1st : write demension of board\n"
                    "2nd : for each user write first number of ships\n"
                    "      and then position of explosion place in form of <num> <char>\n"
                    "e.g. : 1 A\n"
                    "some ruls :\n"
                    "1) max of demension is 26 => 1-26 & A-Z\n\n"
                    "press any key to continue...";

/*
    error -> f_darkyellow
    pointers -> b_white , f_black
    water -> b_blue , f_darkblue
    exploied place -> b_blue , f_darkred
*/

void board_creator(char *board, int size)
{
    // water
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            pos(board, i, j, size) = '~';
        }
    }
}

void loop_print_space(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf(" ");
    }
}

void print_border(char *map1, char *map2, int size)
{
    char characters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // contains \0
    int i_temp;

    printf("##FOCP1");
    loop_print_space(SPACE + size + size + 2 - 7); // we have $SPACE space between 2 tables
    printf("##FOCP2\n\n");

    // j index pointer < start

    printf("   ");

    for (int i = 0; i < size; i++)
    {
        printf("%s%s%c %s", b_white, f_black, characters[i], color_reset);
    }

    loop_print_space(SPACE + 1);

    printf(" ");

    for (int i = 0; i < size; i++)
    {
        printf("%s%s%c %s", b_white, f_black, characters[i], color_reset);
    }

    printf("\n");

    // j index pointer end >

    for (int i = 0; i < size; i++)
    {
        i_temp = i + 1;

        for (int j = -1; j < (2 * size) + SPACE; j++)
        {
            if (j == -1)
            {
                printf("%s%s%2d %s", b_white, f_black, i_temp, color_reset);
            }
            else if (j == size + SPACE - 1)
            {
                printf("%s%s%2d %s", b_white, f_black, i_temp, color_reset);
            }
            else if (j < size)
            {
                if (pos(map1, i, j, size) == '~')
                {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else
                {
                    printf("%s%sX %s", b_blue, f_darkred, color_reset);
                }
            }
            else if (j >= size + SPACE)
            {
                if (pos(map2, i, j - (size + SPACE), size) == '~')
                {
                    printf("%s%s~ %s", b_blue, f_darkblue, color_reset);
                }
                else
                {
                    printf("%s%sX %s", b_blue, f_darkred, color_reset);
                }
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }
}

int main()
{
    system("clear");

    int n;
    int ship_num; // hasn't usage now
    int i_index;
    char j_index;
    int check = 0;
    int turn = 0;

    printf("%s", guide);

    while (!getchar())
    {
    };

    system("clear");

    printf("please write size of map\n");

    scanf("%d", &n);

    while (n < 1 || 26 < n)
    {
        printf("%s!!!your number either lower than 0 or grather than 26 --- please write it again%s\n", f_darkyellow, color_reset);
        scanf("%d", &n);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }

    system("clear");

    char focp1_board[n][n];
    char focp2_board[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            focp1_board[i][j] = ' ';
            focp2_board[i][j] = ' ';
        }
    }

    board_creator(&focp1_board[0][0], n);
    board_creator(&focp2_board[0][0], n);

    print_border(&focp1_board[0][0], &focp2_board[0][0], n);

    printf("\n");

    // focp1
    printf("FOCP1 :\n\n");

    printf("please write number of ships\n");

    scanf("%d", &ship_num);

    printf("%s%s", mv_cur_up, erase_line);
    printf("%s%s", mv_cur_up, erase_line);

    printf("please write positions in this template <number> <character>\n");

    for (int k = 0; k < 3; k++)
    {
        scanf("%d %c", &i_index, &j_index);

        while (i_index < 1 || i_index > n)
        {
            check = 1;
            ++turn;

            printf("%s!!!error : input is wrong --- please write it again%s\n", f_darkyellow, color_reset);
            scanf("%d %c", &i_index, &j_index);

            printf("%s%s", mv_cur_up, erase_line);
            printf("%s%s", mv_cur_up, erase_line);

            if (turn == 1)
            {
                printf("%s%s", mv_cur_up, erase_line);
            }
        }

        while (j_index < 65 || j_index >= 65 + n)
        {
            check = 1;
            ++turn;

            printf("%s!!!error : input is wrong --- please write it again\n%s", f_darkyellow, color_reset);
            scanf("%d %c", &i_index, &j_index);

            printf("%s%s", mv_cur_up, erase_line);
            printf("%s%s", mv_cur_up, erase_line);

            if (turn == 1)
            {
                printf("%s%s", mv_cur_up, erase_line);
            }
        }

        if (!check)
        {
            printf("%s%s", mv_cur_up, erase_line);
        }

        focp1_board[true_i(i_index)][true_j(rnbt(j_index))] = 'X';
    }

    // focp2
    printf("%s%s", mv_cur_up, erase_line);
    printf("%s%s", mv_cur_up, erase_line);
    printf("%s%s", mv_cur_up, erase_line);

    check = 0;

    printf("FOCP2 :\n\n");

    printf("please write number of ships\n");

    scanf("%d", &ship_num);

    printf("%s%s", mv_cur_up, erase_line);
    printf("%s%s", mv_cur_up, erase_line);

    printf("please write positions in this template <number> <character>\n");

    for (int k = 0; k < 3; k++)
    {
        scanf("%d %c", &i_index, &j_index);

        while (i_index < 1 || i_index > n)
        {
            check = 1;
            ++turn;

            printf("%s!!!error : input is wrong --- please write it again%s\n", f_darkyellow, color_reset);
            scanf("%d", &i_index);

            printf("%s%s", mv_cur_up, erase_line);
            printf("%s%s", mv_cur_up, erase_line);

            if (turn == 1)
            {
                printf("%s%s", mv_cur_up, erase_line);
            }
        }
        while (j_index < 65 || j_index > 65 + n)
        {
            check = 1;
            ++turn;

            printf("%s!!!error : input is wrong --- please write it again%s\n", f_darkyellow, color_reset);
            scanf("%c", &j_index);

            printf("%s%s", mv_cur_up, erase_line);
            printf("%s%s", mv_cur_up, erase_line);

            if (turn == 1)
            {
                printf("%s%s", mv_cur_up, erase_line);
            }
        }

        if (!check)
        {
            printf("%s%s", mv_cur_up, erase_line);
        }

        focp2_board[true_i(i_index)][true_j(rnbt(j_index))] = 'X';
    }

    system("clear");

    print_border(&focp1_board[0][0], &focp2_board[0][0], n);

    return 0;
}
