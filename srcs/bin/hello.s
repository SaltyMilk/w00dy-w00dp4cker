
section .text
    global _start
_start:
    mov     rax, 1
    mov     rdi, 1
	push	rdx
	push	0x0a2e2e2e
	mov		rdx, 0x59444f4f572e2e2e
	push	rdx
	lea		rsi, [rsp]
    mov     rdx, 12
    syscall
	pop rax
	pop rax
	pop rdx
    mov    rax, 60
    mov    rdi, 0
    syscall
	
