#include "../include/kernel.h"

static volatile uint32_t timer_ticks = 0;
static void (*timer_callbacks[16])(void) = {0};
static uint8_t callback_count = 0;

// Timer interrupt handler
void timer_interrupt_handler(void) {
    timer_ticks++;
    
    // Call registered callbacks every 100 ticks (approximately 1 second)
    if (timer_ticks % 100 == 0) {
        for (uint8_t i = 0; i < callback_count; i++) {
            if (timer_callbacks[i]) {
                timer_callbacks[i]();
            }
        }
    }
    
    // Send EOI to PIC
    outb(0x20, 0x20);
}

// Initialize PIT timer
void timer_init(void) {
    // Set PIT frequency to ~100Hz
    uint16_t divisor = 1193180 / 100;
    
    outb(0x43, 0x36);  // Command byte: channel 0, lobyte/hibyte, rate generator
    outb(0x40, divisor & 0xFF);        // Low byte
    outb(0x40, (divisor >> 8) & 0xFF); // High byte
    
    // Install timer interrupt handler (simplified - would need proper IDT setup)
    timer_ticks = 0;
}

// Register a timer callback
void timer_register_callback(void (*callback)(void)) {
    if (callback_count < 16) {
        timer_callbacks[callback_count++] = callback;
    }
}

// Get current timer ticks
uint32_t timer_get_ticks(void) {
    return timer_ticks;
}

// Default timer callback
void timer_callback(void) {
    // This could be used for periodic system maintenance
    // For now, it's just a placeholder
}