bits 16
org 0x7C00

jmp 0:boot_main

%include "io16.inc"

OutString: db "BIOS Has LBA Addressing: ", 0
Result: times 1 db 0				; crappy hack for bin files

boot_main:
	xor ax, ax
	mov ds, ax

	mov ah, 0x41
	mov dl, 0
	mov bx, 0x55AA
	int 0x13

	setnc bl
	mov [Result], bl

	mov si, OutString
	call Print16

	mov ah, 0x0E
	mov al, [Result]
	add al, '0'
	int 0x10

	call PrintNwl16

	cli
	hlt

times 510-($-$$) db 0
dw 0xAA55
