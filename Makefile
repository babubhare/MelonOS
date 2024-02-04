ASM_FILENAME=char.asm 
BOOT_FILENAME=char.bin 

all: clean 
	nasm -f bin ./$(ASM_FILENAME) -o ./$(BOOT_FILENAME) 

clean: 
	rm -f ./$(BOOT_FILENAME) 
 
run: all 
    qemu-system-x86_64 -hda ./$(BOOT_FILENAME) -nographic  
