%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_0 db "",0AH,"",00h
   g_a times 1000 dd 0
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
qsort:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,76
   mov eax,[ebp+8]
   mov [ebp-4],eax
   mov ebx,[ebp+12]
   mov [ebp-8],ebx
   push esi
   push edi
   lea esi,[g_a]
   mov edi,eax
   imul edi,4
   mov ecx,[esi+edi]
   pop edi
   pop esi
   mov [ebp-12],ecx
   mov [ebp+8],eax
   mov [ebp+12],ebx
   mov [ebp-16],ecx
   .label_while_start_0:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   setl al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_while_end_1
   mov [ebp-20],eax
   .label_while_start_2:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   setl al
   and eax,000000ffh
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov [ebp-24],eax
   mov eax,[esi+edi]
   pop edi
   pop esi
   mov [ebp-28],eax
   mov eax,dword [ebp-28]
   cmp eax,dword [ebp-12]
   setge al
   and eax,000000ffh
   mov [ebp-32],eax
   cmp dword [ebp-24],0
   je .label_x86_false_logiand_21
   cmp dword [ebp-32],0
   je .label_x86_false_logiand_21
   .label_x86_true_logiand_20:
   mov eax,1
   jmp .label_x86_end_logiand_22
   .label_x86_false_logiand_21:
   xor eax,eax
   .label_x86_end_logiand_22:
   cmp eax,dword 0
   je .label_while_end_3
   mov [ebp-36],eax
   dec dword [ebp-8]
   jmp .label_while_start_2
   .label_while_end_3:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   setl al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_4
   mov [ebp-40],eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov eax,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov [esi+edi],eax
   pop edi
   pop esi
   inc dword [ebp-4]
   mov [ebp-44],eax
   jmp .label_5
   .label_4:
   .label_5:
   .label_while_start_6:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   setl al
   and eax,000000ffh
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov [ebp-48],eax
   mov eax,[esi+edi]
   pop edi
   pop esi
   mov [ebp-52],eax
   mov eax,dword [ebp-52]
   cmp eax,dword [ebp-12]
   setl al
   and eax,000000ffh
   mov [ebp-56],eax
   cmp dword [ebp-48],0
   je .label_x86_false_logiand_30
   cmp dword [ebp-56],0
   je .label_x86_false_logiand_30
   .label_x86_true_logiand_29:
   mov eax,1
   jmp .label_x86_end_logiand_31
   .label_x86_false_logiand_30:
   xor eax,eax
   .label_x86_end_logiand_31:
   cmp eax,dword 0
   je .label_while_end_7
   mov [ebp-60],eax
   inc dword [ebp-4]
   jmp .label_while_start_6
   .label_while_end_7:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   setl al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_8
   mov [ebp-64],eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov eax,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov [esi+edi],eax
   pop edi
   pop esi
   dec dword [ebp-8]
   mov [ebp-68],eax
   jmp .label_9
   .label_8:
   .label_9:
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov eax,[ebp-12]
   mov [esi+edi],eax
   pop edi
   pop esi
   push edx
   push ecx
   push eax
   mov ebx,dword [ebp-4]
   sub ebx,dword 1
   mov [ebp-12],eax
   mov eax,dword [ebp+16]
   push eax
   mov eax,ebx
   push eax
   mov eax,dword [ebp+8]
   push eax
   call qsort
   add esp,12
   pop eax
   pop ecx
   pop edx
   push edx
   push ecx
   push eax
   mov ecx,dword [ebp-4]
   add ecx,dword 1
   mov [ebp-12],eax
   mov eax,dword [ebp+16]
   push eax
   mov eax,dword [ebp+12]
   push eax
   mov eax,ecx
   push eax
   call qsort
   add esp,12
   pop eax
   pop ecx
   pop edx
   mov [ebp-12],eax
   jmp .label_while_start_0
   .label_while_end_1:
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,32
   call $scan_int
   mov [ebp-4],eax
   mov [ebp-8],dword 0
   .label_10:
   mov eax,dword [ebp-8]
   cmp eax,dword [ebp-4]
   setl al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_11
   mov [ebp-12],eax
   call $scan_int
   mov [ebp-16],eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov eax,[ebp-16]
   mov [esi+edi],eax
   pop edi
   pop esi
   inc dword [ebp-8]
   jmp .label_10
   .label_11:
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-4]
   sub eax,dword 1
   mov [ebp-20],eax
   mov eax,dword [ebp-4]
   push eax
   mov eax,dword [ebp-20]
   push eax
   mov eax,dword 0
   push eax
   call qsort
   add esp,12
   pop eax
   pop ecx
   pop edx
   mov [ebp-24],dword 0
   .label_12:
   mov eax,dword [ebp-24]
   cmp eax,dword [ebp-4]
   setl al
   and eax,000000ffh
   cmp eax,dword 0
   je .label_13
   push edx
   push ecx
   push eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-24]
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   mov eax,ebx
   push eax
   call $print_int
   pop eax
   mov eax,dword 32
   push eax
   call $print_char
   pop eax
   pop eax
   pop ecx
   pop edx
   inc dword [ebp-24]
   jmp .label_12
   .label_13:
   mov [ebp-28],eax
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
   mov eax,dword 0
   pop ebx
   leave
   ret
