#include "pci.h"

void pci_config_write(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset, uint32_t data) {
    uint32_t address = (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
    
    outl(PCI_CONFIG_ADDRESS, address);
    outl(PCI_CONFIG_DATA, data);
}

uint32_t pci_config_read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    uint32_t address;
    uint32_t data;

    // Construct the configuration address
    address = (uint32_t)((bus << 16) |
                         (device << 11) |
                         (function << 8) |
                         (offset & 0xFC) | // Ensure offset is DWORD-aligned
                         0x80000000);     // Enable bit

    // Write the address to the CONFIG_ADDRESS port
    outl(PCI_CONFIG_ADDRESS, address);

    // Read the data from the CONFIG_DATA port
    data = inl(PCI_CONFIG_DATA);

    // Extract the specific byte/word if offset is not 32-bit aligned
    // This part depends on whether the caller expects a byte, word, or dword
    // For a full 32-bit read, no further adjustment is needed here if offset is already aligned.
    // If reading a byte or word, bit shifting and masking would be required.
    // This example assumes a 32-bit read and the offset is already aligned to a 32-bit boundary.
    // For example, if offset is 0x00, 0x04, 0x08, etc.

    return data;
}

const char* get_pci_class_name(uint8_t class_code) {
    switch (class_code) {
        case PCI_CLASS_UNCLASSIFIED:    return "Unclassified";
        case PCI_CLASS_MASS_STORAGE:    return "Mass Storage";
        case PCI_CLASS_NETWORK:         return "Network";
        case PCI_CLASS_DISPLAY:         return "Display";
        case PCI_CLASS_MULTIMEDIA:      return "Multimedia";
        case PCI_CLASS_MEMORY:          return "Memory";
        case PCI_CLASS_BRIDGE:          return "Bridge";
        default:                        return "Unknown";
    }
}

const char* get_vendor_name(uint16_t vendor_id) {
    switch (vendor_id) {
        case 0x8086: return "Intel";
        case 0x1022: return "AMD";
        case 0x10DE: return "NVIDIA";
        case 0x1002: return "ATI/AMD";
        case 0x15AD: return "VMware";
        case 0x1234: return "QEMU";
        case 0x1AF4: return "Red Hat (VirtIO)";
        default:     return "Unknown";
    }
}