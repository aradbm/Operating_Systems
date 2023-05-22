#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

hashmap_t *hashmap_create()
{
    hashmap_t *map = malloc(sizeof(hashmap_t));
    map->pairs = NULL;
    map->num_pairs = 0;
    pthread_mutex_init(&map->lock, NULL);  // Initialize the mutex
    return map;
}

void hashmap_destroy(hashmap_t *map)
{
    free(map->pairs);
    pthread_mutex_destroy(&map->lock);  // Destroy the mutex
    free(map);
}

void hashmap_add(hashmap_t *map, int fd, handler_t handler)
{
    pthread_mutex_lock(&map->lock);  // Acquire the lock

    map->pairs = realloc(map->pairs, (map->num_pairs + 1) * sizeof(fd_handler_pair_t));
    map->pairs[map->num_pairs].fd = fd;
    map->pairs[map->num_pairs].handler = handler;
    map->num_pairs++;

    pthread_mutex_unlock(&map->lock);  // Release the lock
}

handler_t hashmap_get(hashmap_t *map, int fd)
{
    handler_t result = NULL;

    pthread_mutex_lock(&map->lock);  // Acquire the lock

    for (size_t i = 0; i < map->num_pairs; i++)
    {
        if (map->pairs[i].fd == fd)
        {
            result = map->pairs[i].handler;
            break;
        }
    }

    pthread_mutex_unlock(&map->lock);  // Release the lock

    return result;
}

void hashmap_remove(hashmap_t *map, int fd)
{
    pthread_mutex_lock(&map->lock);  // Acquire the lock

    size_t i = 0;
    for (; i < map->num_pairs; i++)
    {
        if (map->pairs[i].fd == fd)
        {
            break;
        }
    }

    if (i != map->num_pairs)
    {
        memmove(&map->pairs[i], &map->pairs[i + 1], (map->num_pairs - i - 1) * sizeof(fd_handler_pair_t));
        map->num_pairs--;
        map->pairs = realloc(map->pairs, map->num_pairs * sizeof(fd_handler_pair_t));
    }

    pthread_mutex_unlock(&map->lock);  // Release the lock
}
