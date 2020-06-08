%include "io.asm"
section .data
   ?string_1 db "yingyingying",00h
   ?string_0 db "hahaha",00h
   g_dd dd 0
   g_cc dd 0
   g_aa dd 0
   g_dhhh dd 10 dup (0)
   g_bb dd 0
section .bss
   ?res resb 64
   ?res_read resb 4096
global _start
_start:
   call main
   call $quit
add:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,32
   .label_0:
   .label_1:
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,420
   push edx
   push ecx
   push eax
   mov eax,[ebp-1]
   push eax
   mov eax,[ebp-1]
   push eax
   mov eax,[ebp-12]
   push eax
   call add
   add esp,12
   pop eax
   pop ecx
   pop edx
   .label_2:
   .label_3:
   pop ebx
   leave
   ret
