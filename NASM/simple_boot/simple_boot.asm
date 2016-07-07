bits 16
org 0x7C00

boot_main:
	mov ah, 0x0E
	mov al, 'A'
	int 0x10
	cli
	hlt

times 510-($-$$) db 0
dw 0xAA55
