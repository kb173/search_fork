#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Include Datei für getopt(); getopt.h geht auch, ist aber älter. */
#include <unistd.h>

int main (int argc, char* argv[])
{
    int c;
    char * programm_name = argv[0];


    while ((c = getopt( argc, argv, "Ri" )) != EOF ) {
        switch (c) {
            case 'R':
                printf("Recursive\n");
                break;
            case 'i':
                printf("Case insensitive\n");
                break;
            case '?':
                fprintf( stderr, "%s error: Unknown option.\n", programm_name );
                exit(1);
                break;
            default:
                /* assert() dient nur zu Debugzwecken und sollte nur dort eingesetzt sein,
                wo etwas sicher niemals passieren darf. 0 ist in C immer gleich "logisch falsch". */
                assert(0);
        }
    }

    for (int i = optind; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}