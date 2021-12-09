    global _start   ; Make label available to linker 

_start:             ; Standard ld entry point    
    jmp callback    ; Jump to the end to get our current address

dowork: 
    pop     rsi     ;
    mov rax,1       ; System call number for write
    mov     rdi,1   ; 1 for stdout
    mov     rdx,12  ; length of Hello World
    syscall         ; Switch to the kernel mode

    mov   rax,231   ; exit_group(0)
    xor rdi,rdi     ;
    syscall         ;

callback:
    call dowork     ; Pushes the address of "Hello World" onto the stack
    db 'Hello World',0xA  ; The string we want to print
