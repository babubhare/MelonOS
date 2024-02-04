first:
	nasm -f bin ./1/first.asm -o ./bin/boot.bin

run:
	qemu-system-x86_64 -hda ./bin/boot.bin -nographic 