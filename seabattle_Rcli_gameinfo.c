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

    printf("write max part of ships (max = 108 part) (your limit = must be less than %d) : ",
           (board_size * board_size) / 4);
    scanf("%d", &max_part);
    while ((max_part < 1) || (max_part > ((board_size * board_size) / 4)) || (max_part > 108)) {
        printf("%s!!!your number is either less than 1 or more than limit%s\n", f_orange, color_reset);
        scanf("%d", &max_part);

        printf("%s%s", mv_cur_up, erase_line);
        printf("%s%s", mv_cur_up, erase_line);
    }
    if (max_part > 108) {
        p1.ship_number %= 108;
    }
}