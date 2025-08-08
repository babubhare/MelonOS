CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-builtin -nostdlib -Wall -Wextra
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

KERNEL_OBJECTS = kernel.o io.o devices.o interrupts.o memory.o pci.o isr.o
BOOT_BIN = boot.bin
KERNEL_BIN = kernel.bin
OS_IMG = simpleos.img

all: $(OS_IMG)

$(OS_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	@echo "Creating OS image..."
	dd if=/dev/zero of=$(OS_IMG) bs=512 count=2880 2>/dev/null
	dd if=$(BOOT_BIN) of=$(OS_IMG) bs=512 count=1 conv=notrunc 2>/dev/null
	dd if=$(KERNEL_BIN) of=$(OS_IMG) bs=512 seek=1 conv=notrunc 2>/dev/null
	@echo "OS image created: $(OS_IMG)"

$(BOOT_BIN): boot.asm
	@echo "Assembling bootloader..."
	$(AS) -f bin boot.asm -o $(BOOT_BIN)

$(KERNEL_BIN): $(KERNEL_OBJECTS)
	@echo "Linking kernel..."
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(KERNEL_OBJECTS)

kernel.o: kernel.c kernel.h
	@echo "Compiling kernel.c..."
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

io.o: io.c kernel.h
	@echo "Compiling io.c..."
	$(CC) $(CFLAGS) -c io.c -o io.o

devices.o: devices.c kernel.h pci.h
	@echo "Compiling devices.c..."
	$(CC) $(CFLAGS) -c devices.c -o devices.o

interrupts.o: interrupts.c kernel.h
	@echo "Compiling interrupts.c..."
	$(CC) $(CFLAGS) -c interrupts.c -o interrupts.o

memory.o: memory.c kernel.h
	@echo "Compiling memory.c..."
	$(CC) $(CFLAGS) -c memory.c -o memory.o

pci.o: pci.c pci.h kernel.h
	@echo "Compiling pci.c..."
	$(CC) $(CFLAGS) -c pci.c -o pci.o

isr.o: isr.asm
	@echo "Assembling interrupt handlers..."
	$(AS) $(ASFLAGS) isr.asm -o isr.o

run: $(OS_IMG)
	@echo "Starting QEMU..."
	qemu-system-i386 -drive format=raw,file=$(OS_IMG) -m 16M -nographic

run-debug: $(OS_IMG)
	@echo "Starting QEMU with debugging..."
	qemu-system-i386 -drive format=raw,file=$(OS_IMG) -m 16M -monitor stdio

clean:
	@echo "Cleaning build files..."
	rm -f *.o $(BOOT_BIN) $(KERNEL_BIN) $(OS_IMG)

install-deps:
	@echo "Install required dependencies:"
	@echo "Ubuntu/Debian: sudo apt-get install gcc-multilib nasm qemu-system-x86"
	@echo "Fedora: sudo dnf install gcc.i686 nasm qemu-system-x86"
	@echo "Arch: sudo pacman -S gcc-multilib nasm qemu"

.PHONY: all run run-debug clean install-deps