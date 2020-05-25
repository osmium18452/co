	.file	"test.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	cmpl	$9, -8(%rbp)
	ja	.L2
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L4(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L2-.L4
	.long	.L3-.L4
	.long	.L5-.L4
	.long	.L6-.L4
	.long	.L7-.L4
	.long	.L2-.L4
	.long	.L2-.L4
	.long	.L2-.L4
	.long	.L8-.L4
	.long	.L9-.L4
	.text
.L3:
	addl	$1, -8(%rbp)
	jmp	.L10
.L5:
	subl	$1, -8(%rbp)
.L6:
	addl	$5, -8(%rbp)
.L7:
	subl	$5, -8(%rbp)
	jmp	.L10
.L9:
	movl	$123, -8(%rbp)
.L8:
	addl	$1, -8(%rbp)
	subl	$124, -4(%rbp)
	jmp	.L10
.L2:
	addl	$999, -8(%rbp)
	nop
.L10:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
