%include "io.asm"

section .data
msg db "hello world",0ah,00h
msg2 db "12345678955555",0ah,00h
msg3 db "-0",00h
negative db "negative num",00h
positive db "positive num",00h
rtn db 0ah,00h
int_val dd 123456

section .bss
?res resb 64
?res_read resb 4096

section .text
global _start

_start:
    call main
    call $quit

main:
	push ebp
    mov ebp,esp
    push ebx
    mov esi,?res_read
    xor edi,edi
    mov byte [esi+edi],0ah
    sub esp,100
    lea eax,[ebp-80]
    push eax
    call $scan_string
    pop eax
    lea eax,[ebp-80]
    push eax
    call $print_str
    call $print_rtn
    pop eax
    pop ebx
    leave
    ret
