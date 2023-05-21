#ifndef REACTOR_H
#define REACTOR_H

#include "hashmap.h"

typedef struct
{
    int max_fd;
    fd_set read_fds;
    hashmap_t *handlers;
} reactor_t;

reactor_t *createReactor();
void stopReactor(reactor_t *reactor);
void addFd(reactor_t *reactor, int fd, handler_t handler);
void startReactor(reactor_t *reactor);

#endif
