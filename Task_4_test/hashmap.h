#ifndef HASHMAP_H
#define HASHMAP_H

#include <pthread.h>

typedef struct {
    int fd;
    handler_t handler;
} fd_handler_pair_t;

typedef struct {
    fd_handler_pair_t *pairs;
    size_t num_pairs;
    pthread_mutex_t lock;  // Mutex for synchronization
} hashmap_t;

hashmap_t *hashmap_create();
void hashmap_destroy(hashmap_t *map);
void hashmap_add(hashmap_t *map, int fd, handler_t handler);
handler_t hashmap_get(hashmap_t *map, int fd);
void hashmap_remove(hashmap_t *map, int fd);

#endif /* HASHMAP_H */
