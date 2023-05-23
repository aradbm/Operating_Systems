#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

hashmap_t *hashmap_create()
{
    hashmap_t *map = malloc(sizeof(hashmap_t));
    map->pairs = NULL;
    map->num_pairs = 0;
    pthread_mutex_init(&(map->mutex), NULL);
    return map;
}
void hashmap_destroy(hashmap_t *map)
{
    pthread_mutex_destroy(&(map->mutex));
    free(map->pairs);
    free(map);
}

void hashmap_add(hashmap_t *map, int fd, handler_t handler)
{
    pthread_mutex_lock(&(map->mutex));
    map->pairs = realloc(map->pairs, (map->num_pairs + 1) * sizeof(fd_handler_pair_t));
    map->pairs[map->num_pairs].fd = fd;
    map->pairs[map->num_pairs].handler = handler;
    map->num_pairs++;
    pthread_mutex_unlock(&(map->mutex));
}

handler_t hashmap_get(hashmap_t *map, int fd)
{
    pthread_mutex_lock(&(map->mutex));
    for (size_t i = 0; i < map->num_pairs; i++)
    {
        if (map->pairs[i].fd == fd)
        {
            handler_t handler = map->pairs[i].handler;
            pthread_mutex_unlock(&(map->mutex));
            return handler;
        }
    }
    pthread_mutex_unlock(&(map->mutex));
    return NULL;
}

void hashmap_remove(hashmap_t *map, int fd)
{
    pthread_mutex_lock(&(map->mutex));
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
    pthread_mutex_unlock(&(map->mutex));
}