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
add:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,8
   mov eax,dword [ebp+12]
   imul eax,dword [ebp+16]
   mov ebx,dword [ebp+8]
   add ebx,eax
   mov eax,ebx
   mov [ebp-4],eax
   mov [ebp-8],ebx
   pop ebx
   leave
   ret
return1:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,0
   mov eax,dword 1
   pop ebx
   leave
   ret
add2:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,4
   mov eax,dword [ebp+8]
   add eax,dword [ebp+12]
   mov eax,eax
   mov [ebp-4],eax
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,44
   mov [ebp-4],dword 9
   mov [ebp-8],dword 3
   mov [ebp-16],dword 5
   mov ecx,3
   mov eax,dword [ebp-4]
   cdq
   idiv ecx
   inc dword [ebp-16]
   mov eax,dword 2
   imul eax,dword [ebp-16]
   mov ebx,edx
   add ebx,eax
   mov [ebp-12],ebx
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-12]
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
   push edx
   push ecx
   push eax
   push edx
   push ecx
   push eax
   push edx
   push ecx
   push eax
   call return1
   mov [ebp-32], eax
   add esp,0
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   call return1
   mov [ebp-36], eax
   add esp,0
   pop eax
   pop ecx
   pop edx
   mov ecx,dword [ebp-36]
   imul ecx,dword [ebp-16]
   mov eax,ecx
   push eax
   mov eax,dword [ebp-32]
   push eax
   call add2
   mov [ebp-44], eax
   add esp,8
   pop eax
   pop ecx
   pop edx
   mov eax,dword [ebp-44]
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
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
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
   mov eax,dword [ebp-12]
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
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
   mov [ebp-28],ebx
   mov [ebp-40],ecx
   mov [ebp-20],edx
   pop ebx
   leave
   ret
