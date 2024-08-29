#include "idt.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
#include "io/io.h"
struct idt_desc idt_descriptors[PEACHOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);
extern void int21hKeyboardHandler();
extern void int0h();

extern void no_interrupt();
extern void int20hTimerHandler();

void int21h_keyboard_handler()
{
    print("Keyboard pressed!\n");
    outb(0x20, 0x20);
}

void int20h_timer_handler()
{
    print("Timer activated!\n");
    outb(0x20, 0x20);
}

void no_interrupt_handler()
{
    outb(0x20, 0x20);
}

void int0h_handler()
{
    print("Divide by zero error\n");
    outb(0x20, 0x20);
}

void idt_set(int interrupt_no, void* address)
{
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}

void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) -1;
    idtr_descriptor.base = (uint32_t) idt_descriptors;

    for (int i = 0; i < PEACHOS_TOTAL_INTERRUPTS; i++)
    {
        idt_set(i, no_interrupt);
    }

    idt_set(0, int0h);
    idt_set(0x21, int21hKeyboardHandler);
    idt_set(0x20, int20hTimerHandler);


    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}