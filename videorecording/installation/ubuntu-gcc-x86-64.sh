#!/bin/sh

export PREFIX="$HOME/opt/cross86"
#export TARGET=i686-elf
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

cd $HOME/src
mkdir build-binutils
cd build-binutils
../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

../gdb-14.2/configure --target=$TARGET --prefix="$PREFIX" --disable-werror
make all-gdb
make install-gdb

cd $HOME/src
# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir build-gcc
cd build-gcc
../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
$HOME/opt/cross/bin/$TARGET-gcc --version
