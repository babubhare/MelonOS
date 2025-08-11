#include "../include/kernel.h"

#define MAX_COMMAND_LENGTH 256

static char command_buffer[MAX_COMMAND_LENGTH];
static size_t command_length = 0;

// Get current time from RTC
void get_time(void) {
    uint8_t second, minute, hour, day, month, year;
    
    // Read from RTC
    outb(0x70, 0x00); second = inb(0x71);
    outb(0x70, 0x02); minute = inb(0x71);
    outb(0x70, 0x04); hour = inb(0x71);
    outb(0x70, 0x07); day = inb(0x71);
    outb(0x70, 0x08); month = inb(0x71);
    outb(0x70, 0x09); year = inb(0x71);
    
    // Convert from BCD if necessary
    if (!(inb(0x71) & 0x04)) {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
    }
    
    terminal_writestring("Current time: ");
    // Simple time display (would need proper formatting in real implementation)
    terminal_writestring("20XX-XX-XX XX:XX:XX\n");
}

// List devices command
void list_devices(void) {
    terminal_writestring("Connected devices:\n");
    terminal_writestring("  - VGA Text Display\n");
    terminal_writestring("  - PS/2 Keyboard\n");
    terminal_writestring("  - PIT Timer\n");
    terminal_writestring("  - RTC Clock\n");
    terminal_writestring("  - PCI Bus\n");
}

// Help command
void show_help(void) {
    terminal_writestring("OrangeOS Shell Commands:\n");
    terminal_writestring("  help     - Show this help message\n");
    terminal_writestring("  clear    - Clear the screen\n");
    terminal_writestring("  time     - Show current system time\n");
    terminal_writestring("  devices  - List connected devices\n");
    terminal_writestring("  memory   - Show memory information\n");
    terminal_writestring("  cpu      - Show CPU information\n");
    terminal_writestring("  reboot   - Restart the system\n");
    terminal_writestring("  shutdown - Halt the system\n");
}

// Memory info command
void show_memory_info(void) {
    terminal_writestring("Memory Information:\n");
    terminal_writestring("  Total RAM: 16MB (simulated)\n");
    terminal_writestring("  Kernel Heap: 1MB\n");
    terminal_writestring("  Available: ~15MB\n");
}

// CPU info command
void show_cpu_info(void) {
    terminal_writestring("CPU Information:\n");
    detect_cpu();
}

// Reboot system
void reboot_system(void) {
    terminal_writestring("Rebooting system...\n");
    // Triple fault to reboot
    asm volatile("int $0x00");
}

// Shutdown system
void shutdown_system(void) {
    terminal_writestring("System halted. You can now power off.\n");
    asm volatile("hlt");
}

// Process command
void process_command(void) {
    if (command_length == 0) return;
    
    command_buffer[command_length] = '\0';
    
    if (strcmp(command_buffer, "help") == 0) {
        show_help();
    } else if (strcmp(command_buffer, "clear") == 0) {
        terminal_clear();
    } else if (strcmp(command_buffer, "time") == 0) {
        get_time();
    } else if (strcmp(command_buffer, "devices") == 0) {
        list_devices();
    } else if (strcmp(command_buffer, "memory") == 0) {
        show_memory_info();
    } else if (strcmp(command_buffer, "cpu") == 0) {
        show_cpu_info();
    } else if (strcmp(command_buffer, "reboot") == 0) {
        reboot_system();
    } else if (strcmp(command_buffer, "shutdown") == 0) {
        shutdown_system();
    } else {
        terminal_writestring("Unknown command: ");
        terminal_writestring(command_buffer);
        terminal_writestring("\nType 'help' for available commands.\n");
    }
    
    command_length = 0;
}

// Get keyboard input (simplified)
char get_keyboard_input(void) {
    // Wait for keyboard input
    while (!(inb(0x64) & 1));
    
    uint8_t scancode = inb(0x60);
    
    // Simple scancode to ASCII conversion (US keyboard layout)
    static char scancode_to_ascii[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*', 0, ' '
    };
    
    if (scancode < sizeof(scancode_to_ascii)) {
        return scancode_to_ascii[scancode];
    }
    
    return 0;
}

// Initialize shell
void shell_init(void) {
    command_length = 0;
    memset(command_buffer, 0, MAX_COMMAND_LENGTH);
}

// Main shell loop
void shell_run(void) {
    terminal_writestring("OrangeOS Shell v1.0\n");
    terminal_writestring("Type 'help' for available commands.\n\n");
    
    while (1) {
        terminal_writestring("orange> ");
        
        while (1) {
            char c = get_keyboard_input();
            
            if (c == '\n') {
                terminal_putchar('\n');
                process_command();
                break;
            } else if (c == '\b') {
                if (command_length > 0) {
                    command_length--;
                    terminal_writestring("\b \b");
                }
            } else if (c >= 32 && c <= 126 && command_length < MAX_COMMAND_LENGTH - 1) {
                command_buffer[command_length++] = c;
                terminal_putchar(c);
            }
        }
    }
}