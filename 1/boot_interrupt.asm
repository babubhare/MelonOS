ORG 0
BITS 16

jmp 0x7c0: start

handle_interrupt_0: 
    mov ah, 0eh
    mov al, "I"
    mov bx, 0x00
    int 0x10

    mov ah, 0eh
    mov al, "0"
    mov bx, 0x00
    int 0x10

    iret

handle_interrupt_1: 
    mov ah, 0eh
    mov al, "I"
    mov bx, 0x00
    int 0x10

    mov ah, 0eh
    mov al, "1"
    mov bx, 0x00
    int 0x10

    iret

start:
    cli
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax

    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov word[ss:0x00], handle_interrupt_0
    mov word[ss:0x02], 0x7c0
    int 0

    mov word[ss:0x04], handle_interrupt_1
    mov word[ss:0x06], 0x7c0
    int 1

    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510-($ - $$) db 0
dw 0xAA55