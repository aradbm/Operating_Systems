#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
int main(int argc, char **argv)
{
    bool v_flag = false, f_flag = false; // check if -v for output
                                         //       or -f allows to overwrite
    if (argc < 3)
    {
        printf("Arguments missing! to use, enter after './copy':\n");
        printf("1. File to copy FROM\n \
                2. File to copy TO\n \
                3. Optional Flags: -v for output -f to allow overwrite\n");
        return 1;
    }
    for (size_t j = 0; j < argc; j++)
    {
        if (strcmp(argv[j], "-v") == 0)
            v_flag = true;
        else if (strcmp(argv[j], "-f") == 0)
            f_flag = true;
        else if (j > 2)
        {
            printf("Illegal Arguments! to use, enter after './copy':\n");
            printf("1. File to copy FROM\n \
                    2. File to copy TO\n \
                    3. Optional Flags: -v for output -f to allow overwrite\n");
            return 1; // the input is not -v or -i
        }
    }
    FILE *ptr1;
    FILE *ptr2;
    char char_f1;
    ptr1 = fopen(argv[1], "r");
    if (access(argv[2], F_OK) == 0) // file exist
        if (f_flag != true)
        {
            if (v_flag == true)
                printf("target file exist\n");
            return 1;
        }

    ptr2 = fopen(argv[2], "w+");
    if (ptr1 == NULL || ptr2 == NULL)
    {
        if (v_flag == true)
            printf("general failiure\n");
        return 1;
    }
    while (!feof(ptr1))
    {
        if ((char_f1 = fgetc(ptr1)) == 255)
            break;
        fputc(char_f1, ptr2);
    }
    fclose(ptr1);
    fclose(ptr2);

    if (v_flag == true)
        printf("success\n");
    return 0;
}