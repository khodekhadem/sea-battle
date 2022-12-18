#include "sb_globdef.h"

void call_Rcli_gi () {
    printf("please write size of map (1 .. 52)\n");
    scanf("%d", &board_size);

    while (board_size < 1 || 52 < board_size) {
        printf("%s!!!your number either lower than 1 or grather than 52 --- please write it again%s\n", f_orange,
               color_reset);
        scanf("%d", &board_size);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }

    system(cls);

    printf("please write repair number : \n");
    scanf("%d", &repair_num);

    system(cls);

    printf("write player1 name (max = 19 character) : ");
    scanf("%s", p1.name);
    printf("\nwrite player2 name (max = 19 character) : ");
    scanf("%s", p2.name);

    system(cls);

    printf("write max part of ships (max = 108 part) (your limit = must be less than %d) : ",
           (board_size * board_size) / 4);
    scanf("%d", &ship_part_number);
    while (ship_part_number < 1 || ship_part_number > ((board_size * board_size) / 4)) {
        printf("%s!!!your number is either less than 1 or more than limit%s\n", f_orange, color_reset);
        scanf("%d", &ship_part_number);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }
    if (ship_part_number > 108) {
        p1.ship_number %= 108;
    }
}