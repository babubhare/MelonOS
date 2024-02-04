ASM_FILENAME_CHAR=char.asm
BOOT_FILENAME_CHAR=char.bin

char.asm: clean_char
	nasm -f bin ./$(ASM_FILENAME_CHAR) -o ./$(BOOT_FILENAME_CHAR)

run_char: char.asm
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_CHAR) -nographic 
 
clean_char: 
	rm -f ./$(BOOT_FILENAME_CHAR) 
 
