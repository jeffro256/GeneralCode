BITS 16
ORG 0x7C00

%define VIDSEG		0xA000
%define VIDWIDTH	320
%define VIDHEIGHT	200

main:
mov ah, 0
mov al, 13h
int 10h
mov ax, VIDSEG
mov es, ax
mov cx, VIDWIDTH * VIDHEIGHT
xor ax, ax
.draw_loop:
mov di, ax
mov [es:di], al
inc ax
loop .draw_loop
cli
end:
hlt
jmp end

; Bootloader footprint
times 510-($-$$) db 0
dw 0xAA55
