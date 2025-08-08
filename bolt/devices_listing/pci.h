#ifndef PCI_H
#define PCI_H

#include "kernel.h"

// PCI Configuration Space
#define PCI_CONFIG_ADDRESS  0xCF8
#define PCI_CONFIG_DATA     0xCFC

// PCI device classes
#define PCI_CLASS_UNCLASSIFIED      0x00
#define PCI_CLASS_MASS_STORAGE      0x01
#define PCI_CLASS_NETWORK           0x02
#define PCI_CLASS_DISPLAY           0x03
#define PCI_CLASS_MULTIMEDIA        0x04
#define PCI_CLASS_MEMORY            0x05
#define PCI_CLASS_BRIDGE            0x06

// Function declarations
uint32_t pci_config_read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset);
void pci_config_write(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset, uint32_t data);
const char* get_pci_class_name(uint8_t class_code);
const char* get_vendor_name(uint16_t vendor_id);

#endif