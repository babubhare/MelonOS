qemu-system-x86_64 -hda ./bin/os.bin

target remote | qemu-system-x86_64 -hda ./bin/os.bin -S -gdb stdio -nographic 

target remote | qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 stdio -s

qemu-system-x86_64.exe -hda ./bin/os.bin -S


For Windows system

In one terminal of mingw:
qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234

In another terminal of mingw:
gdb
target remote tcp:127.0.0.1:1234