$quit:
    mov ebx,0
    mov eax,1
    int 80h

$itos:
    push ebp
    mov ebp,esp
    push ebx
    push esi
    mov eax,[ebp+8]
    mov esi,eax
    cmp eax,0
    je .eq0
    jg .pos
    neg eax
    .pos:
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
	cmp esi,0
	jg .positive
	mov edx,'-'
	push edx
	inc ecx
	.positive:
    mov byte [?res+ecx],00h
    mov ebx,0
    .loop2:
        pop edx
        mov [?res+ebx],dl
        inc ebx
        cmp ebx,ecx
        jne .loop2
    jmp .eop
    .eq0:
    mov word[?res],0030h
    .eop:
    pop esi
    pop ebx
    leave
    ret

$hextos:
    push ebp
    mov ebp,esp
    push ebx
    push esi
    mov eax,[ebp+8]
    mov esi,eax
    cmp eax,0
    je .eq0
    jg .pos
    neg eax
    .pos:
    mov ecx,0
    mov ebx,10h
    .loop1:
        cdq
        div ebx
        cmp edx,9
        jg .greater
        add edx,'0'
        jmp .addend
        .greater:
        add edx,'a'
        sub edx,10
        .addend:
        push edx
        inc ecx
        cmp eax,0
        jne .loop1
	cmp esi,0
	jg .positive
	mov edx,'-'
	push edx
	inc ecx
	.positive:
    mov byte [?res+ecx],00h
    mov ebx,0
    .loop2:
        pop edx
        mov [?res+ebx],dl
        inc ebx
        cmp ebx,ecx
        jne .loop2
    jmp .eop
    .eq0:
    mov word[?res],0030h
    .eop:
    pop esi
    pop ebx
    leave
    ret

$print_int:
    push ebp
    mov ebp,esp
    mov eax,[ebp+8]
    push eax
    call $itos
    push ?res
    call $print_str
    leave
    ret

$print_hex:
    push ebp
    mov ebp,esp
    mov eax,[ebp+8]
    push eax
    call $hextos
    push ?res
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

$print_char:
	push ebp
	mov ebp,esp
	mov edx,1
	lea ecx,[ebp+8]
	mov ebx,1
	mov eax,4
	int 80h
	leave
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

$print_space:
	pusha
	mov eax,' '
	push eax
	call $print_char
	pop eax
	popa
	ret

$scan_str:
	push ebx
	mov edx,4095
	mov ecx, ?res_read
	mov ebx,0
	mov eax,3
	int 80h
	pop ebx
	ret



$stoi:
	push ebp
	mov ebp,esp

	push esi
	push edi

	mov eax,0
	mov esi,[ebp+8]
	xor edi,edi
	cmp byte [esi], '-'
	jne .notdash
	inc edi
	inc esi
	.notdash:
	mov ecx,10
	xor edx,edx
	.loop1:
		mov dl,[esi]
		cmp dl,0
		je .end
		imul eax,ecx
		sub edx,'0'
		add eax,edx
		inc esi
		jmp .loop1

	.end:
	cmp edi,0
	je .non_neg
	neg eax
	.non_neg:
	pop edi
	pop esi
	leave
	ret
