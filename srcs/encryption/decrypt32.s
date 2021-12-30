
global _decryptSelmelc

;takes two strings as param (rdi = str to decrypt, rsi = key to decrypt, rdx = str length)
_decryptSelmelc:
	xor edx, edx
	mov edx, 0x44434241
	lea edi, [rel $-0x48474645]
	lea esi, cs:[+51]
	xor ecx, ecx
	reset:
		xor ebx, ebx
	loop:
		mov al, byte[esi + ebx]
		add byte[edi + ecx], cl
		xor byte[edi + ecx], al
		inc ebx
		inc ecx
		cmp ecx, edx
		je exit
		cmp byte[esi + ebx], 0
		je reset
		jmp loop
exit: 
	retn
