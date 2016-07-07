%ifndef __IO16_ASM__
%define __IO16_ASM__

jmp IO16SectionEnd      ; We don't want to execute by inclusion

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Params:
; [ds:si] pointer to string

Print16:
    lodsb
    or al, al
    jz .end
    mov ah, 0x0E        ; BIOS Function
    int 0x10            ; BIOS Video Interrupt
    jmp Print16
.end:
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Params:
; [ds:si] pointer to string

Puts16:
    call Print16
PrintNwl16:
    mov ah, 0x0E        ; BIOS Function
    mov al, 0x0D        ; Carriage Return
    int 0x10            ; BIOS Video Interrupt
    mov ah, 0x0E        ; BIOS Function
    mov al, 0x0A        ; Newline
    int 0x10            ; BIOS Video Interrupt
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Params:
; None

DumpAX:
    mov ecx, 16
.loop:
    mov bx, ax
    and bx, 0x8000
    setnz bl
    mov dx, ax
    mov al, bl
    add al, '0'
    mov ah, 0x0E
    int 0x10
    mov ax, dx
    shl ax, 1
    loop .loop

    call PrintNwl16
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

struc SectorReadParam
    .bufoff:    resw 1
    .bufseg:    resw 1
    .numsecs:   resb 1
    .track:     resb 1
    .sector:    resb 1
    .head:      resb 1
    .drive:     resb 1
endstruc

; Params:
; [ds:si] - Pointer to a SectorReadParam struct (see above)

ReadSectors:
    xor ah, ah                                  ; Function number
    mov dl, [ds:si + SectorReadParam.drive]     ; Drive number
    int 0x13                                    ; Reset floppy
    jc ReadSectors                             ; If failed, try again

.actual_reading:
    mov ax, [ds:si + SectorReadParam.bufseg]
    mov es, ax
    mov bx, [ds:si + SectorReadParam.bufoff]
    mov ah, 2                                   ; BIOS function
    mov al, [ds:si + SectorReadParam.numsecs]
    mov ch, [ds:si + SectorReadParam.track]
    mov cl, [ds:si + SectorReadParam.sector]
    mov dh, [ds:si + SectorReadParam.head]
    mov dl, [ds:si + SectorReadParam.drive] 
    int 0x13                                    ; Read the sectors!
    jc .actual_reading                        ; If failed, try again

    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

IO16SectionEnd:

%endif
