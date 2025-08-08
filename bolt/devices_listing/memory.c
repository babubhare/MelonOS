#include "kernel.h"

// Simple memory management
static uint32_t memory_start = 0x100000;  // 1MB mark
static uint32_t memory_end = 0x1000000;   // 16MB (assumed)

typedef struct memory_block {
    uint32_t size;
    int free;
    struct memory_block* next;
} memory_block_t;

static memory_block_t* first_block = NULL;

void init_memory(void) {
    print_string("  Initializing memory management...\n");
    
    // Initialize first memory block
    first_block = (memory_block_t*)memory_start;
    first_block->size = memory_end - memory_start - sizeof(memory_block_t);
    first_block->free = 1;
    first_block->next = NULL;
    
    print_string("  Memory management initialized\n");
}

void* kmalloc(uint32_t size) {
    memory_block_t* current = first_block;
    
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            
            // Split block if it's much larger than needed
            if (current->size > size + sizeof(memory_block_t) + 64) {
                memory_block_t* new_block = (memory_block_t*)((uint8_t*)current + sizeof(memory_block_t) + size);
                new_block->size = current->size - size - sizeof(memory_block_t);
                new_block->free = 1;
                new_block->next = current->next;
                
                current->size = size;
                current->next = new_block;
            }
            
            return (void*)((uint8_t*)current + sizeof(memory_block_t));
        }
        current = current->next;
    }
    
    return NULL;  // Out of memory
}

void kfree(void* ptr) {
    if (!ptr) return;
    
    memory_block_t* block = (memory_block_t*)((uint8_t*)ptr - sizeof(memory_block_t));
    block->free = 1;
    
    // Simple coalescing with next block
    if (block->next && block->next->free) {
        block->size += block->next->size + sizeof(memory_block_t);
        block->next = block->next->next;
    }
}

uint32_t get_memory_usage(void) {
    uint32_t used = 0;
    memory_block_t* current = first_block;
    
    while (current) {
        if (!current->free) {
            used += current->size;
        }
        current = current->next;
    }
    
    return used;
}