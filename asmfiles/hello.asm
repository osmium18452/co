%include "io.asm"

section .data
msg db "hello world",0ah,00h
msg2 db "123456",0ah,00h
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
    jmp main

main:
;	mov eax,123abch
;	push eax
;	call $print_hex
;	call $print_rtn
;	call $quit
	mov eax,msg3
	push eax
	call $stoi
	push eax
	call $print_int
	call $print_rtn
    call $quit
