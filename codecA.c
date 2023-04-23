#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "codec.h"

#endif

int encode(char *src, char *dst, int len)
{
    int i = 0;
    while (i < len)
    {
        if (isalpha(src[i]))
        {
            if (src[i] == tolower(src[i]))
            {
                src[i] = toupper(src[i]);
            }
            else
            {
                src[i] = tolower(src[i]);
            }
        }
        i += 1;
    }
    return 0;
}

int decode(char *src, char *dst, int len)
{
    int i = 0;
    while (i < len)
    {
        if (isalpha(src[i]))
        {
            if (src[i] == tolower(src[i]))
            {
                src[i] = toupper(src[i]);
            }
            else
            {
                src[i] = tolower(src[i]);
            }
        }
        i += 1;
    }
    return 0;
}

int main()
{
    printf("wrong name for the shared file\n");
    return 0;
}
