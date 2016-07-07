global start
global fizzbuzz


SECTION .TEXT

start:
fizzbuzz:
    mov r8, 1
    xor rbx, rbx

.loop:
    cmp rbx, FizzBuzzBuff.size - fizz.len - buzz.len - 1
    jbe .buffer_data
    call PrintFizzBuzz
.buffer_data
    xor rdx, rdx
    mov rax, r8
    mov rcx, 5
    div rcx
    test rdx, rdx
    setz dl
    cmp rax, 100
    jbe .loop

    mov rax, 0x2000001
    mov rdi, 0
    syscall

PrintFizzBuzz:
    mov rax, 0x2000004
    mov rdi, 1
    lea rsi, [rel FizzBuzzBuff]
    mov rdx, FizzBuffBuff.size
    syscall
    xor rbx, rbx

    ret


SECTION .DATA

fizz db "Fizz"
    .len equ $ - fizz
buzz db "Buzz"
    .len equ $ - buzz


SECTION .BSS

FizzBuzzBuff resb 1000
    .size equ $ - FizzBuzzBuff

