; Disassembly of file: sum.o
; Thu Oct  1 08:53:13 2015
; Mode: 64 bits
; Syntax: YASM/NASM
; Instruction set: 8086, x64

default rel

global _sum


SECTION ._TEXT.__text align=16 execute                  ; section number 1, code

_sum:   ; Function begin
        push    rbp                                     ; 0000 _ 55
        mov     rbp, rsp                                ; 0001 _ 48: 89. E5
        mov     dword [rbp-4H], edi                     ; 0004 _ 89. 7D, FC
        mov     dword [rbp-8H], esi                     ; 0007 _ 89. 75, F8
        mov     esi, dword [rbp-4H]                     ; 000A _ 8B. 75, FC
        add     esi, dword [rbp-8H]                     ; 000D _ 03. 75, F8
        mov     eax, esi                                ; 0010 _ 89. F0
        pop     rbp                                     ; 0012 _ 5D
        ret                                             ; 0013 _ C3
; _sum End of function


