#include "../include/kernel.h"

#define MAX_DEVICES 32

typedef struct {
    char name[32];
    void* driver;
    int active;
} device_t;

static device_t devices[MAX_DEVICES];
static uint8_t device_count = 0;

// Initialize device management system
void device_init(void) {
    for (int i = 0; i < MAX_DEVICES; i++) {
        devices[i].active = 0;
        memset(devices[i].name, 0, 32);
        devices[i].driver = NULL;
    }
    device_count = 0;
    
    // Register built-in devices
    device_register("VGA Display", NULL);
    device_register("PS/2 Keyboard", NULL);
    device_register("PIT Timer", NULL);
    device_register("RTC Clock", NULL);
}

// Register a new device
void device_register(const char* name, void* driver) {
    if (device_count >= MAX_DEVICES) {
        return; // Device table full
    }
    
    // Copy device name
    size_t name_len = strlen(name);
    if (name_len >= 32) name_len = 31;
    
    memcpy(devices[device_count].name, name, name_len);
    devices[device_count].name[name_len] = '\0';
    devices[device_count].driver = driver;
    devices[device_count].active = 1;
    
    device_count++;
    
    // Simulate device hotplug notification
    terminal_writestring("Device registered: ");
    terminal_writestring(name);
    terminal_writestring("\n");
}

// Unregister a device
void device_unregister(const char* name) {
    for (uint8_t i = 0; i < device_count; i++) {
        if (devices[i].active && strcmp(devices[i].name, name) == 0) {
            devices[i].active = 0;
            terminal_writestring("Device unregistered: ");
            terminal_writestring(name);
            terminal_writestring("\n");
            return;
        }
    }
}

// List all registered devices
void device_list(void) {
    terminal_writestring("Registered devices:\n");
    for (uint8_t i = 0; i < device_count; i++) {
        if (devices[i].active) {
            terminal_writestring("  - ");
            terminal_writestring(devices[i].name);
            terminal_writestring("\n");
        }
    }
}

// Simple keyboard driver
typedef struct {
    char buffer[256];
    uint8_t head;
    uint8_t tail;
} keyboard_driver_t;

static keyboard_driver_t keyboard_driver;

void keyboard_init(void) {
    keyboard_driver.head = 0;
    keyboard_driver.tail = 0;
    memset(keyboard_driver.buffer, 0, 256);
}

void keyboard_add_char(char c) {
    uint8_t next_head = (keyboard_driver.head + 1) % 256;
    if (next_head != keyboard_driver.tail) {
        keyboard_driver.buffer[keyboard_driver.head] = c;
        keyboard_driver.head = next_head;
    }
}

char keyboard_get_char(void) {
    if (keyboard_driver.head == keyboard_driver.tail) {
        return 0; // Buffer empty
    }
    
    char c = keyboard_driver.buffer[keyboard_driver.tail];
    keyboard_driver.tail = (keyboard_driver.tail + 1) % 256;
    return c;
}