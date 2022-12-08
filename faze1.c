// it is faze 1
//this game is optimized for under 10*10 maps

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VER_BORDER '|'
#define HOR_BORDER '-'
#define SPACE 10

// no. of columns = colN => arr[row][col] = *(arr + ((row * colN) + col))
#define pos(map, row, col, size) *(map + ((row * size) + col))

#define true_i(i) i + 1
#define true_j(j) j + 1

// return_number_by_char
#define rnbt(ch) ch - 64

void board_creator(char *board, int size)
{
    char characters[27] = "ABCDEFGHI";
    int numbers = 1;

    // water
    for (int i = 2; i < size - 1; i++)
    {
        for (int j = 2; j < size - 1; j++)
        {
            pos(board, i, j, size) = '~';
        }
    }

    // chars
    for (int j = 2; j < size - 1; j++)
    {
        pos(board, 0, j, size) = characters[j - 2];
    }

    // nums
    for (int i = 2; i < size - 1; i++)
    {
        pos(board, i, 0, size) = numbers + 48;

        ++numbers;
    }

    // border
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < size; j++)
        {
            if ((i == 1 || i == size - 1) && (1 < j) && (j < size - 1))
            {
                pos(board, i, j, size) = HOR_BORDER;
            }
            else if ((j == 1 || j == size - 1) && (1 < i) && (i < size - 1))
            {
                pos(board, i, j, size) = VER_BORDER;
            }
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
    printf("##FOCP1");
    loop_print_space(SPACE + size + size - 1 - 5); // we have $SPACE space between 2 tables
    printf("##FOCP2\n\n");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (2 * size) + SPACE; j++)
        {
            if (j < size)
            {
                printf("%c", pos(map1, i, j, size));

                if (j != size - 1)
                {
                    printf(" ");
                }
            }
            else if (j >= size + SPACE)
            {
                printf("%c", pos(map2, i, j - (size + SPACE), size));

                printf(" ");
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
    int n;
    int ship_num; // hasn't usage now
    int focp1_i_indexes[3];
    char focp1_j_indexes[3];
    int focp2_i_indexes[3];
    char focp2_j_indexes[3];
    int i_temp;
    int j_temp;

    printf("please write size of map\n");

    scanf("%d", &n);

    printf("\n");

    printf("please insert focp1 and then focp2\n");
    printf("please first write number of ships and then position of them seperatly\n");
    printf("for position do this template <num> <capital char>\n\n");

    // focp1
    scanf("%d", &ship_num);

    for (int k = 0; k < 3; k++)
    {
        scanf("%d %c", &focp1_i_indexes[k], &focp1_j_indexes[k]);

        while (focp1_i_indexes[k] < 1 || focp1_i_indexes[k] > n)
        {
            printf("error : i is wrong --- please write it again(only i)\n");
            scanf("%d", &focp1_i_indexes[k]);
        }
        while (focp1_j_indexes[k] < 65 || focp1_j_indexes[k] > 65 + n)
        {
            printf("error : j is wrong --- please write it again(only j)\n");
            scanf("%c", &focp1_j_indexes[k]);
        }
    }

    printf("\n\n------\n\n");

    // focp2
    scanf("%d", &ship_num);

    for (int k = 0; k < 3; k++)
    {
        scanf("%d %c", &focp2_i_indexes[k], &focp2_j_indexes[k]);

        while (focp1_i_indexes[k] < 1 || focp1_i_indexes[k] > n)
        {
            printf("error : i is wrong --- please write it again(only i)\n");
            scanf("%d", &focp1_i_indexes[k]);
        }
        while (focp1_j_indexes[k] < 65 || focp1_j_indexes[k] > 65 + n)
        {
            printf("error : j is wrong --- please write it again(only j)\n");
            scanf("%c", &focp1_j_indexes[k]);
        }
    }

    system("clear");
    sleep(1);

    char focp1_board[n + 3][n + 3]; // has border + index pointer
    char focp2_board[n + 3][n + 3]; // has border + index pointer

    for (int i = 0; i < n + 3; i++)
    {
        for (int j = 0; j < n + 3; j++)
        {
            focp1_board[i][j] = ' ';
            focp2_board[i][j] = ' ';
        }
    }

    board_creator(&focp1_board[0][0], n + 3);
    board_creator(&focp2_board[0][0], n + 3);

    for (int k = 0; k < 3; k++)
    {
        i_temp = true_i(focp1_i_indexes[k]);
        j_temp = true_j(rnbt(focp1_j_indexes[k]));

        focp1_board[i_temp][j_temp] = 'x';
    }

    for (int k = 0; k < 3; k++)
    {
        i_temp = true_i(focp2_i_indexes[k]);
        j_temp = true_j(rnbt(focp2_j_indexes[k]));

        focp2_board[i_temp][j_temp] = 'x';
    }

    print_border(&focp1_board[0][0], &focp2_board[0][0], n + 3);

    return 0;
}
