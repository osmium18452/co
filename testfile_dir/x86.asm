%include "io.asm"
section .data
section .bss
   ?res resb 64
   ?res_read resb 4096
global _start
_start:
   call main
   call $quit
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,12
   mov [ebp-4],3
   mov eax,[ebp-4]
   mov [ebp-8],eax
   mov [ebp-12],eax
   mov [ebp-4],eax
   pop ebx
   leave
   ret
