; OrangeOS Bootloader
; 512-byte boot sector that loads the kernel and transitions to protected mode

[BITS 16]
[ORG 0x7C00]

; Boot sector entry point
start:
    ; Initialize segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    
    ; Clear screen and display boot message
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    
    mov si, boot_msg
    call print_string
    
    ; Load kernel from disk (sector 2 onwards)
    mov ah, 0x02        ; Read sectors function
    mov al, 10          ; Number of sectors to read
    mov ch, 0           ; Cylinder 0
    mov cl, 2           ; Start from sector 2
    mov dh, 0           ; Head 0
    mov dl, 0x80        ; Drive 0 (first hard disk)
    mov bx, 0x1000      ; Load kernel at 0x1000
    int 0x13
    
    jc disk_error
    
    ; Enable A20 line
    call enable_a20
    
    ; Load GDT
    lgdt [gdt_descriptor]
    
    ; Enter protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    ; Jump to protected mode code
    jmp CODE_SEG:protected_mode

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt

; Print string function (16-bit mode)
print_string:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

; Enable A20 line
enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; Protected mode entry point
[BITS 32]
protected_mode:
    ; Set up segment registers for protected mode
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Set up stack
    mov esp, 0x90000
    
    ; Jump to kernel
    jmp 0x1000

; Global Descriptor Table
gdt_start:
    ; Null descriptor
    dd 0x0
    dd 0x0
    
    ; Code segment descriptor
    dw 0xFFFF       ; Limit (bits 0-15)
    dw 0x0000       ; Base (bits 0-15)
    db 0x00         ; Base (bits 16-23)
    db 10011010b    ; Access byte
    db 11001111b    ; Flags + Limit (bits 16-19)
    db 0x00         ; Base (bits 24-31)
    
    ; Data segment descriptor
    dw 0xFFFF       ; Limit (bits 0-15)
    dw 0x0000       ; Base (bits 0-15)
    db 0x00         ; Base (bits 16-23)
    db 10010010b    ; Access byte
    db 11001111b    ; Flags + Limit (bits 16-19)
    db 0x00         ; Base (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size
    dd gdt_start                ; Offset

; Constants
CODE_SEG equ gdt_start + 0x08
DATA_SEG equ gdt_start + 0x10

; Messages
boot_msg db 'OrangeOS Bootloader v1.0', 13, 10, 'Loading kernel...', 13, 10, 0
disk_error_msg db 'Disk read error!', 13, 10, 0

; Boot signature
times 510-($-$$) db 0
dw 0xAA55