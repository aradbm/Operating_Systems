#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

// #include <stdio.h>
#include "codec.h"
#include <dlfcn.h>

#endif

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("there was a mistake with args\n");
        return -1;
    }
    else
    {
        char *src = argv[2];
        char *dest = argv[2] + strlen(argv[2]);

        char check[strlen(argv[1]) + 5];
        strcpy(check, "./");
        strncat(check, argv[1], strlen(argv[1]));
        char *end = ".so";
        strncat(check, end, 3);
        void *handle = dlopen(check, RTLD_LAZY);

        if (handle == NULL)
        {
            return -1;
        }
        int (*func)(char *, char *, int);
        func = dlsym(handle, "encode");
        if (!func)
        {
            return -1;
        }
        func(src, dest, strlen(argv[2]));
        printf("the string :%s\n", src);
        dlclose(handle);
    }
    return 0;
}
