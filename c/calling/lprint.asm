global _lprint

section .text

_lprint:
    ; setup stack
    push rbp 		; save base pointer
    mov rbp, rsp 	; move current stack to base

    ; save registers
    push rsi
    push rdi

    ; main
    mov rax, 0x2000004
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 1
    syscall

    ; restore registers
    pop rsi
    pop rdi

    ; clean stack
    mov rbp, rsp
    pop rbp 

    ; return
    ret
