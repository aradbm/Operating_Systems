// st_pipeline.c
#include "st_pipeline.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Prime.h"
#include "ActiveObject.h"

void printAndCheckPrime(void *num, ActiveObject *nextAo)
{
    unsigned int number = *((unsigned int *)num);
    printf("Number: %u, is Prime: %s\n", number, isPrime(number) ? "True" : "False");
    number += 11;

    if (nextAo)
    {
        unsigned int *nextNum = (unsigned int *)malloc(sizeof(unsigned int));
        *nextNum = number;
        enqueue(getQueue(nextAo), nextNum);
    }
}

void subtractThirteen(void *num, ActiveObject *nextAo)
{
    unsigned int number = *((unsigned int *)num);
    printf("Number: %u, is Prime: %s\n", number, isPrime(number) ? "True" : "False");
    number -= 13;

    if (nextAo)
    {
        unsigned int *nextNum = (unsigned int *)malloc(sizeof(unsigned int));
        *nextNum = number;
        enqueue(getQueue(nextAo), nextNum);
    }
}

void addTwoAndPrint(void *num, ActiveObject *nextAo)
{
    unsigned int number = *((unsigned int *)num);
    printf("Number: %u, is Prime: %s\n", number, isPrime(number) ? "True" : "False");
    number += 2;
    printf("New Number: %u\n", number);
}

int main(int argc, char *argv[])
{
    srand((argc > 2) ? atoi(argv[2]) : time(NULL));

    int tasks = (argc > 1) ? atoi(argv[1]) : 10;

    ActiveObject *ao1 = CreateActiveObject(printAndCheckPrime);
    ActiveObject *ao2 = CreateActiveObject(subtractThirteen);
    ActiveObject *ao3 = CreateActiveObject(addTwoAndPrint);

    // Set up the pipeline
    ao1->next = ao2;
    ao2->next = ao3;

    for (int i = 0; i < tasks; i++)
    {
        unsigned int *num = (unsigned int *)malloc(sizeof(unsigned int));
        *num = rand() % 1000000;
        printf("Enqueuing: %u\n", *num);
        enqueue(getQueue(ao1), num);
        printf("------------------------------------------------------\n");
        sleep(1);
    }
    sleep(2);
    stop(ao1);
    stop(ao2);
    stop(ao3);
    return 0;
}
