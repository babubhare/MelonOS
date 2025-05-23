#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10


#define PEACHOS_TOTAL_INTERRUPTS 512

// 100MB heap size
#define PEACHOS_HEAP_SIZE_BYTES 104857600
#define PEACHOS_HEAP_BLOCK_SIZE 4096
#define PEACHOS_HEAP_ADDRESS 0x01000000 
#define PEACHOS_HEAP_TABLE_ADDRESS 0x00007E00

#define PEACHOS_SECTOR_SIZE 512

#define PEACHOS_MAX_FILESYSTEMS 12
#define PEACHOS_MAX_FILE_DESCRIPTORS 512

#define PEACHOS_MAX_PATH 108

#define PEACHOS_TOTAL_GDT_SEGMENTS 3
#endif