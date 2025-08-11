#include "../include/kernel.h"

// CPU detection using CPUID instruction
void detect_cpu(void) {
    uint32_t eax, ebx, ecx, edx;
    char vendor[13];
    
    // Get vendor string
    asm volatile("cpuid"
                : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                : "a"(0));
    
    // Extract vendor string
    *((uint32_t*)vendor) = ebx;
    *((uint32_t*)(vendor + 4)) = edx;
    *((uint32_t*)(vendor + 8)) = ecx;
    vendor[12] = '\0';
    
    terminal_writestring("CPU: ");
    terminal_writestring(vendor);
    terminal_writestring(" compatible processor\n");
    
    // Get CPU features
    asm volatile("cpuid"
                : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                : "a"(1));
    
    terminal_writestring("Features: ");
    if (edx & (1 << 0)) terminal_writestring("FPU ");
    if (edx & (1 << 4)) terminal_writestring("TSC ");
    if (edx & (1 << 23)) terminal_writestring("MMX ");
    if (edx & (1 << 25)) terminal_writestring("SSE ");
    terminal_writestring("\n");
}

// Simple PCI device detection
void detect_pci_devices(void) {
    terminal_writestring("PCI Devices:\n");
    
    for (uint16_t bus = 0; bus < 256; bus++) {
        for (uint8_t device = 0; device < 32; device++) {
            for (uint8_t function = 0; function < 8; function++) {
                uint32_t address = (bus << 16) | (device << 11) | (function << 8);
                
                // Read vendor ID
                outw(0xCF8, 0x8000 | address);
                uint16_t vendor = inw(0xCFC);
                
                if (vendor != 0xFFFF) {
                    // Read device ID
                    outw(0xCF8, 0x8000 | address | 2);
                    uint16_t device_id = inw(0xCFC);
                    
                    terminal_writestring("  Device found: ");
                    // Simple hex output (simplified)
                    terminal_writestring("Vendor/Device ID found\n");
                    
                    // Only check function 0 for single-function devices
                    if (function == 0) {
                        outw(0xCF8, 0x8000 | address | 0x0E);
                        uint8_t header_type = inb(0xCFC + 2);
                        if ((header_type & 0x80) == 0) break;
                    }
                }
            }
        }
    }
}

// Floppy drive detection
void detect_floppy(void) {
    // Read CMOS to check for floppy drives
    outb(0x70, 0x10);
    uint8_t drives = inb(0x71);
    
    terminal_writestring("Floppy drives: ");
    
    uint8_t drive_a = drives >> 4;
    uint8_t drive_b = drives & 0x0F;
    
    if (drive_a == 0 && drive_b == 0) {
        terminal_writestring("None detected\n");
    } else {
        if (drive_a != 0) {
            terminal_writestring("Drive A: ");
            switch (drive_a) {
                case 1: terminal_writestring("360KB 5.25\" "); break;
                case 2: terminal_writestring("1.2MB 5.25\" "); break;
                case 3: terminal_writestring("720KB 3.5\" "); break;
                case 4: terminal_writestring("1.44MB 3.5\" "); break;
                case 5: terminal_writestring("2.88MB 3.5\" "); break;
                default: terminal_writestring("Unknown "); break;
            }
        }
        if (drive_b != 0) {
            terminal_writestring("Drive B: ");
            switch (drive_b) {
                case 1: terminal_writestring("360KB 5.25\" "); break;
                case 2: terminal_writestring("1.2MB 5.25\" "); break;
                case 3: terminal_writestring("720KB 3.5\" "); break;
                case 4: terminal_writestring("1.44MB 3.5\" "); break;
                case 5: terminal_writestring("2.88MB 3.5\" "); break;
                default: terminal_writestring("Unknown "); break;
            }
        }
        terminal_writestring("\n");
    }
}