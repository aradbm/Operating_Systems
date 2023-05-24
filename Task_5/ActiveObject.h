// ActiveObject.h
#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "CustomQueue.h"

typedef struct ActiveObject ActiveObject;

struct ActiveObject
{
    pthread_t thread;
    Queue *queue;
    ActiveObject *next;
    void (*func)(void *, ActiveObject *);
};

ActiveObject *CreateActiveObject(void (*func)(void *, ActiveObject *));
void ActiveObjectLoop(ActiveObject *ao);
Queue *getQueue(ActiveObject *ao);
void stop(ActiveObject *ao);

#endif
