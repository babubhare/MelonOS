#/bin/bash
export PREFIX="$HOME/x-tools/x86_64-unknown-linux-gnu"
export TARGET=x86_64-unknown-linux-gnu
export PATH="$PREFIX/bin:$PATH"


make all -B
