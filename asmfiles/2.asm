
SECTION .data                            ; 数据段
    msg     db  'Hello World!', 0Ah     ; 创建字符串，0Ah是换行符

SECTION .text                            ; 代码段
global  _start
_start:
    mov     eax, msg         ; 将字符串初始地址存入EAX寄存器
    call    strlen           ; 调用我们编写的函数

    mov     edx, eax         ; 我们的函数将结果存入EAX，所以这里把它的值传到EDX中去
    mov     ecx, msg         ; 字符串地址
    mov     ebx, 1           ; 写入到标准输出
    mov     eax, 4           ; SYS_WRITE 中断操作数 4
    int     80h              ; 调用系统中断

    mov     ebx, 0           ; 返回值
    mov     eax, 1           ; SYS_EXIT 中断操作数 1
    int     80h              ; 调用系统中断


strlen:                      ; 这是我们编写的第一个函数的声明
    push    ebx              ; 接下来会用到EBX，所以将EBX中的值入栈，之后我们再把它取出来
    mov     ebx, eax         ; 将EAX中的值存入EBX

nextchar:                    ; 计算字符串长度
    cmp     byte [eax], 0    ; 将eax储存地址指向的数据与0进行比对（字符串以0结尾）
    jz      finished         ; 若标志位被设置为0，则跳转至finished
    inc     eax              ; 递加eax
    jmp     nextchar         ; 跳转至nextchar

finished:
    sub     eax, ebx         ; eax = eax - ebx
    pop     ebx              ; 将之前存入的值取出来
    ret                      ; 返回到调用CALL的地方