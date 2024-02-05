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

#make boot_bios33.asm
#make run_boot_bios33
#make clean_boot_bios33

ASM_FILENAME_BOOT_BIOS33=boot_bios33.asm
BOOT_FILENAME_BOOT_BIOS33=boot_bios33.bin

$(ASM_FILENAME_BOOT_BIOS33): clean_boot_bios33
	nasm -f bin ./$(ASM_FILENAME_BOOT_BIOS33) -o ./$(BOOT_FILENAME_BOOT_BIOS33)

run_boot_bios33: $(ASM_FILENAME_BOOT_BIOS33)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_BIOS33) -nographic 
 
clean_boot_bios33: 
	rm -f ./$(BOOT_FILENAME_BOOT_BIOS33) 


############################################################################################################

############################################################################################################

#make boot_interrupt.asm
#make run_boot_interrupt
#make clean_boot_interrupt

ASM_FILENAME_BOOT_INTERRUPT=boot_interrupt.asm
BOOT_FILENAME_BOOT_INTERRUPT=boot_interrupt.bin

$(ASM_FILENAME_BOOT_INTERRUPT): clean_boot_interrupt
	nasm -f bin ./$(ASM_FILENAME_BOOT_INTERRUPT) -o ./$(BOOT_FILENAME_BOOT_INTERRUPT)

run_boot_interrupt: $(ASM_FILENAME_BOOT_INTERRUPT)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_INTERRUPT) -nographic 
 
clean_boot_interrupt: 
	rm -f ./$(BOOT_FILENAME_BOOT_INTERRUPT) 


############################################################################################################