#ifndef REACTOR_H
#define REACTOR_H

#include "hashmap.h"
#include <pthread.h>
#include <sys/select.h>

typedef struct {
    fd_set read_fds;
    int max_fd;
    hashmap_t *handlers;
    pthread_mutex_t lock;  // Mutex for synchronization
} reactor_t;

reactor_t *createReactor();
void stopReactor(reactor_t *reactor);
void addFd(reactor_t *reactor, int fd, handler_t handler);
void startReactor(reactor_t *reactor);
#endif

