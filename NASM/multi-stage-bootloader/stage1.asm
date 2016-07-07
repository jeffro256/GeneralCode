; This is stage 1 of a multi-stage bootloader

bits 16
org 0x7C00

jmp 0:boot_main

%include "io16.inc"

boot_main:
    ; setup the new stack
    cli
    mov ax, 0x100
    mov ss, ax
    mov bp, 0x4000
    mov sp, bp
    sti 

    ; Setup data segment
    xor ax, ax
    mov ds, ax

    ; Save which drive we booted from
    mov [Stage2Read + SectorReadParam.drive], dl
    
    ; Initialize Stage2FarPtr
    mov ax, [Stage2Read + SectorReadParam.bufseg]
    mov [Stage2FarPtr.segment], ax
    mov ax, [Stage2Read + SectorReadParam.bufoff]
    mov [Stage2FarPtr.offset], ax
    add [Stage2FarPtr.offset], word 2

    ; Home-made BIOS wrapper to read sectors into memory
    mov si, Stage2Read
    call ReadSectors

    ; Read how many more sectors we need
    ; The number is stored as the first word in Stage 2's memory
    mov es, [Stage2Read + SectorReadParam.bufseg]
    mov al, [es:0]
    mov [Stage2Read + SectorReadParam.numsecs], al
    add word [Stage2Read + SectorReadParam.bufseg], 512 / 16
    inc byte [Stage2Read + SectorReadParam.sector]
    call ReadSectors

    ; Change to new data segment
    mov ax, [Stage2FarPtr.segment]
    mov ds, ax

    ; Jump to Stage 2 Code
    jmp far word [cs:Stage2FarPtr]

; Used as the parameters for ReadSectors
Stage2Read: ISTRUC SectorReadParam
    AT SectorReadParam.bufoff,  dw 0
    AT SectorReadParam.bufseg,  dw 0x07E0
    AT SectorReadParam.numsecs, db 1
    AT SectorReadParam.track,   db 0
    AT SectorReadParam.sector,  db 2
    AT SectorReadParam.head,    db 0
    AT SectorReadParam.drive,   db 0        ; needs to be initialized!
IEND

; Not initialized
Stage2FarPtr:
    .offset     dw 0
    .segment    dw 0

; Ending
times 510-($-$$) db 0    
dw 0xAA55                                  ; Master Boot Record Signature
