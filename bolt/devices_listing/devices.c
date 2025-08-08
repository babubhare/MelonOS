#include "kernel.h"

// PCI device detection
void scan_pci_devices(void) {
    print_colored("PCI Devices:\n", COLOR_LIGHT_CYAN);
    
    for (int bus = 0; bus < 256; bus++) {
        for (int device = 0; device < 32; device++) {


            uint32_t vendor_id = pci_config_read(bus, device, 0, 0);
            
            if ((vendor_id & 0xFFFF) != 0xFFFF) {
                uint32_t device_id = (vendor_id >> 16) & 0xFFFF;
                vendor_id &= 0xFFFF;
                
                print_string("  Bus ");
                print_hex(bus);
                print_string(" Device ");
                print_hex(device);
                print_string(" - Vendor: ");
                print_hex(vendor_id);
                print_string(" Device: ");
                print_hex(device_id);
                print_string("\n");
            }
        }
    }
}

void detect_basic_hardware(void) {
    print_colored("Basic Hardware:\n", COLOR_LIGHT_CYAN);
    
    // Detect CPU
    print_string("  CPU: x86 Compatible Processor\n");
    
    // Detect memory (simplified)
    print_string("  RAM: Available (amount detection not implemented)\n");
    
    // Detect video adapter
    print_string("  Video: VGA Compatible Display Adapter\n");
    
    // Detect keyboard
    print_string("  Keyboard: PS/2 Compatible\n");
    
    // Check for floppy drive
    uint8_t floppy_status = inb(0x3F2);
    if (floppy_status & 0x04) {
        print_string("  Floppy: Drive detected\n");
    }
    
    // Check for serial ports
    outb(0x3F8 + 1, 0x00);    // Disable interrupts
    outb(0x3F8 + 3, 0x80);    // Enable DLAB
    outb(0x3F8 + 0, 0x03);    // Set divisor to 3 (38400 baud)
    outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x03);    // 8 bits, no parity, one stop bit
    
    if (inb(0x3F8 + 5) != 0xFF) {
        print_string("  Serial: COM1 port detected\n");
    }
}

void detect_devices(void) {
    detect_basic_hardware();
    print_string("\n");
    scan_pci_devices();
}

// PCI configuration space access
// uint32_t pci_config_read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
//     uint32_t address = (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
    
//     outl(0xCF8, address);
//     return inl(0xCFC);
// }