#include "kernel.h"

static uint16_t* video_memory = (uint16_t*)VIDEO_MEMORY;
static int cursor_x = 0;
static int cursor_y = 0;

void kernel_main(void) {
    clear_screen();
    
    // Print welcome message
    print_colored("SimpleOS Kernel v1.0", COLOR_LIGHT_GREEN);
    print_string("\n");
    print_colored("Written in C and x86 Assembly", COLOR_LIGHT_CYAN);
    print_string("\n\n");
    
    // Initialize system components
    print_string("Initializing system components...\n");
    init_interrupts();
    init_memory();
    
    print_colored("System initialized successfully!\n\n", COLOR_LIGHT_GREEN);
    
    // Detect and list devices
    print_colored("=== Device Detection ===\n", COLOR_YELLOW);
    detect_devices();
    
    print_string("\n");
    print_colored("=== System Information ===\n", COLOR_YELLOW);
    print_string("CPU: x86 Compatible Processor\n");
    print_string("Memory: Basic memory management active\n");
    print_string("Video: VGA Text Mode (80x25)\n\n");
    
    // Start simple shell
    simple_shell();
}

void clear_screen(void) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = (COLOR_WHITE << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print_string(const char* str) {
    print_colored(str, COLOR_WHITE);
}

void print_colored(const char* str, uint8_t color) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            int pos = cursor_y * SCREEN_WIDTH + cursor_x;
            if (pos < SCREEN_WIDTH * SCREEN_HEIGHT) {
                video_memory[pos] = (color << 8) | *str;
                cursor_x++;
                if (cursor_x >= SCREEN_WIDTH) {
                    cursor_x = 0;
                    cursor_y++;
                }
            }
        }
        str++;
    }
}

void print_hex(uint32_t num) {
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[11] = "0x";
    
    for (int i = 7; i >= 0; i--) {
        buffer[2 + (7 - i)] = hex_chars[(num >> (i * 4)) & 0xF];
    }
    buffer[10] = '\0';
    
    print_string(buffer);
}

void simple_shell(void) {
    print_colored("SimpleOS Shell - Type 'help' for commands\n", COLOR_LIGHT_CYAN);
    
    while (1) {
        print_colored("os> ", COLOR_LIGHT_GREEN);
        
        // Simple command simulation
        print_string("help\n");
        print_string("Available commands:\n");
        print_string("  help    - Show this help message\n");
        print_string("  clear   - Clear the screen\n");
        print_string("  devices - List detected devices\n");
        print_string("  reboot  - Restart the system\n\n");
        
        // For demonstration, we'll break after showing help
        break;
    }
}