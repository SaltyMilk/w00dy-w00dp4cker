
global _encryptSelmelc

;takes two strings as param (rdi = str to encrypt, rsi = key to encrypt, rdx = length of str)
_encryptSelmelc:
	xor rcx, rcx
	reset:
		xor rbx, rbx
	loop:
		mov r9b, byte[rsi + rbx]
		xor byte[rdi + rcx], r9b
		sub byte[rdi + rcx], cl
		inc rbx
		inc rcx
		cmp rcx, rdx
		je exit
		cmp byte[rsi + rbx], 0
		je reset
		jmp loop
exit:
	retn
