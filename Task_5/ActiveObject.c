// ActiveObject.c
#include "ActiveObject.h"
#include <stdlib.h>
ActiveObject *CreateActiveObject(void (*func)(void *, ActiveObject *))
{
    ActiveObject *ao = (ActiveObject *)malloc(sizeof(ActiveObject));
    ao->queue = initQueue();
    ao->next = NULL;
    ao->func = func;

    pthread_create(&ao->thread, NULL, (void *(*)(void *))ActiveObjectLoop, (void *)ao);

    return ao;
}

void ActiveObjectLoop(ActiveObject *ao)
{
    void *task;
    while ((task = dequeue(ao->queue)) != NULL)
    {
        ao->func(task, ao->next);
        free(task);
    }
}

Queue *getQueue(ActiveObject *ao)
{
    return ao->queue;
}

void stop(ActiveObject *ao)
{
    pthread_cancel(ao->thread);
    free(ao->queue);
    free(ao);
}
