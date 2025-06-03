
############################################################################################################

ASM_FILENAME_BOOT_PROTECTED=boot_protected.asm
BOOT_FILENAME_BOOT_PROTECTED=boot_protected.bin

all: clean_boot_protected
	nasm -f bin ./$(ASM_FILENAME_BOOT_PROTECTED) -o ./$(BOOT_FILENAME_BOOT_PROTECTED)

run_boot_protected: $(ASM_FILENAME_BOOT_PROTECTED)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_PROTECTED) -nographic 
 
clean_boot_protected: 
	rm -f ./$(BOOT_FILENAME_BOOT_PROTECTED) 

run_boot_protected_mac: $(ASM_FILENAME_BOOT_PROTECTED)
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_PROTECTED) 

windows:
	qemu-system-x86_64 -hda ./$(BOOT_FILENAME_BOOT_PROTECTED) -S -gdb tcp:127.0.0.1:1234
	## qemu-system-x86_64 -hda ./boot_protected.bin -S -gdb tcp:127.0.0.1:1234
	# gdb
	# target remote tcp:127.0.0.1:1234
############################################################################################################
