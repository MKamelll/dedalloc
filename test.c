#define DEDALLOC_IMPLEMENTATION
#include "dedalloc.h"

#include<stdio.h>
#include<string.h>

int main()
{
    arena_t arena = dedalloc_init(1024);

    if (!dedalloc_arena_is_initialized(&arena)) {
        printf("Couldn't initialize an Arena\n");
        exit(1);
    }
    
    const char * data = "Hello";
    size_t data_len = strlen(data) + 1;
    
    char * str = (char*)dedalloc_alloc(&arena, data_len * sizeof(char));

    if (str == NULL) {
        printf("Arena is empty!\n");
        dedalloc_clean(&arena);
        exit(1);
    }
    
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

    if (str2 == NULL) {
        printf("Stop this madness!\n");
        dedalloc_clean(&arena);
        exit(1);
    }

    
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
