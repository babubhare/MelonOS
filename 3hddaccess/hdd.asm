ORG 0
BITS 16

_start:
    jmp short start
    nop

    times 33 db 0

start:
    jmp 0x7c0: step2


step2:
    cli
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax

    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti

    ; REad from HDD and load to the buffer address
    mov ah, 2
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, buffer
    int 0x13

    jc error

    mov si, buffer
    call print

    jmp $

error:
    mov si, error_message
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
error_message: db 'Error Message', 0
times 510-($ - $$) db 0
dw 0xAA55

buffer:
