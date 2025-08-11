#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

// Basic type definitions
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// VGA text mode constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// VGA colors
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

// Memory management
#define HEAP_START 0x100000
#define HEAP_SIZE 0x100000

// Function declarations
void kernel_main(void);
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_setcolor(uint8_t color);
void terminal_clear(void);

// Memory management
void* kmalloc(size_t size);
void kfree(void* ptr);
void memory_init(void);

// Hardware detection
void detect_cpu(void);
void detect_memory(void);
void detect_pci_devices(void);
void detect_floppy(void);

// Shell
void shell_init(void);
void shell_run(void);

// Timer
void timer_init(void);
void timer_callback(void);

// Device management
void device_init(void);
void device_register(const char* name, void* driver);

// Utility functions
size_t strlen(const char* str);
int strcmp(const char* str1, const char* str2);
void* memset(void* ptr, int value, size_t size);
void* memcpy(void* dest, const void* src, size_t size);

// I/O operations
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t value);

#endif