#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* Include Datei für getopt(); getopt.h geht auch, ist aber älter. */
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void print_usage(char *programm_name)
{
    printf("Usage: %s [-R] [-i] searchpath filename1 [filename2]...[filenameN]\n\n", programm_name);
    return;
}

char* get_full_path(char *path)

{
    char *full_path;
    long maxpath;

    if ((maxpath = pathconf(".", _PC_PATH_MAX)) == -1)
    {
        perror("Failed to determine pathname length\n");
        return 0;
    }

    if ((full_path = (char *)malloc(maxpath)) == NULL)
    {
        perror("Failed to allocate space for pathname\n");
        return 0;
    }

    if (realpath(path, full_path) == NULL)
    {
        perror("Failed to get current working directory\n");
        return 0;
    }

    return full_path;
}

int search_dir(char *path, char *file)
{
    struct dirent *direntp;
    DIR *dirp;
    int found = 0;

    if ((dirp = opendir(path)) == NULL)
    {
        perror("Failed to open directory");
        return 0;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, file) == 0)
        {
            found = 1;
        }
    }

    while ((closedir(dirp) == -1) && (errno == EINTR));

    return found;
}

int main (int argc, char* argv[])
{
    int c;
    char* programm_name = argv[0];

    char* searchpath;
    int rec = 0, casein = 0;

    if (argc < 3)
    {
        print_usage(programm_name);
        exit(1);
    }

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
                print_usage(programm_name);
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

    // Get remaining files
    char* files[argc - optind];

    for (int i = optind + 1; i < argc; i++)
    {
        files[i - optind - 1] = argv[i];
        printf("%s\n", files[i - optind - 1]);
    }

    printf("\n------------------\n\n");

    char *full_path;

    if ((full_path = get_full_path(searchpath)) == 0)
    {
        exit(1);
    }

    printf("Full searchpath: %s\n", full_path);

    if (search_dir(full_path, files[0]))
    {
        printf("Found!\n");
    }
}