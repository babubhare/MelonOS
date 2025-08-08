#include "kernel.h"

// Port I/O functions implemented in assembly
uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}

uint16_t inw(uint16_t port) {
    uint16_t result;
    __asm__ volatile ("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void outw(uint16_t port, uint16_t data) {
    __asm__ volatile ("outw %0, %1" : : "a" (data), "dN" (port));
}

uint32_t inl(uint16_t port) {
    uint32_t result;
    __asm__ volatile ("inl %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void outl(uint16_t port, uint32_t data) {
    __asm__ volatile ("outl %0, %1" : : "a" (data), "dN" (port));
}

// Keyboard input (simplified)
uint8_t get_keyboard_input(void) {
    while (!(inb(0x64) & 1)) {
        // Wait for key press
    }
    return inb(0x60);
}