qemu-system-i386 -hda ./boot_segment.bin -S -gdb tcp:127.0.0.1:1234 -nographic

Open another prompt
    gdb
    target remote tcp:127.0.0.1:1234
    add-symbol-file ./build/kernelfull.o 0x0100000
    set print pretty on
    break _start
    break kernel_main
    c "continue"
    info registers
    frame
    n (next)
    cntrl c
    disas 0x0100000, 0x0100fff
    layout asm
    layout prev
    exit from layout asm CTRL+X, A
    view memory location x/5i 0x7c00
    CTRL + A ; X to exit from qemu
    p ($esp + (void *)&intValue1)
    p/x *above address
    info address variable
    set print pretty on
    dump memory memorydump.bin 0x00 0xffff
    cp -r memorydump.bin /root/shared