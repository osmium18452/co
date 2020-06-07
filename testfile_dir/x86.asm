%include "io.asm"
section .data
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
   jmp main
