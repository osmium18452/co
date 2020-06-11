%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_2 db "",0AH,"",00h
   ?string_0 db "Please input: ",00h
   ?string_1 db " ",00h
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
fib:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,28
   cmp dword [ebp+8],dword 0
   je .label_x86_ne_equal_6
   xor eax,eax
   jmp .label_x86_ne_end_7
   .label_x86_ne_equal_6:
   mov eax,1
   .label_x86_ne_end_7:
   cmp eax,dword 0
   je .label_0
   mov eax,dword 1
   mov [ebp-4],eax
   jmp .label_1
   .label_0:
   cmp dword [ebp+8],dword 1
   je .label_x86_ne_equal_8
   xor eax,eax
   jmp .label_x86_ne_end_9
   .label_x86_ne_equal_8:
   mov eax,1
   .label_x86_ne_end_9:
   cmp eax,dword 0
   je .label_2
   mov eax,dword 1
   mov [ebp-8],eax
   jmp .label_3
   .label_2:
   push edx
   push ecx
   push eax
   mov eax,dword [ebp+8]
   sub eax,dword 1
   mov eax,eax
   push eax
   call fib
   mov [ebp-16], eax
   add esp,4
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov ebx,dword [ebp+8]
   sub ebx,dword 2
   mov eax,ebx
   push eax
   call fib
   mov [ebp-24], eax
   add esp,4
   pop eax
   pop ecx
   pop edx
   mov ecx,dword [ebp-16]
   add ecx,dword [ebp-24]
   mov eax,ecx
   mov [ebp-28],ecx
   .label_3:
   .label_1:
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,16
   push edx
   push ecx
   push eax
   mov eax,?string_0
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   call $scan_int
   mov [ebp-4],eax
   mov [ebp-8],dword 0
   .label_4:
   mov eax,dword [ebp-8]
   cmp eax,dword [ebp-4]
   jb .label_x86_true_lt_10
   xor eax,eax
   jmp .label_x86_end_lt_11
   .label_x86_true_lt_10:
   mov eax,1
   .label_x86_end_lt_11:
   cmp eax,dword 0
   je .label_5
   push edx
   push ecx
   push eax
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-8]
   push eax
   call fib
   mov [ebp-16], eax
   add esp,4
   pop eax
   pop ecx
   pop edx
   mov eax,dword [ebp-16]
   push eax
   call $print_int
   pop eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   mov [ebp-12],eax
   inc dword [ebp-8]
   jmp .label_4
   .label_5:
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
   pop ebx
   leave
   ret
