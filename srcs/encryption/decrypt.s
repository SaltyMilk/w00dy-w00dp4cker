
global _decryptSelmelc

;takes two strings as param (rdi = str to decrypt, rsi = key to decrypt, rdx = str length)
_decryptSelmelc:
;	mov rdx, 0x4242424242424242
;	lea rdi, [rel $-0x4847464544434241]
;	lea rsi, [rel $+65]
	xor rcx, rcx
	reset:
		xor rbx, rbx
	loop:
		mov r9b, byte[rsi + rbx]
		add byte[rdi + rcx], cl
		xor byte[rdi + rcx], r9b
		inc rbx
		inc rcx
		cmp rcx, rdx
		je exit
		cmp byte[rsi + rbx], 0
		je reset
		jmp loop
exit: 
	retn
