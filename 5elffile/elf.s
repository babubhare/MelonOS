	.file	"elf.p"
	.text
	.globl	stage
	.bss
	.align 4
	.type	stage, @object
	.size	stage, 4
stage:
	.zero	4
	.section	.rodata
	.align 8
.LC0:
	.string	"initializer function (stage: %d) \n"
	.text
	.globl	initializer
	.type	initializer, @function
initializer:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	stage(%rip), %eax
	addl	$1, %eax
	movl	%eax, stage(%rip)
	movl	stage(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	initializer, .-initializer
	.section	.init_array,"aw"
	.align 8
	.quad	initializer
	.section	.rodata
	.align 8
.LC1:
	.string	"finalizer function (stage: %d) \n"
	.text
	.globl	finalizer
	.type	finalizer, @function
finalizer:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	stage(%rip), %eax
	addl	$1, %eax
	movl	%eax, stage(%rip)
	movl	stage(%rip), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	finalizer, .-finalizer
	.section	.fini_array,"aw"
	.align 8
	.quad	finalizer
	.section	.rodata
.LC2:
	.string	"main function (stage: %d) \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	stage(%rip), %eax
	addl	$1, %eax
	movl	%eax, stage(%rip)
	movl	stage(%rip), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC3:
	.string	"This is an alternative entry point to the program (stage: %d) \n"
	.text
	.globl	alternativeEntryPoint
	.type	alternativeEntryPoint, @function
alternativeEntryPoint:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	stage(%rip), %eax
	addl	$1, %eax
	movl	%eax, stage(%rip)
	movl	stage(%rip), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE9:
	.size	alternativeEntryPoint, .-alternativeEntryPoint
	.ident	"GCC: (Ubuntu 13.2.0-4ubuntu3) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
