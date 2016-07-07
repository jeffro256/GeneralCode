global _sum

SECTION .text align=16

_sum:
    mov eax, edi
    add eax, esi
    ret
