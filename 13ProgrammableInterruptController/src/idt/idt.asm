section .asm

extern int21h_keyboard_handler
extern int0h_handler
extern no_interrupt_handler
extern int20h_timer_handler

global int21hKeyboardHandler
global int0h
global idt_load
global no_interrupt
global int20hTimerHandler

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]
    pop ebp    
    ret


int21hKeyboardHandler:
    cli
    pushad
    call int21h_keyboard_handler
    popad
    sti
    iret

no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret

int0h:
    cli
    pushad
    call int0h_handler
    popad
    sti
    iret
    

int20hTimerHandler:
    cli
    pushad
    call int20h_timer_handler
    popad
    sti
    iret
    