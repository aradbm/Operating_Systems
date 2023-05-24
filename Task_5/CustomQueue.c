#include "CustomQueue.h"
#include <stdlib.h>

Queue *initQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
    return q;
}

void enqueue(Queue *q, void *data)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->next = NULL;

    pthread_mutex_lock(&q->lock);

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        pthread_cond_signal(&q->cond);
    }
    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }

    pthread_mutex_unlock(&q->lock);
}

void *dequeue(Queue *q)
{
    pthread_mutex_lock(&q->lock);

    while (q->front == NULL) // Queue is empty
        pthread_cond_wait(&q->cond, &q->lock);

    QueueNode *temp = q->front;
    void *data = temp->data;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    pthread_mutex_unlock(&q->lock);

    free(temp);

    return data;
}
