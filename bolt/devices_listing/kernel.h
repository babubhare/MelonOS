#ifndef KERNEL_H
#define KERNEL_H

// Basic types
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Video memory
#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Colors
#define COLOR_BLACK     0
#define COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_CYAN      3
#define COLOR_RED       4
#define COLOR_MAGENTA   5
#define COLOR_BROWN     6
#define COLOR_LIGHT_GRAY 7
#define COLOR_DARK_GRAY  8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED  12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_YELLOW    14
#define COLOR_WHITE     15

// Function declarations
void kernel_main(void);
void clear_screen(void);
void print_string(const char* str);
void print_colored(const char* str, uint8_t color);
void print_hex(uint32_t num);
void init_interrupts(void);
void init_memory(void);
void detect_devices(void);
void simple_shell(void);

// I/O functions
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t data);

#endif