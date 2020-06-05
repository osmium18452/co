%include "io.asm"

section .data
msg db "hello world",0ah,00h
msg2 db "123456789",0ah,00h
rtn db 0ah,00h
int_val dd 123456

section .bss
?res resb 64
?res_read resb 4096

section .text
global _start

_start:
    jmp main

main:
;    mov eax,123456666
;    push eax
;    call $print_int
;    call $print_rtn
    call $scan_str
    mov eax,?res_read
    push eax
    call $print_str
    call $quit
