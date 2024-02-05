nope:

############################################################################################################

ASM_FILENAME_BOOT_PROTECTED=boot_protected.asm
BOOT_FILENAME_BOOT_PROTECTED=boot_protected.bin

$(ASM_FILENAME_BOOT_PROTECTED): clean_boot_protected
	nasm -f bin ./$(ASM_FILENAME_BOOT_PROTECTED) -o ./$(BOOT_FILENAME_BOOT_PROTECTED)

run_boot_protected: $(ASM_FILENAME_BOOT_PROTECTED)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_PROTECTED) -nographic 
 
clean_boot_protected: 
	rm -f ./$(BOOT_FILENAME_BOOT_PROTECTED) 

run_boot_protected_mac: $(ASM_FILENAME_BOOT_PROTECTED)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_PROTECTED) 

############################################################################################################
