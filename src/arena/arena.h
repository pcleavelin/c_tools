#ifndef ARENA_H
#define ARENA_H

typedef struct Arena {
    unsigned long totalSize;
    unsigned long index;
    void *backingMemory;
} Arena;

Arena new_arena(unsigned long size);
void *arena_allocate_block(Arena *arena, unsigned long size);
char *arena_allocate_string(Arena *arena, unsigned long size);
void arena_clear(Arena *arena);

#endif
