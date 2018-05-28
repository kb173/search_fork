#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Include Datei für getopt(); getopt.h geht auch, ist aber älter. */
#include <unistd.h>

int main (int argc, char* argv[])
{
    int c;
    char* programm_name = argv[0];

    char* searchpath;
    int rec = 0, casein = 0;

    printf("\nEntered options:\n");


    while ((c = getopt( argc, argv, "Ri" )) != EOF ) {
        switch (c) {
            case 'R':
                rec = 1;
                printf("Recursive\n");
                break;
            case 'i':
                casein = 1;
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

    printf("\nEntered searchpath:\n");

    searchpath = argv[optind];
    printf("%s\n", searchpath);

    printf("\nEntered files:\n");

    char* files[argc - optind];

    for (int i = optind + 1; i < argc; i++)
    {
        files[i - optind - 1] = argv[i];
        printf("%s\n", files[i - optind - 1]);
    }

    printf("\n------------------\n\n");
}