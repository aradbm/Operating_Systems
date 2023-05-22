#include "reactor.h"
#include <stdlib.h>
#include <sys/select.h>

reactor_t *createReactor()
{
    reactor_t *reactor = malloc(sizeof(reactor_t));
    FD_ZERO(&reactor->read_fds);
    reactor->max_fd = -1;
    reactor->handlers = hashmap_create();
    pthread_mutex_init(&reactor->lock, NULL);  // Initialize the mutex
    return reactor;
}

void stopReactor(reactor_t *reactor)
{
    hashmap_destroy(reactor->handlers);
    pthread_mutex_destroy(&reactor->lock);  // Destroy the mutex
    free(reactor);
}

void addFd(reactor_t *reactor, int fd, handler_t handler)
{
    pthread_mutex_lock(&reactor->lock);  // Acquire the lock

    FD_SET(fd, &reactor->read_fds);
    if (fd > reactor->max_fd)
    {
        reactor->max_fd = fd;
    }
    hashmap_add(reactor->handlers, fd, handler);

    pthread_mutex_unlock(&reactor->lock);  // Release the lock
}

void startReactor(reactor_t *reactor)
{
    while (1)
    {
        fd_set temp_set;

        pthread_mutex_lock(&reactor->lock);  // Acquire the lock
        temp_set = reactor->read_fds;
        pthread_mutex_unlock(&reactor->lock);  // Release the lock

        if (select(reactor->max_fd + 1, &temp_set, NULL, NULL, NULL) == -1)
        {
            exit(4);
        }

        pthread_mutex_lock(&reactor->lock);  // Acquire the lock

        for (int i = 0; i <= reactor->max_fd; i++)
        {
            if (FD_ISSET(i, &temp_set))
            {
                handler_t handler = hashmap_get(reactor->handlers, i);
                if (handler != NULL)
                {
                    handler(i);
                }
            }
        }

        pthread_mutex_unlock(&reactor->lock);  // Release the lock
    }
}
