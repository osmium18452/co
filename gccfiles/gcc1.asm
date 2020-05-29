	.file	"gcc1.c"
	.intel_syntax noprefix
	.text
	.comm	abc, 4, 2
	.comm	def, 4, 2
	.comm	ghi, 40, 5
	.globl	jkl
	.data
	.align 8
jkl:
	.ascii "fuck \12 china\0"
	.text
	.globl	func
	.def	func;	.scl	2;	.type	32;	.endef
	.seh_proc	func
func:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 16
	.seh_stackalloc	16
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	mov	DWORD PTR 24[rbp], edx
	mov	DWORD PTR 32[rbp], r8d
	mov	DWORD PTR 40[rbp], r9d
	mov	edx, DWORD PTR 16[rbp]
	mov	eax, DWORD PTR 24[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 32[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 40[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 48[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 56[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 64[rbp]
	add	edx, eax
	mov	eax, DWORD PTR 72[rbp]
	add	eax, edx
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	add	rsp, 16
	pop	rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 96
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	movabs	rax, 8031924123371070824
	mov	QWORD PTR -32[rbp], rax
	mov	QWORD PTR -24[rbp], 6581362
	mov	DWORD PTR -16[rbp], 0
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	edx, eax
	lea	rax, abc[rip]
	mov	DWORD PTR [rax], edx
	mov	edx, DWORD PTR -8[rbp]
	mov	eax, DWORD PTR -4[rbp]
	mov	DWORD PTR 56[rsp], 8
	mov	DWORD PTR 48[rsp], 7
	mov	DWORD PTR 40[rsp], 6
	mov	DWORD PTR 32[rsp], 5
	mov	r9d, 4
	mov	r8d, 3
	mov	ecx, eax
	call	func
	mov	edx, eax
	lea	rax, def[rip]
	mov	DWORD PTR [rax], edx
	movzx	eax, BYTE PTR -26[rbp]
	movsx	edx, al
	lea	rax, def[rip]
	mov	eax, DWORD PTR [rax]
	add	eax, edx
	add	rsp, 96
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
