[BITS 32]

global _start
global _problem
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    call kernel_main
    ;Calling the interrupt
    ;int 100
   

_problem: 
    int 100

    jmp $

times 512-($ - $$) db 0
