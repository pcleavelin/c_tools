// Super simple arena allocator
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "arena.h"

Arena new_arena(unsigned long size) {
    void *backingMemory = malloc(size);
    if(backingMemory == NULL) {
        assert(false && "new_arena: malloc returned NULL");
    }

    Arena a = {
        size,
        0, // start arena off at beginning
        backingMemory,
    };

    return a;
}

void *arena_allocate_block(Arena *arena, unsigned long size) {
    if ((arena->index + size) > arena->totalSize) {
        assert(false && "arena_allocate_block: ran out of memory");
        return NULL;
    }

    void *mem = (char *)arena->backingMemory + arena->index;
    arena->index += size;

    return mem;
}

char *arena_allocate_string(Arena *arena, unsigned long size) {
    char *mem = (char *)arena_allocate_block(arena, size+1);

    mem[size] = 0;

    return mem;
}

void arena_clear(Arena *arena) {
    arena->index = 0;
}
