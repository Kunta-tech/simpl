#!/bin/zsh

set -xe

mkdir -p bin/

# Compiling examples
function compile_example ()
{
	NAME="$1"
	gcc -Os -o bin/$NAME.exe examples/$NAME.c libspl.c
}

for i in $(ls ./examples)
	compile_example "${i%%.*}"
