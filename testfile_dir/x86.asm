%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_3 db "Please input: ",00h
   ?string_2 db "",0AH,"",00h
   ?string_0 db "Move disk from ",00h
   ?string_1 db " to ",00h
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
hanio:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,12
   cmp dword [ebp+8],dword 0
   sete al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_0
   pop ebx
   leave
   ret
   jmp .label_1
   .label_0:
   .label_1:
   push edx
   push ecx
   push eax
   mov ebx,dword [ebp+8]
   sub ebx,dword 1
   mov [ebp-4],eax
   mov eax,dword [ebp+16]
   push eax
   mov eax,dword [ebp+20]
   push eax
   mov eax,dword [ebp+12]
   push eax
   mov eax,ebx
   push eax
   call hanio
   add esp,16
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov eax,?string_0
   push eax
   call $print_str
   pop eax
   mov eax,dword [ebp+12]
   push eax
   call $print_char
   pop eax
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   mov eax,dword [ebp+20]
   push eax
   call $print_char
   pop eax
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov eax,?string_2
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov ecx,dword [ebp+8]
   sub ecx,dword 1
   mov [ebp-4],eax
   mov eax,dword [ebp+20]
   push eax
   mov eax,dword [ebp+12]
   push eax
   mov eax,dword [ebp+16]
   push eax
   mov eax,ecx
   push eax
   call hanio
   add esp,16
   pop eax
   pop ecx
   pop edx
   mov [ebp-4],eax
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,4
   push edx
   push ecx
   push eax
   mov eax,?string_3
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   call $scan_int
   mov [ebp-4],eax
   push edx
   push ecx
   push eax
   mov eax,dword 67
   push eax
   mov eax,dword 66
   push eax
   mov eax,dword 65
   push eax
   mov eax,dword [ebp-4]
   push eax
   call hanio
   add esp,16
   pop eax
   pop ecx
   pop edx
   pop ebx
   leave
   ret
