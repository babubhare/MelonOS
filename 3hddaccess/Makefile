all:
	nasm -f bin ./hdd.asm -o ./hdd.bin
	dd if=message.txt >> ./hdd.bin
	dd if=/dev/zero bs=512 count=1 >> ./hdd.bin