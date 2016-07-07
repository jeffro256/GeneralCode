bits 16
org 0

dw num_secs
jmp stage2

%include "io16.inc"

; VIDEO INFO (for mode 13H)
VID_ADDR    equ 0xA0000
VID_SEG     equ VID_ADDR / 16
VID_OFF     equ VID_ADDR % 16
VID_WIDTH   equ 320
VID_HEIGHT  equ 200
VID_SIZE    equ VID_WIDTH * VID_HEIGHT

stage2:
    xor ah, ah
    mov al, 0x13
    int 0x10
    
    mov ecx, VID_SIZE
draw_loop:
    xor dx, dx
    mov eax, ecx
    mov ebx, VID_WIDTH
    div ebx
    add eax, edx
    mov bx, VID_SEG
    mov es, bx
    lea edi, [VID_OFF + VID_SIZE]
    sub edi, ecx
    mov [es:edi], al
    loop draw_loop

    cli
    hlt
    
align 512, db 0
num_secs equ ($-$$)/512