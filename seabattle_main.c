// optimize up to 52*52 board
// optimize for windows and linux

#include <stdio.h>
#include <unistd.h>

extern int* call_cli(int,int*);
extern int* call_engine(int*);
extern void call_Rfile();
extern void call_Rcli();
extern void call_save();

extern int is_ended;
extern char *logo;

int main()
{
    char mode;
    int *cli_result;
    int *engine_result;

    printf("%s",logo);

    sleep(1);
    system("clear");

    printf("'n' for new game and 's' for saved game and any other key for exit\n");
    scanf("%c", &mode);
    system("clear");

    switch (mode)
    {
    case 'n':
        call_Rcli();

        break;

    case 's':
        call_Rfile();

        break;

    default:
        return 0;
    }

    cli_result = call_cli(0, NULL);

    while (!is_ended)
    {
        engine_result = call_engine(cli_result);
        cli_result = call_cli(1, engine_result);
    }

    return 0;
}