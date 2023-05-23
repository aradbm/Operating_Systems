#ifndef REACTOR_H
#define REACTOR_H

#include "hashmap.h"

typedef struct
{
    int max_fd;
    fd_set read_fds;
    hashmap_t *handlers;
} reactor_t;

reactor_t *reactor_create();
void reactor_destroy(reactor_t *reactor);
void reactor_add_handler(reactor_t *reactor, int fd, handler_t handler);
void reactor_run(reactor_t *reactor);
void reactor_remove_handler(reactor_t *reactor, int fd);
#endif
