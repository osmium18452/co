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
	.ascii "fuck china\0"
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
	mov	edx, DWORD PTR 16[rbp]
	mov	eax, DWORD PTR 24[rbp]
	add	eax, edx
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	add	rsp, 16
	pop	rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "0\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 64
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	movabs	rax, 8031924123371070824
	mov	QWORD PTR -32[rbp], rax
	mov	QWORD PTR -24[rbp], 6581362
	mov	DWORD PTR -16[rbp], 0
	cmp	DWORD PTR -4[rbp], 9
	ja	.L4
	mov	eax, DWORD PTR -4[rbp]
	lea	rdx, 0[0+rax*4]
	lea	rax, .L6[rip]
	mov	eax, DWORD PTR [rdx+rax]
	cdqe
	lea	rdx, .L6[rip]
	add	rax, rdx
	jmp	rax
	.section .rdata,"dr"
	.align 4
.L6:
	.long	.L4-.L6
	.long	.L11-.L6
	.long	.L10-.L6
	.long	.L9-.L6
	.long	.L8-.L6
	.long	.L4-.L6
	.long	.L4-.L6
	.long	.L4-.L6
	.long	.L7-.L6
	.long	.L5-.L6
	.text
.L11:
	add	DWORD PTR -4[rbp], 1
	jmp	.L12
.L10:
	sub	DWORD PTR -4[rbp], 1
.L9:
	add	DWORD PTR -4[rbp], 5
.L8:
	sub	DWORD PTR -4[rbp], 5
	jmp	.L12
.L5:
	mov	DWORD PTR -4[rbp], 123
.L7:
	add	DWORD PTR -4[rbp], 1
	sub	DWORD PTR -8[rbp], 124
	jmp	.L12
.L4:
	add	DWORD PTR -4[rbp], 999
	lea	rax, .LC0[rip]
	mov	BYTE PTR -27[rbp], al
	nop
.L12:
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	edx, eax
	lea	rax, abc[rip]
	mov	DWORD PTR [rax], edx
	mov	edx, DWORD PTR -8[rbp]
	mov	eax, DWORD PTR -4[rbp]
	mov	ecx, eax
	call	func
	mov	edx, eax
	lea	rax, def[rip]
	mov	DWORD PTR [rax], edx
	movzx	eax, BYTE PTR -26[rbp]
	movsx	eax, al
	add	rsp, 64
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
