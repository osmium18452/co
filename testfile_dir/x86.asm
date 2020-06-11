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
   mov esi,?res_read
   xor edi,edi
   mov byte [esi+edi],0ah
   call main
   call $quit
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,8
   call $scan_int
   mov [ebp-4],eax
   call $scan_char
   mov [ebp-8],eax
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-4]
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
   mov eax,dword [ebp-8]
   push eax
   call $print_char
   pop eax
   pop eax
   pop ecx
   pop edx
   mov eax,dword 0
   pop ebx
   leave
   ret
