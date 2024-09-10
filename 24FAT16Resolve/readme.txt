Commands:

./build.sh

1. Creates os.bin to bin directory
2. Debug symbols are available in build folder
3. Kernel.asm is built and linked as elf and then converted to pure binary which is not an elf
4. Kernel c code is compiled as elf and moved to object file with plain assembly code
5. The characters cannot be viewed from the vm; need to run the qemu from parent computer to view the text
5. IRQ are set at https://wiki.osdev.org/Interrupts starting from 20
IRQ 20 => Timer
IRQ 21 => Keyboard


Run qemu up command 
    qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 -nographic
    qemu-system-x86_64 -hda ./bin/os.bin -nographic

    qemu-system-i386 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 -nographic

    qemu-system-i386 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 -nographic –drive file=./bin/os1.bin,format=raw,media=disk
Since no graphics is used in a vm; we cannot view the Interrupts messages. Follow the steps
1. Push to git
2. Pull to base computer 
3. qemu-system-x86_64 -hda ./bin/os.bin 

in vm GTX has issues with graphics

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
    view memory location x/5i 0x7c00
    ALT + A ; X to exit fromqemu
    p ($esp + (void *)&intValue1)
    p/x *above address
    info address variable
    set print pretty on

https://web.mit.edu/gnu/doc/html/gdb_8.html


How to view the data at the buf pointer in the kernel.c

1. get the esp (i r esp)
2. get the address of buf; &buf
3. add esp + buf
4. x/b *0x1ffde8 (to print the binary value)
5. x/512b *0x1ffdec


https://imhex.werwolv.net/
imhex to view the binary data
https://visualgdb.com/gdbreference/commands/x


1. user mkfs command to create a file system
sudo touch /mnt/usb.img
sudo fallocate -l 512M /mnt/usb.img
sudo mkfs.vfat usb.img
sudo mount -t vfat /mnt/usb.img /mnt/d
https://www.nixcraft.com/t/how-to-create-exfat-vfat-image-file-on-linux/4406/2

