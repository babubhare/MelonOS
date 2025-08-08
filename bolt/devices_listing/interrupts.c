#include "kernel.h"

// Interrupt Descriptor Table
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idt_pointer;

// Assembly interrupt handlers (simplified)
extern void isr0(void);
extern void isr1(void);
extern void load_idt(uint32_t);

void init_interrupts(void) {
    print_string("  Setting up Interrupt Descriptor Table...\n");
    
    // Set up IDT pointer
    idt_pointer.limit = sizeof(idt) - 1;
    idt_pointer.base = (uint32_t)&idt;
    
    // Clear IDT
    for (int i = 0; i < 256; i++) {
        idt[i].base_low = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].type_attr = 0;
        idt[i].base_high = 0;
    }
    
    // Install some basic interrupt handlers
    set_idt_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    set_idt_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    
    // Load IDT
    load_idt((uint32_t)&idt_pointer);
    
    print_string("  Interrupts initialized\n");
}

void set_idt_gate(int n, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].selector = selector;
    idt[n].zero = 0;
    idt[n].type_attr = flags;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}

// Simple interrupt handlers
void divide_by_zero_handler(void) {
    print_colored("Error: Division by zero!\n", COLOR_LIGHT_RED);
}

void debug_handler(void) {
    print_colored("Debug interrupt triggered\n", COLOR_YELLOW);
}