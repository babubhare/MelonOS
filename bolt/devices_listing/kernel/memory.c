#include "../include/kernel.h"

// Simple heap management structure
typedef struct block {
    size_t size;
    int free;
    struct block* next;
} block_t;

static block_t* heap_start = NULL;
static uint8_t* heap_memory = (uint8_t*)HEAP_START;
static size_t heap_offset = 0;

// Initialize memory management
void memory_init(void) {
    heap_start = (block_t*)heap_memory;
    heap_start->size = HEAP_SIZE - sizeof(block_t);
    heap_start->free = 1;
    heap_start->next = NULL;
    heap_offset = sizeof(block_t);
}

// Simple malloc implementation
void* kmalloc(size_t size) {
    if (size == 0) return NULL;
    
    // Align size to 4 bytes
    size = (size + 3) & ~3;
    
    block_t* current = heap_start;
    
    while (current) {
        if (current->free && current->size >= size) {
            // Split block if it's much larger than needed
            if (current->size > size + sizeof(block_t) + 16) {
                block_t* new_block = (block_t*)((uint8_t*)current + sizeof(block_t) + size);
                new_block->size = current->size - size - sizeof(block_t);
                new_block->free = 1;
                new_block->next = current->next;
                
                current->size = size;
                current->next = new_block;
            }
            
            current->free = 0;
            return (uint8_t*)current + sizeof(block_t);
        }
        current = current->next;
    }
    
    return NULL; // Out of memory
}

// Simple free implementation
void kfree(void* ptr) {
    if (!ptr) return;
    
    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->free = 1;
    
    // Coalesce with next block if it's free
    if (block->next && block->next->free) {
        block->size += sizeof(block_t) + block->next->size;
        block->next = block->next->next;
    }
    
    // Coalesce with previous block if it's free
    block_t* current = heap_start;
    while (current && current->next != block) {
        current = current->next;
    }
    
    if (current && current->free) {
        current->size += sizeof(block_t) + block->size;
        current->next = block->next;
    }
}

// Detect available memory
void detect_memory(void) {
    terminal_writestring("Memory: 16MB available (simulated)\n");
    terminal_writestring("Heap: 1MB allocated for kernel use\n");
}