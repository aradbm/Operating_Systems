#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

typedef void (*handler_t)(int);

typedef struct
{
    int fd;
    handler_t handler;
} fd_handler_pair_t;

typedef struct
{
    fd_handler_pair_t *pairs;
    size_t num_pairs;
    pthread_mutex_t mutex;
} hashmap_t;

hashmap_t *hashmap_create();
void hashmap_destroy(hashmap_t *map);
void hashmap_add(hashmap_t *map, int fd, handler_t handler);
handler_t hashmap_get(hashmap_t *map, int fd);
void hashmap_remove(hashmap_t *map, int fd);
#endif
