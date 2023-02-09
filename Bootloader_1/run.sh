#!/bin/bash
clear
nasm -f bin -o bootloader.bin bootloader.asm &&
qemu-system-i386 -fda bootloader.bin

true
