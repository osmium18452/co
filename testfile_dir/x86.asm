%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_3 db " ",00h
   ?string_2 db "",0AH,"",00h
   ?string_0 db "l: ",00h
   ?string_1 db " r: ",00h
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



   push edx
   push ecx
   push eax
   mov eax,?string_0
   push eax
   call $print_str
   pop eax
   mov eax,dword [ebp+8]
   push eax
   call $print_int
   pop eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   mov eax,dword [ebp+12]
   push eax
   call $print_int
   pop eax
   mov eax,?string_2
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx

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
   .label_0:
   mov [ebp+8],eax
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_14
   xor eax,eax
   jmp .label_x86_end_lt_15
   .label_x86_true_lt_14:
   mov eax,1
   .label_x86_end_lt_15:
   cmp eax,dword 0
   je .label_1
   .label_2:
   mov [ebp-20],eax
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_16
   xor eax,eax
   jmp .label_x86_end_lt_17
   .label_x86_true_lt_16:
   mov eax,1
   .label_x86_end_lt_17:
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov edx,[esi+edi]
   pop edi
   pop esi
   mov [ebp-24],eax
   cmp edx,dword [ebp-12]
   jge .label_x86_true_ge_18
   xor eax,eax
   jmp .label_x86_end_ge_19
   .label_x86_true_ge_18:
   mov eax,1
   .label_x86_end_ge_19:
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
   je .label_3
   dec dword [ebp-8]
   mov [ebp-36],eax
   mov [ebp+12],ebx
   mov [ebp-16],ecx
   mov [ebp-28],edx
   jmp .label_2
   .label_3:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_23
   xor eax,eax
   jmp .label_x86_end_lt_24
   .label_x86_true_lt_23:
   mov eax,1
   .label_x86_end_lt_24:
   cmp eax,dword 0
   je .label_4
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
   mov [ebp-40],eax
   mov [ebp-44],ebx
   jmp .label_5
   .label_4:
   .label_5:
   .label_6:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_25
   xor eax,eax
   jmp .label_x86_end_lt_26
   .label_x86_true_lt_25:
   mov eax,1
   .label_x86_end_lt_26:
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
   jb .label_x86_true_lt_27
   xor eax,eax
   jmp .label_x86_end_lt_28
   .label_x86_true_lt_27:
   mov eax,1
   .label_x86_end_lt_28:
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
   je .label_7
   inc dword [ebp-4]
   mov [ebp-60],eax
   jmp .label_6
   .label_7:
   mov eax,dword [ebp-4]
   cmp eax,dword [ebp-8]
   jb .label_x86_true_lt_32
   xor eax,eax
   jmp .label_x86_end_lt_33
   .label_x86_true_lt_32:
   mov eax,1
   .label_x86_end_lt_33:
   cmp eax,dword 0
   je .label_8
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
   mov [ebp-64],eax
   mov [ebp-68],ebx
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
   jmp .label_0
   .label_1:
   pop ebx
   leave
   ret
main:
   push ebp
   mov ebp,esp
   push ebx
   sub esp,32
   mov [ebp-4],dword 5
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword 0
   imul edi,4
   mov dword [esi+edi],2
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword 1
   imul edi,4
   mov dword [esi+edi],1
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword 2
   imul edi,4
   mov dword [esi+edi],3
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword 3
   imul edi,4
   mov dword [esi+edi],5
   pop edi
   pop esi
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword 4
   imul edi,4
   mov dword [esi+edi],4
   pop edi
   pop esi
   mov [ebp-8],dword 0
   .label_10:
   mov eax,dword [ebp-8]
   cmp eax,dword [ebp-4]
   jb .label_x86_true_lt_34
   xor eax,eax
   jmp .label_x86_end_lt_35
   .label_x86_true_lt_34:
   mov eax,1
   .label_x86_end_lt_35:
   cmp eax,dword 0
   je .label_11
   push edx
   push ecx
   push eax
   push esi
   push edi
   lea esi,[g_a]
   mov edi,dword [ebp-8]
   imul edi,4
   mov ebx,[esi+edi]
   pop edi
   pop esi
   mov eax,ebx
   push eax
   call $print_int
   pop eax
   mov eax,?string_3
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   inc dword [ebp-8]
   jmp .label_10
   .label_11:
   mov [ebp-12],eax
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
   .label_12:
   mov eax,dword [ebp-24]
   cmp eax,dword [ebp-4]
   jb .label_x86_true_lt_36
   xor eax,eax
   jmp .label_x86_end_lt_37
   .label_x86_true_lt_36:
   mov eax,1
   .label_x86_end_lt_37:
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
   mov eax,?string_2
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
