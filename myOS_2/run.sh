#!/bin/bash
clear &&
nasm -f elf32 -o kernelAsm.o kernel.asm &&
gcc -m32 -lm -ffreestanding -c kernel.c -o kernelC.o &&
#ld -m elf_i386 -T linker.ld -o kernel.bin kernelAsm.o kernelC.o &&
gcc -m32 -Xlinker linker.ld -o kernel.bin kernelAsm.o kernelC.o &&
qemu-system-i386 -kernel kernel.bin