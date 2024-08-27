Commands:

./build.sh

1. Creates os.bin to bin directory
2. Debug symbols are available in build folder
3. Kernel.asm is built and linked as elf and then converted to pure binary which is not an elf
4. Kernel c code is compiled as elf and moved to object file with plain assembly code


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
    ALT + A ; X to exit fromqemu