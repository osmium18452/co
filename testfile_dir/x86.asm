%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
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
   sub esp,24
   mov [ebp-4],dword 0
   mov [ebp-8],dword 65535
   mov [ebp-12],dword -65536
   cmp dword [ebp-4],dword 0
   je .label_0
   mov eax,dword [ebp-8]
   or eax,dword [ebp-12]
   mov [ebp-16],eax
   mov [ebp-20],eax
   jmp .label_1
   .label_0:
   mov eax,dword [ebp-8]
   and eax,dword [ebp-12]
   mov [ebp-16],eax
   .label_1:
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-16]
   push eax
   call $print_int
   pop eax
   mov eax,dword 10
   push eax
   call $print_char
   pop eax
   pop eax
   pop ecx
   pop edx
   mov eax,dword 0
   mov [ebp-24],eax
   pop ebx
   leave
   ret
