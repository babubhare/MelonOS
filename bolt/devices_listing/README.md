# OrangeOS - Educational Operating System

OrangeOS is a minimalist educational operating system designed to demonstrate core OS concepts. It's written in C and x86 assembly, targeting the i386 architecture and running in QEMU.

## Features

### Core Components
- **Bootloader**: 512-byte boot sector with protected mode transition
- **Kernel**: Basic kernel with VGA text mode display
- **Memory Management**: Simple heap allocator with malloc/free
- **Hardware Detection**: CPU, memory, PCI devices, and floppy drives
- **Shell**: Interactive command-line interface
- **Timer System**: PIT-based timer with callback support
- **Device Management**: Basic device registration and management

### Hardware Support
- VGA text mode display (80x25)
- PS/2 keyboard input
- PIT timer (Programmable Interval Timer)
- RTC (Real-Time Clock)
- Basic PCI device enumeration
- Floppy drive detection

### Shell Commands
- `help` - Show available commands
- `clear` - Clear the screen
- `time` - Display current system time
- `devices` - List connected devices
- `memory` - Show memory information
- `cpu` - Display CPU information
- `reboot` - Restart the system
- `shutdown` - Halt the system

## Building and Running

### Prerequisites

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install gcc nasm qemu-system-x86 build-essential
```

#### Arch Linux
```bash
sudo pacman -S gcc nasm qemu-system-x86 make
```

#### macOS (with Homebrew)
```bash
brew install gcc nasm qemu
```

### Building
```bash
# Build the complete OS image
make

# Or use the convenience script
./run_qemu.sh
```

### Running
```bash
# Run in QEMU
make run

# Run with debugging support
make debug

# Use the launch script
chmod +x run_qemu.sh
./run_qemu.sh
```

## Project Structure

```
orangeos/
├── boot/
│   └── boot.asm          # Bootloader assembly code
├── kernel/
│   ├── kernel.c          # Main kernel and terminal
│   ├── memory.c          # Memory management
│   ├── hardware.c        # Hardware detection
│   ├── shell.c           # Interactive shell
│   └── timer.c           # Timer system
├── drivers/
│   └── device.c          # Device management
├── lib/
│   ├── string.c          # String utilities
│   └── io.c              # I/O port operations
├── include/
│   └── kernel.h          # Main header file
├── Makefile              # Build configuration
├── linker.ld             # Linker script
├── run_qemu.sh           # QEMU launch script
└── README.md             # This file
```

## Technical Details

### Boot Process
1. BIOS loads bootloader from first sector
2. Bootloader enables A20 line and sets up GDT
3. Transitions from 16-bit real mode to 32-bit protected mode
4. Loads kernel from disk sectors 2-11
5. Jumps to kernel entry point

### Memory Layout
- `0x0000-0x7BFF`: Real mode stack and data
- `0x7C00-0x7DFF`: Bootloader (512 bytes)
- `0x1000-0xFFFF`: Kernel code and data
- `0x100000+`: Kernel heap (1MB)

### Compilation Process
1. Assemble bootloader with NASM
2. Compile C sources with GCC (32-bit, freestanding)
3. Link kernel objects with custom linker script
4. Create floppy disk image with bootloader and kernel

## Educational Value

This OS demonstrates:
- **Low-level Programming**: Assembly language and hardware interaction
- **Memory Management**: Basic heap allocation algorithms
- **Hardware Abstraction**: Device drivers and hardware detection
- **System Calls**: Basic kernel services
- **Boot Process**: From BIOS to kernel execution
- **Protected Mode**: x86 segmentation and privilege levels

## Limitations

As an educational project, OrangeOS has several limitations:
- No multitasking or process management
- No file system support
- Limited hardware support
- No network capabilities
- Simplified memory management
- No security features

## Testing

### Basic Functionality Test
1. Boot the system
2. Verify hardware detection output
3. Test shell commands:
   ```
   orange> help
   orange> cpu
   orange> memory
   orange> devices
   orange> time
   orange> clear
   ```

### Memory Test
1. The system should boot without memory errors
2. Shell should respond to commands
3. No crashes during normal operation

### Hardware Detection Test
1. CPU information should display
2. Memory detection should show 16MB
3. Basic devices should be listed

## Troubleshooting

### Build Issues
- Ensure all dependencies are installed
- Check that you're using a 32-bit capable GCC
- Verify NASM is in your PATH

### QEMU Issues
- Make sure QEMU system emulation is installed
- Try different QEMU versions if display issues occur
- Use `-nographic` flag for text-only mode

### Boot Issues
- Verify the disk image is exactly 1.44MB
- Check that the boot signature (0xAA55) is present
- Ensure the bootloader fits in 512 bytes

## Contributing

This is an educational project. Contributions that improve clarity, add comments, or fix bugs are welcome. Please maintain the educational focus and avoid adding complex features that obscure the learning objectives.

## License

This project is released into the public domain for educational use.

## References

- Intel 80386 Programmer's Reference Manual
- OSDev Wiki (https://wiki.osdev.org/)
- "Operating Systems: Design and Implementation" by Tanenbaum
- "Operating System Concepts" by Silberschatz, Galvin, and Gagne