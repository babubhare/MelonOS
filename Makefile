first:
	nasm -f bin ./first/first.asm -o ./bin/boot.bin

run:
	qemu-system-x86_64 -hda ./bin/boot.bin -nographic 