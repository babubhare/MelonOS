# SimpleOS - A Basic Operating System

SimpleOS is a minimal operating system written in C and x86 assembly language, designed for educational purposes and QEMU virtualization.

## Features

- **Custom Bootloader**: Written in x86 assembly, loads the kernel from disk
- **Kernel**: Written in C with assembly support code
- **Device Detection**: Enumerates PCI devices and basic hardware
- **Memory Management**: Simple heap allocation system
- **Interrupt Handling**: Basic IDT setup and interrupt service routines
- **VGA Text Mode**: Color text output with 80x25 resolution
- **QEMU Compatible**: Designed to run perfectly in QEMU

## Building and Running

### Prerequisites

Install the required development tools:

```bash
# Ubuntu/Debian
sudo apt-get install gcc-multilib nasm qemu-system-x86

# Fedora
sudo dnf install gcc.i686 nasm qemu-system-x86

# Arch Linux
sudo pacman -S gcc-multilib nasm qemu
```

### Building

```bash
# Build the OS
make

# Clean build files
make clean
```

### Running

```bash
# Run in QEMU
make run

# Run with debug monitor
make run-debug
```

## Project Structure

- `boot.asm` - Bootloader that loads the kernel
- `kernel.c` - Main kernel initialization and shell
- `kernel.h` - Main header file with common definitions
- `io.c` - Port I/O operations
- `devices.c` - Hardware device detection and enumeration
- `interrupts.c` - Interrupt descriptor table setup
- `memory.c` - Basic memory management system
- `pci.c` - PCI device enumeration
- `pci.h` - PCI-related definitions
- `isr.asm` - Interrupt service routines in assembly
- `linker.ld` - Linker script for kernel layout
- `Makefile` - Build system

## System Requirements

- x86 compatible processor
- At least 16MB RAM (QEMU default)
- VGA compatible display adapter

## Development Notes

This OS demonstrates:
- Bootloader development and kernel loading
- Protected mode transition
- Basic hardware abstraction
- Device enumeration via PCI
- Simple memory management
- Interrupt handling
- Cross-compilation for x86

The system is intentionally minimal but functional, serving as an excellent starting point for OS development learning.