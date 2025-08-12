# OrangeOS Makefile
# Educational Operating System Build Configuration

# Compiler and tools
CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld

CFLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc -Wno-unused-variable
# Compiler flags
#CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
#         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

#

# Assembler flags
ASFLAGS = -f bin

# Linker flags
LDFLAGS = -m elf_i386 -T linker.ld

# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
DRIVERS_DIR = drivers
LIB_DIR = lib
INCLUDE_DIR = ./include
BUILD_DIR = build

# Source files
BOOT_SRC = $(BOOT_DIR)/boot.asm
KERNEL_SOURCES = $(wildcard $(KERNEL_DIR)/*.c)
DRIVER_SOURCES = $(wildcard $(DRIVERS_DIR)/*.c)
LIB_SOURCES = $(wildcard $(LIB_DIR)/*.c)

# Object files
KERNEL_OBJECTS = $(KERNEL_SOURCES:$(KERNEL_DIR)/%.c=$(BUILD_DIR)/kernel_%.o)
DRIVER_OBJECTS = $(DRIVER_SOURCES:$(DRIVERS_DIR)/%.c=$(BUILD_DIR)/driver_%.o)
LIB_OBJECTS = $(LIB_SOURCES:$(LIB_DIR)/%.c=$(BUILD_DIR)/lib_%.o)

ALL_OBJECTS = $(KERNEL_OBJECTS) $(DRIVER_OBJECTS) $(LIB_OBJECTS)

# Output files
BOOTLOADER = $(BUILD_DIR)/boot.bin
KERNEL = $(BUILD_DIR)/kernel.bin
OS_IMAGE = orangeos.img

# Default target
all: $(OS_IMAGE)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build bootloader
$(BOOTLOADER): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Build kernel object files
$(BUILD_DIR)/kernel_%.o: $(KERNEL_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -std=gnu99 -c $< -o $@

# Build driver object files
$(BUILD_DIR)/driver_%.o: $(DRIVERS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -o $@

# Build library object files
$(BUILD_DIR)/lib_%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -o $@

# Link kernel
$(KERNEL): $(ALL_OBJECTS) linker.ld | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(ALL_OBJECTS) -o $@

# Create OS image
$(OS_IMAGE): $(BOOTLOADER) $(KERNEL)
	# Create 1.44MB floppy image
	dd if=/dev/zero of=$@ bs=1024 count=1440
	# Write bootloader to first sector
	dd if=$(BOOTLOADER) of=$@ bs=512 count=1 conv=notrunc
	# Write kernel starting from sector 2
	dd if=$(KERNEL) of=$@ bs=512 seek=1 conv=notrunc

# Run in QEMU
run: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE) -boot a

# Run in QEMU with debugging
debug: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE) -boot a -s -S

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OS_IMAGE)

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install gcc nasm qemu-system-x86 build-essential

# Create linker script if it doesn't exist
linker.ld:
	@echo "Creating linker script..."
	@echo "ENTRY(kernel_main)" > linker.ld
	@echo "SECTIONS {" >> linker.ld
	@echo "    . = 0x1000;" >> linker.ld
	@echo "    .text : { *(.text) }" >> linker.ld
	@echo "    .data : { *(.data) }" >> linker.ld
	@echo "    .bss : { *(.bss) }" >> linker.ld
	@echo "}" >> linker.ld

# Help target
help:
	@echo "OrangeOS Build System"
	@echo "Available targets:"
	@echo "  all          - Build complete OS image"
	@echo "  run          - Build and run in QEMU"
	@echo "  debug        - Build and run in QEMU with debugging"
	@echo "  clean        - Remove build files"
	@echo "  install-deps - Install required dependencies"
	@echo "  help         - Show this help message"

.PHONY: all run debug clean install-deps help
