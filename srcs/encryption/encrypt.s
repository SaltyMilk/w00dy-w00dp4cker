
global _encrypt

;takes two strings as param (rdi = str to encrypt, rsi = key to encrypt)
_encrypt:
	xor rcx, rcx
	reset:
		xor rbx, rbx
	loop:
		mov r9b, byte[rsi + rbx]
		xor byte[rdi + rcx], r9b
		sub byte[rdi + rcx], cl
		inc rbx
		inc rcx
		cmp byte[rdi + rcx], 0
		je exit
		cmp byte[rsi + rbx], 0
		je reset
		jmp loop
exit: 
	retn