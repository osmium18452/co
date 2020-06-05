$quit:
    mov ebx,0
    mov eax,1
    int 80h

$itos:
    push ebp
    mov ebp,esp
    push ebx
    mov eax,[ebp+8]
    cmp eax,0
    je .eq0
    mov ecx,0
    mov ebx,10
    .loop1:
        cdq
        div ebx
        add edx,'0'
        push edx
        inc ecx
        cmp eax,0
        jne .loop1
    mov byte [res+ecx],00h
    mov ebx,0
    .loop2:
        pop edx
        mov [res+ebx],dl
        inc ebx
        cmp ebx,ecx
        jne .loop2
    jmp .eop
    .eq0:
    mov word[res],0030h
    .eop:
    pop ebx
    leave
    ret

$print_int:
    push ebp
    mov ebp,esp
    mov eax,[ebp+8]
    push eax
    call $itos
    push res
    call $print_str
    leave
    ret

$strlen:
    ;ebp+8: string location
    push ebp
    mov ebp,esp
    mov ecx,[ebp+8]
    mov eax,ecx
    .nextchar:
        cmp byte[eax],0
        jz .finished
        inc eax
        jmp .nextchar
    .finished:
    sub eax,ecx
    leave
    ret

$print_str:
    push ebp
    mov ebp,esp
    push ebx
    mov eax,[ebp+8]
    push eax
    call $strlen
    mov edx,eax
    pop eax
    mov ecx,eax
    mov ebx,1
    mov eax,4
    int 80h
    pop ebx
    leave
    ret

$print_rtn:
    pusha
    mov edx,1
    mov ecx,rtn
    mov ebx,1
    mov eax,4
    int 80h
    popa
    ret

$print_hello:
    pusha
    mov edx,12
    mov ecx,msg
    mov ebx,1
    mov eax,4
    int 80h
    popa
    ret