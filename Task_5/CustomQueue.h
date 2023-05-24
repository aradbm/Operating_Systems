#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include <pthread.h>

typedef struct QueueNode
{
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front, *rear;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Queue;

Queue *initQueue();
void enqueue(Queue *q, void *data);
void *dequeue(Queue *q);

#endif /* CUSTOM_QUEUE_H */
