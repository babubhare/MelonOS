Commands:

./build.sh

1. Creates os.bin to bin directory
2. Debug symbols are available in build folder

Run qemu up command 
    qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 -nographic

Open another prompt
    gdb
    target remote tcp:127.0.0.1:1234
    add-symbol-file ./build/kernelfull.o 0x0100000
    break _start
    break kernel_main
    c "continue"
    info registers
    frame
    n (next)
    cntrl c
    disas 0x0100000, 0x0100fff
    layout asm
    view memory location x/5i 0x7c00