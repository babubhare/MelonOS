; Simple Bootloader - boot.asm
; This bootloader loads our kernel from disk and jumps to it

[BITS 16]
[ORG 0x7C00]

; Boot sector starts here
start:
    ; Set up segments
    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Print boot message
    mov si, boot_msg
    call print_string

    ; Load kernel from disk
    mov ah, 0x02        ; Read sectors function
    mov al, 15          ; Number of sectors to read
    mov ch, 0           ; Cylinder 0
    mov cl, 2           ; Sector 2 (sector 1 is boot sector)
    mov dh, 0           ; Head 0
    mov dl, 0x80        ; Drive 0x80 (first hard disk)
    mov bx, 0x1000      ; Load kernel at 0x1000
    int 0x13            ; BIOS disk interrupt

    jc disk_error       ; Jump if carry flag set (error)

    ; Switch to protected mode
    cli                 ; Disable interrupts
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt

print_string:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print_string
done:
    ret

; Global Descriptor Table
gdt:
    dq 0x0000000000000000    ; Null descriptor
    dq 0x00CF9A000000FFFF    ; Code segment
    dq 0x00CF92000000FFFF    ; Data segment

gdt_descriptor:
    dw gdt_descriptor - gdt - 1
    dd gdt

[BITS 32]
protected_mode:
    mov ax, 0x10        ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000    ; Set up stack

    ; Jump to kernel
    jmp 0x1000

boot_msg db 'SimpleOS Bootloader v1.0', 0x0D, 0x0A, 'Loading kernel...', 0x0D, 0x0A, 0
disk_error_msg db 'Disk read error!', 0x0D, 0x0A, 0

; Pad to 510 bytes and add boot signature
times 510-($-$$) db 0
dw 0xAA55