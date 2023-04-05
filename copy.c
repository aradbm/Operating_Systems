#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
int main(int argc, char **argv)
{
    bool v_flag = false, f_flag = false, same = true; // check if -v for output
                                                      //       or -f allows to overwrite
    if (argc != 4)
    {
        printf("Arguments missing! to use, enter after './copy':\n");
        printf("1. File to copy FROM\n \
                2. File to copy TO\n \
                3. Flags: -v for output -f to allow overwrite\n");
        return 1;
    }
    if (strcmp(argv[3], "-v") == 0)
        v_flag = true;
    else
        f_flag = true;
    FILE *ptr1;
    FILE *ptr2;
    char char_f1;
    char char_f2;
    ptr1 = fopen(argv[1], "r");
    if (access(argv[2], F_OK) == 0) // file exist
    {
        if (f_flag != true)
        {
            printf("target file exist\n");
        }
    }
    ptr2 = fopen(argv[2], "w+");

    while (feof(ptr1) == 0)
    {
        char_f1 = fgetc(ptr1);
        fputc(char_f1, ptr2);
    }
    fclose(ptr1);
    fclose(ptr2);
    if (v_flag == true)
        printf("aaa\n");
    else
        printf("bbb\n");

    if (same)
    {
        return 0;
    }
    return 1;
}