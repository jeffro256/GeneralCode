; A minimal BIOS "Hello, World!" Bootloader

bits 16
org 0x7C00

boot_main:
	xor ax, ax
	mov ds, ax
	cli
	mov ss, ax
	mov bp, 0xF000
	mov sp, bp
	sti

	mov si, msg
	call Print

	cli
	hlt

Print:
	lodsb
	or al, al
	jz .end
	mov ah, 0x0E
	int 0x10
	jmp Print
.end:
	ret

msg db "Hello, World!", 13, 10, 0

times 510-($-$$) db 0
dw 0xAA55
