qemu-system-x86_64 -hda ./bin/os.bin

target remote | qemu-system-x86_64 -hda ./bin/os.bin -S -gdb stdio -nographic 

target remote | qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234 stdio -s

qemu-system-x86_64.exe -hda ./bin/os.bin -S


git reset --hard <commitID> 

For Windows system

In one terminal of mingw:
qemu-system-x86_64 -hda ./bin/os.bin -S -gdb tcp:127.0.0.1:1234


**************************************************************************************
In another terminal of mingw:
gdb
target remote tcp:127.0.0.1:1234
add-symbol-file ./build/kernelfull.o 0x0100000
https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_toc.html#TOC56 

gdb:

break _start
info registers
frame
c
n
cntrl c
disas 0x0100000, 0x0100fff
layout asm
**************************************************************************************

**************************************************************************************
cross compiler codebase

https://ftp.gnu.org/gnu/gdb/
https://ftp.gnu.org/gnu/binutils/

curl "https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz" --output binutils-2.42.tar.gz
curl "https://ftp.gnu.org/gnu/gdb/gdb-14.2.tar.gz" --output gdb-14.2.tar.gz

git clone git://gcc.gnu.org/git/gcc.git

Extract
tar -xvzf [archive name]
tar -xvzf binutils-2.42.tar.gz
tar -xvzf gdb-14.2.tar.gz

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

**************************************************************************************