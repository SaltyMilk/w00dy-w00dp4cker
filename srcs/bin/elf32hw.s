global _start

_start:
mov    eax,0x4
mov    ebx,0x1
push   edx
push   0xa2e2e2e
push   0x59444f4f
push   0x572e2e2e
lea    ecx,[esp]
mov    edx,0xc
int 0x80
pop eax
pop eax
pop eax 
pop edx
xor ebx, ebx
mov eax, 0x1
int 0x80
