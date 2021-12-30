
global _decryptSelmelc

;takes two strings as param (rdi = str to decrypt, rsi = key to decrypt, rdx = str length)
_decryptSelmelc:
	xor edx, edx
	mov edx, 0x44434241
	call $ + 5
	pop eax
	add eax, 0x44434241
	mov esi, eax
	sub eax, 0x44434241
	add eax, 0x45444342
	mov edi, eax
	lea edi, [rel $-0x48474645]
	lea esi, [rel $+51]
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
