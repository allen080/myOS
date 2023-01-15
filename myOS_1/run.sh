#!/bin/bash
clear &&
nasm -f elf32 -o kernelAsm.o kernel.asm &&
gcc -m32 -c kernel.c -o kernelC.o &&
ld -m elf_i386 -T linker.ld -o OS.bin kernelAsm.o kernelC.o &&
qemu-system-i386 -kernel OS.bin