#include "../include/kernel.h"

// Global variables
static uint16_t* terminal_buffer;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;

// Create VGA color attribute
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

// Create VGA entry
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

// Terminal initialization
void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) VGA_MEMORY;
    
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

// Set terminal color
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

// Clear terminal
void terminal_clear(void) {
    terminal_row = 0;
    terminal_column = 0;
    
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

// Put character at terminal position
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

// Scroll terminal up one line
void terminal_scroll(void) {
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    
    // Clear last line
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }
    
    terminal_row = VGA_HEIGHT - 1;
}

// Put character to terminal
void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_scroll();
        }
        return;
    }
    
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_scroll();
        }
    }
}

// Write data to terminal
void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

// Write string to terminal
void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

// Kernel main function
void kernel_main(void) {
    // Initialize terminal
    terminal_initialize();
    
    // Display welcome message
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
    terminal_writestring("Welcome to OrangeOS v1.0\n");
    terminal_writestring("Educational Operating System\n\n");
    
    // Initialize subsystems
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    terminal_writestring("Initializing subsystems...\n");
    
    memory_init();
    terminal_writestring("Memory management initialized\n");
    
    timer_init();
    terminal_writestring("Timer system initialized\n");
    
    device_init();
    terminal_writestring("Device management initialized\n");
    
    // Hardware detection
    terminal_writestring("\nDetecting hardware...\n");
    detect_cpu();
    detect_memory();
    detect_pci_devices();
    detect_floppy();
    
    // Initialize and run shell
    terminal_writestring("\nStarting shell...\n\n");
    shell_init();
    shell_run();
}