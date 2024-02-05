nope:

############################################################################################################

ASM_FILENAME_BOOT_CHAR=boot_char.asm
BOOT_FILENAME_BOOT_CHAR=boot_char.bin

$(ASM_FILENAME_BOOT_CHAR): clean_boot_char
	nasm -f bin ./$(ASM_FILENAME_BOOT_CHAR) -o ./$(BOOT_FILENAME_BOOT_CHAR)

run_boot_char: $(ASM_FILENAME_BOOT_CHAR)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_CHAR) -nographic 
 
clean_boot_char: 
	rm -f ./$(BOOT_FILENAME_BOOT_CHAR) 


############################################################################################################

ASM_FILENAME_BOOT_STRING=boot_string.asm
BOOT_FILENAME_BOOT_STRING=boot_string.bin

$(ASM_FILENAME_BOOT_STRING): clean_boot_string
	nasm -f bin ./$(ASM_FILENAME_BOOT_STRING) -o ./$(BOOT_FILENAME_BOOT_STRING)

run_boot_string: $(ASM_FILENAME_BOOT_STRING)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_STRING) -nographic 
 
clean_boot_string: 
	rm -f ./$(BOOT_FILENAME_BOOT_STRING) 

############################################################################################################

#make boot_segment.asm
#make clean_boot_segment

ASM_FILENAME_BOOT_SEGMENT=boot_segment.asm
BOOT_FILENAME_BOOT_SEGMENT=boot_segment.bin

$(ASM_FILENAME_BOOT_SEGMENT): clean_boot_segment
	nasm -f bin ./$(ASM_FILENAME_BOOT_SEGMENT) -o ./$(BOOT_FILENAME_BOOT_SEGMENT)

run_boot_segment: $(ASM_FILENAME_BOOT_SEGMENT)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_SEGMENT) -nographic 
 
clean_boot_segment: 
	rm -f ./$(BOOT_FILENAME_BOOT_SEGMENT) 


############################################################################################################