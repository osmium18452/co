%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_1 db " ",00h
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
   sub esp,92
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
   mov [ebp-20],dword 0
   .label_0:
   mov [ebp+8],eax
   mov eax,dword [ebp-20]
   cmp eax,dword [ebp+16]
   jb .label_x86_true_lt_16
   xor eax,eax
   jmp .label_x86_end_lt_17
   .label_x86_true_lt_16:
   mov eax,1
   .label_x86_end_lt_17:
   cmp eax,dword 0
   je .label_1
   push edx
   push ecx
   push eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-20]
   imul edi,4
   mov edx,[esi+edi]
   pop edi
   pop esi
   mov eax,edx
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
   inc dword [ebp-20]
   jmp .label_0
   .label_1:
   mov [ebp-24],eax
   mov [ebp+12],ebx
   mov [ebp-16],ecx
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
   push edx
   push ecx
   push eax
   mov eax,dword [ebp+8]
   push eax
   call $print_int
   pop eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   mov eax,dword [ebp-12]
   push eax
   call $print_int
   pop eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp+8]
   imul edi,4
   mov eax,[esi+edi]
   pop edi
   pop esi
   mov eax,eax
   push eax
   call $print_int
   pop eax
   mov eax,?string_0
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_2:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_18
   xor eax,eax
   jmp .label_x86_end_lt_19
   .label_x86_true_lt_18:
   mov eax,1
   .label_x86_end_lt_19:
   cmp eax,dword 0
   je .label_3
   .label_4:
   mov [ebp-36],eax
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_20
   xor eax,eax
   jmp .label_x86_end_lt_21
   .label_x86_true_lt_20:
   mov eax,1
   .label_x86_end_lt_21:
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   mov [ebp-40],eax
   cmp ebx,dword [ebp-12]
   jge .label_x86_true_ge_22
   xor eax,eax
   jmp .label_x86_end_ge_23
   .label_x86_true_ge_22:
   mov eax,1
   .label_x86_end_ge_23:
   mov [ebp-48],eax
   cmp dword [ebp-40],0
   je .label_x86_false_logiand_25
   cmp dword [ebp-48],0
   je .label_x86_false_logiand_25
   .label_x86_true_logiand_24:
   mov eax,1
   jmp .label_x86_end_logiand_26
   .label_x86_false_logiand_25:
   xor eax,eax
   .label_x86_end_logiand_26:
   cmp eax,dword 0
   je .label_5
   dec dword [ebp-8]
   mov [ebp-52],eax
   mov [ebp-44],ebx
   jmp .label_4
   .label_5:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_27
   xor eax,eax
   jmp .label_x86_end_lt_28
   .label_x86_true_lt_27:
   mov eax,1
   .label_x86_end_lt_28:
   cmp eax,dword 0
   je .label_6
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov [esi+edi],ebx
   pop edi
   pop esi
   inc dword [ebp-4]
   mov [ebp-56],eax
   mov [ebp-60],ebx
   jmp .label_7
   .label_6:
   .label_7:
   .label_8:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_29
   xor eax,eax
   jmp .label_x86_end_lt_30
   .label_x86_true_lt_29:
   mov eax,1
   .label_x86_end_lt_30:
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov [ebp-64],eax
   mov eax,[esi+edi]
   pop edi
   pop esi
   mov [ebp-68],eax
   mov eax,dword [ebp-68]
   cmp eax,dword [ebp-12]
   jb .label_x86_true_lt_31
   xor eax,eax
   jmp .label_x86_end_lt_32
   .label_x86_true_lt_31:
   mov eax,1
   .label_x86_end_lt_32:
   mov [ebp-72],eax
   cmp dword [ebp-64],0
   je .label_x86_false_logiand_34
   cmp dword [ebp-72],0
   je .label_x86_false_logiand_34
   .label_x86_true_logiand_33:
   mov eax,1
   jmp .label_x86_end_logiand_35
   .label_x86_false_logiand_34:
   xor eax,eax
   .label_x86_end_logiand_35:
   cmp eax,dword 0
   je .label_9
   inc dword [ebp-4]
   mov [ebp-76],eax
   jmp .label_8
   .label_9:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_36
   xor eax,eax
   jmp .label_x86_end_lt_37
   .label_x86_true_lt_36:
   mov eax,1
   .label_x86_end_lt_37:
   cmp eax,dword 0
   je .label_10
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-4]
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov [esi+edi],ebx
   pop edi
   pop esi
   dec dword [ebp-8]
   mov [ebp-80],eax
   mov [ebp-84],ebx
   jmp .label_11
   .label_10:
   .label_11:
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
   jmp .label_2
   .label_3:
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
   .label_12:
   mov eax,dword [ebp-8]
   cmp eax,dword [ebp-4]
   jb .label_x86_true_lt_38
   xor eax,eax
   jmp .label_x86_end_lt_39
   .label_x86_true_lt_38:
   mov eax,1
   .label_x86_end_lt_39:
   cmp eax,dword 0
   je .label_13
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
   jmp .label_12
   .label_13:
   push edx
   push ecx
   push eax
   mov eax,dword [ebp-4]
   sub eax,dword 1
   mov eax,dword [ebp-4]
   push eax
   mov eax,eax
   push eax
   mov eax,dword 0
   push eax
   call qsort
   add esp,12
   pop eax
   pop ecx
   pop edx
   mov [ebp-24],dword 0
   .label_14:
   mov eax,dword [ebp-24]
   cmp eax,dword [ebp-4]
   jb .label_x86_true_lt_40
   xor eax,eax
   jmp .label_x86_end_lt_41
   .label_x86_true_lt_40:
   mov eax,1
   .label_x86_end_lt_41:
   cmp eax,dword 0
   je .label_15
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
   jmp .label_14
   .label_15:
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
