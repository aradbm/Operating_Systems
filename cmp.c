#include "stdio.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
int main(int argc, char **argv)
{
    bool v = false, i = false, same = true; // check if -v or -i
    if (argc < 3)
        return -1;
    for (size_t j = 0; j < argc; j++)
    {
        if (strcmp(argv[j], "-v") == 0)
            v = true;
        else if (strcmp(argv[j], "-i") == 0)
            i = true;
        else if (j > 2)
            return -1; // the input is not -v or -i
    }
    FILE *ptr1;
    FILE *ptr2;
    char char_f1;
    char char_f2;
    ptr1 = fopen(argv[1], "r");
    ptr2 = fopen(argv[2], "r");
    if (ptr1 == NULL || ptr2 == NULL)
    {
        printf("couldnt open the file! try again!\n");
        return -1;
    }
    while (feof(ptr1) == 0 || feof(ptr2) == 0)
    {
        char_f1 = fgetc(ptr1);
        char_f2 = fgetc(ptr2);
        if (i) // if -i than ignore case sensetivity
        {
            if (tolower(char_f1) != tolower(char_f2))
                same = false;
        }
        else
        {
            if (char_f1 != char_f2)
                same = false;
        }
    }
    if ((!ptr1 && ptr2) || (ptr1 && !ptr2))
    {
        same = false;
    }
    fclose(ptr1);
    fclose(ptr2);
    if (v == true)
    {
        if (same)
            printf("equal\n");
        else
            printf("distinct\n");
    }
    if (same)
    {
        return 0;
    }
    return 1;
}