SECTION .data                            ; 数据段
    msg     db  'Hello World!', 0Ah      ; 创建字符串，0Ah是换行符

SECTION .text                            ; 代码段
global  _start
_start:
    mov     edx, 13     ; 字符串长度
    mov     ecx, msg    ; 字符串地址
    mov     ebx, 1      ; 写入到标准输出
    mov     eax, 4      ; SYS_WRITE 中断操作数 4
    int     80h         ; 调用系统中断

    mov     ebx, 0      ; 返回值
    mov     eax, 1      ; SYS_EXIT 中断操作数 1
    int     80h         ; 调用系统中断