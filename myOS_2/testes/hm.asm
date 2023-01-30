section .text
	global _start
_start:
	xor eax,4
	
	mov eax,1
	mov ebx,0
	int 0x80
