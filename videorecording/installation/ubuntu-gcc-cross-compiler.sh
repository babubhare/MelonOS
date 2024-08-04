#!/bin/sh
sudo apt-get update --assume-yes 
#sudo apt-get upgrade --assume-yes

sudo apt-get install build-essential --assume-yes
sudo apt-get install git --assume-yes

cd $HOME
mkdir src
cd src

curl "https://ftp.gnu.org/gnu/gdb/gdb-14.2.tar.gz" --output gdb-14.2.tar.gz
tar -xvzf gdb-14.2.tar.gz
curl "https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz" --output binutils-2.42.tar.gz
tar -xvzf binutils-2.42.tar.gz
curl "https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz" --output gcc-13.2.0.tar.gz
tar -xvzf gcc-13.2.0.tar.gz

sudo apt-get install bison --assume-yes
sudo apt-get install flex --assume-yes
sudo apt-get install libgmp3-dev --assume-yes
sudo apt-get install libmpc-dev --assume-yes
sudo apt-get install libmpfr-dev --assume-yes
sudo apt-get install texinfo --assume-yes
sudo apt-get install libisl-dev --assume-yes

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
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
