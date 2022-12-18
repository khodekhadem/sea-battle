// optimize up to 52*52 board
// optimize for windows and linux

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sb_globvar.h"

#ifdef __linux__
#if __linux__
#define cls "clear"
#endif
#endif

#ifdef _WIN32
#if _WIN32
#define cls "cls"
#endif
#endif

extern void call_Rcli();
extern int* call_cli();
extern int* call_engine();

int main()
{
    system(cls);

    int *cli_result;
    int *engine_result;

    printf("%s", logo);

    sleep(1);
    system(cls);

    call_Rcli();

    cli_result = call_cli(0, NULL);

    while (!is_ended)
    {
        engine_result = call_engine(cli_result);
        cli_result = call_cli(1, engine_result);
    }

    return 0;
}