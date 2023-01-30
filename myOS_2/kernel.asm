bits 32
section .text
	align 4
	dd 0x1badb002
	dd 0x00
	dd - (0x1badb002+0x00)

	global main
	extern kmain
main:
	cli
	call kmain
	hlt