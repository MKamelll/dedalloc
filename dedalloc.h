#ifndef DEDALLOC_H
#define DEDALLOC_H

#include<stddef.h>
#include<stdbool.h>

typedef struct {
    size_t capacity;
    size_t used;
    void * start;
} arena_t;

arena_t dedalloc_init(size_t capacity);
void * dedalloc_alloc(arena_t * arena, size_t size);
bool dedalloc_arena_is_initialized(arena_t * arena);
size_t dedalloc_available(arena_t * arena);
size_t dedalloc_available(arena_t * arena);
void dedalloc_clean(arena_t * arena);

#endif // DEDALLOC_H

/* ............................................................*/

#ifdef DEDALLOC_IMPLEMENTATION

#include<stdlib.h>
#include<string.h>

arena_t dedalloc_init(size_t capacity)
{
    void * start = malloc(capacity);
   
    return (arena_t) {
        .capacity = capacity,
        .used = 0,
        .start = start
    };
}

void * dedalloc_alloc(arena_t * arena, size_t size)
{
    if (size >= (arena->capacity - arena->used)) {
        //todo: handle reallocation if not enough size
        return NULL;
    }
    
    arena->used += size;

    size_t offset = arena->capacity - arena->used;

    void * start_of_block = (char*)arena->start + offset;

    memset(start_of_block, 0, size);

    return start_of_block; 
}

bool dedalloc_arena_is_initialized(arena_t * arena)
{
    if (arena != NULL && arena->start != NULL)
        return true;

    return false;
}

size_t dedalloc_available(arena_t * arena)
{
    return arena->capacity - arena->used;
}

void dedalloc_clean(arena_t * arena)
{
    free(arena->start);
}

#endif // DEDALLOC_IMPLEMENTATION
