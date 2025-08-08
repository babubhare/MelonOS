#include "pci.h"

void pci_config_write(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset, uint32_t data) {
    uint32_t address = (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
    
    outl(PCI_CONFIG_ADDRESS, address);
    outl(PCI_CONFIG_DATA, data);
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