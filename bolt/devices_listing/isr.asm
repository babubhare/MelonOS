; Interrupt Service Routines - isr.asm
[BITS 32]

global isr0
global isr1
global load_idt

extern divide_by_zero_handler
extern debug_handler

; Load IDT
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; ISR 0 - Division by Zero
isr0:
    pusha
    call divide_by_zero_handler
    popa
    iret

; ISR 1 - Debug
isr1:
    pusha
    call debug_handler
    popa
    iret