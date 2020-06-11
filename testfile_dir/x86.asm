%include "io.asm"
section .data
   msg db "hello world",0ah,00h
   rtn db 0ah,00h
   ?string_1 db "false",0AH,"",00h
   ?string_0 db "true",0AH,"",00h
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
   sub esp,40
   mov [ebp-4],dword 1
   mov [ebp-8],dword 0
   cmp dword [ebp-4],0
   je .label_x86_false_logiand_17
   cmp dword [ebp-8],0
   je .label_x86_false_logiand_17
   .label_x86_true_logiand_16:
   mov eax,1
   jmp .label_x86_end_logiand_18
   .label_x86_false_logiand_17:
   xor eax,eax
   .label_x86_end_logiand_18:
   cmp eax,dword 0
   je .label_0
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
   jmp .label_1
   .label_0:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_1:
   mov [ebp-4],dword 1
   mov [ebp-8],dword 1
   cmp dword [ebp-4],0
   je .label_x86_false_logiand_20
   cmp dword [ebp-8],0
   je .label_x86_false_logiand_20
   .label_x86_true_logiand_19:
   mov eax,1
   jmp .label_x86_end_logiand_21
   .label_x86_false_logiand_20:
   xor eax,eax
   .label_x86_end_logiand_21:
   cmp eax,dword 0
   je .label_2
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
   jmp .label_3
   .label_2:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_3:
   mov [ebp-4],dword 0
   mov [ebp-8],dword 1
   cmp dword [ebp-4],0
   je .label_x86_false_logiand_23
   cmp dword [ebp-8],0
   je .label_x86_false_logiand_23
   .label_x86_true_logiand_22:
   mov eax,1
   jmp .label_x86_end_logiand_24
   .label_x86_false_logiand_23:
   xor eax,eax
   .label_x86_end_logiand_24:
   cmp eax,dword 0
   je .label_4
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
   jmp .label_5
   .label_4:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_5:
   mov [ebp-4],dword 0
   mov [ebp-8],dword 0
   cmp dword [ebp-4],0
   je .label_x86_false_logiand_26
   cmp dword [ebp-8],0
   je .label_x86_false_logiand_26
   .label_x86_true_logiand_25:
   mov eax,1
   jmp .label_x86_end_logiand_27
   .label_x86_false_logiand_26:
   xor eax,eax
   .label_x86_end_logiand_27:
   cmp eax,dword 0
   je .label_6
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
   jmp .label_7
   .label_6:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_7:
   mov [ebp-4],dword 1
   mov [ebp-8],dword 0
   cmp dword [ebp-4],0
   ja .label_x86_true_logioir_28
   cmp dword [ebp-8],0
   ja .label_x86_true_logioir_28
   .label_x86_false_logioir_29:
   xor eax,eax
   jmp .label_x86_end_logioir_30
   .label_x86_true_logioir_28:
   mov eax,1
   .label_x86_end_logioir_30:
   cmp eax,dword 0
   je .label_8
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
   jmp .label_9
   .label_8:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_9:
   mov [ebp-4],dword 1
   mov [ebp-8],dword 1
   cmp dword [ebp-4],0
   ja .label_x86_true_logioir_31
   cmp dword [ebp-8],0
   ja .label_x86_true_logioir_31
   .label_x86_false_logioir_32:
   xor eax,eax
   jmp .label_x86_end_logioir_33
   .label_x86_true_logioir_31:
   mov eax,1
   .label_x86_end_logioir_33:
   cmp eax,dword 0
   je .label_10
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
   jmp .label_11
   .label_10:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_11:
   mov [ebp-4],dword 0
   mov [ebp-8],dword 1
   cmp dword [ebp-4],0
   ja .label_x86_true_logioir_34
   cmp dword [ebp-8],0
   ja .label_x86_true_logioir_34
   .label_x86_false_logioir_35:
   xor eax,eax
   jmp .label_x86_end_logioir_36
   .label_x86_true_logioir_34:
   mov eax,1
   .label_x86_end_logioir_36:
   cmp eax,dword 0
   je .label_12
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
   jmp .label_13
   .label_12:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_13:
   mov [ebp-4],dword 0
   mov [ebp-8],dword 0
   cmp dword [ebp-4],0
   ja .label_x86_true_logioir_37
   cmp dword [ebp-8],0
   ja .label_x86_true_logioir_37
   .label_x86_false_logioir_38:
   xor eax,eax
   jmp .label_x86_end_logioir_39
   .label_x86_true_logioir_37:
   mov eax,1
   .label_x86_end_logioir_39:
   cmp eax,dword 0
   je .label_14
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
   jmp .label_15
   .label_14:
   push edx
   push ecx
   push eax
   mov eax,?string_1
   push eax
   call $print_str
   pop eax
   pop eax
   pop ecx
   pop edx
   .label_15:
   mov [ebp-40],eax
   pop ebx
   leave
   ret
