; Disassembly of file: call_test.o
; Thu Oct  1 08:53:13 2015
; Mode: 64 bits
; Syntax: YASM/NASM
; Instruction set: 8086, x64

default rel

global _main

extern _sum                                             ; near


SECTION ._TEXT.__text align=16 execute                  ; section number 1, code

_main:  ; Function begin
        push    rbp                                     ; 0000 _ 55
        mov     rbp, rsp                                ; 0001 _ 48: 89. E5
        sub     rsp, 16                                 ; 0004 _ 48: 83. EC, 10
        mov     edi, 1                                  ; 0008 _ BF, 00000001
        mov     esi, 2                                  ; 000D _ BE, 00000002
        mov     dword [rbp-4H], 0                       ; 0012 _ C7. 45, FC, 00000000
        call    _sum                                    ; 0019 _ E8, 00000000(rel)
        add     rsp, 16                                 ; 001E _ 48: 83. C4, 10
        pop     rbp                                     ; 0022 _ 5D
        ret                                             ; 0023 _ C3
; _main End of function


