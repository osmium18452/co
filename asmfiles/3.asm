section .data
msg db 'hello 123 world',0AH,0H
int_val dd 123456

section .text
global _start

_start:
    jmp main

$quit:
    mov ebx,0
    mov eax,1
    int 80h

$to_string:


$print_str:
    push ebx
    mov ebp,esp
    mov [ebp-4],ebx
    call $strlen
    mov edx,eax
    mov ecx,ebx
    mov ebx,1
    mov eax,4
    int 80h
    pop ebx
    ret

$strlen:
    push ebx
    mov eax,ebx
    .nextchar:
    cmp byte[eax],0
    jz .finished
    inc eax
    jmp .nextchar
    .finished:
    sub eax,ebx
    pop ebx
    ret

main:
    mov ebx,msg
    call $print_str
    mov ebx,10
    mov ecx,10

    call $quit
