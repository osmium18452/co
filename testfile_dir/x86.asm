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
   sub esp,16
   mov [ebp-4],dword 3
   mov [ebp-8],dword 4
   mov eax,dword 2
   add eax,[ebp-4]
   mov [ebp-12],eax
   push eax
   push ecx
   push edx
   mov eax,dword 99
   push eax
   call $print_char
   pop eax
   pop edx
   pop ecx
   pop eax
   push eax
   push ecx
   push edx
   mov eax,dword 10
   push eax
   call $print_char
   pop eax
   pop edx
   pop ecx
   pop eax
   mov [ebp-16],eax
   pop ebx
   leave
   ret
