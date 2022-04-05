#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    size_t capacity;
    size_t used;
    void * start;
} arena_t;

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
        //TODO: Handle reallocation if not enough size
        printf("Arena doen't have enough space\n");
        exit(1);
    }

    arena->used += size;

    size_t offset = arena->capacity - arena->used;

    void * start_of_block = (char*)arena->start + offset;

    memset(start_of_block, 0, size);

    return start_of_block; 
}

bool arena_initialized(arena_t * arena)
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

int main()
{
    arena_t arena = dedalloc_init(1024);

    if (!arena_initialized(&arena)) {
        printf("Couldn't initialize an Arena\n");
        exit(1);
    }
    
    const char * data = "Hello";
    size_t data_len = strlen(data) + 1;
    
    char * str = (char*)dedalloc_alloc(&arena, data_len * sizeof(char));
    
    const char * data2 = "Some things in life are bad\n"
                         "They can really make you mad\n"
                         "Other things just make you swear and curse\n"
                         "When you're chewing on life's gristle\n"
                         "Don't grumble, give a whistle\n"
                         "And this'll help things turn out for the best\n"
                         "And...\n"
                         "Always look on the bright side of life\n"
                         "Always look on the light side of life";
    
    size_t data2_len = strlen(data2) + 1;
    
    char * str2 = (char*)dedalloc_alloc(&arena, data2_len * sizeof(char));

    
    strncpy(str, data, strlen(data));
    strncpy(str2, data2, strlen(data2));

    int a = 151245;
    int * b = (int*)dedalloc_alloc(&arena, sizeof(int));
    
    memcpy(b, &a, sizeof(int));

    printf("%s\n", str);
    printf("%s\n", str2);
    printf("%d\n", *b);

    dedalloc_clean(&arena);

    return 0;
}
