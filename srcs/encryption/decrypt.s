
global _decrypt

;takes two strings as param (rdi = str to decrypt, rsi = key to decrypt)
_decrypt:
	xor rcx, rcx
	reset:
		xor rbx, rbx
	loop:
		mov r9b, byte[rsi + rbx]
		xor byte[rdi + rcx], r9b
		add byte[rdi + rcx], cl
		inc rbx
		inc rcx
		cmp byte[rdi + rcx], 0
		je exit
		cmp byte[rsi + rbx], 0
		je reset
		jmp loop
exit: 
	retn