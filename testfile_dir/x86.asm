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
   sub esp,100
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 0
   imul edi,4
   mov dword [esi+edi],1
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 1
   imul edi,4
   mov dword [esi+edi],2
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 2
   imul edi,4
   mov dword [esi+edi],3
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 0
   imul edi,4
   mov eax,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 1
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   mov ecx,eax
   add ecx,ebx
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 2
   imul edi,4
   mov edx,[esi+edi]
   pop edi
   pop esi
   mov [ebp-60],ecx
   mov ecx,dword [ebp-60]
   add ecx,edx
   mov [ebp-48],ecx
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-48]
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
   mov [ebp-72],dword 1
   mov [ebp-76],dword 1
   push edx
   push ecx
   push eax
   mov [ebp-52],eax
   mov eax,dword [ebp-72]
   add eax,dword [ebp-76]
   mov eax,eax
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
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 0
   imul edi,4
   mov [ebp-56],ebx
   mov ebx,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 1
   imul edi,4
   mov [ebp-64],edx
   mov edx,[esi+edi]
   pop edi
   pop esi
   mov [ebp-68],ecx
   mov ecx,ebx
   add ecx,edx
   mov eax,ecx
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 1
   imul edi,4
   mov [ebp-80],eax
   mov eax,[esi+edi]
   pop edi
   pop esi
   mov eax,eax
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
   push esi
   push edi
   lea esi,[ebp-40]
   mov edi,dword 2
   imul edi,4
   mov [ebp-84],ebx
   mov ebx,[esi+edi]
   pop edi
   pop esi
   mov eax,ebx
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
   mov [ebp-96],eax
   mov [ebp-100],ebx
   mov [ebp-92],ecx
   mov [ebp-88],edx
   pop ebx
   leave
   ret
