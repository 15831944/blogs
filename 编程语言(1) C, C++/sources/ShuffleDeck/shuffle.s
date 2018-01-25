	.file	"shuffle.c"
	.local	seed
	.comm	seed,4,4
	.section	.rodata
.LC0:
	.string	"number %i = %i \n"
	.text
.globl shuffle
	.type	shuffle, @function
shuffle:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ebx
	subl	$64, %esp
	leal	-56(%ebp), %ebx
	movl	$0, %eax
	movl	$10, %edx
	movl	%ebx, %edi
	movl	%edx, %ecx
	rep stosl
	movl	seed, %eax
	testl	%eax, %eax
	jne	.L2
	movl	$0, (%esp)
	call	time
	movl	%eax, seed
	movl	seed, %eax
	movl	%eax, (%esp)
	call	srand
.L2:
	movl	$0, -12(%ebp)
	jmp	.L3
.L5:
	movl	$-1, -16(%ebp)
.L4:
	call	rand
	movl	%eax, %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%ecx, %edi
	subl	%eax, %edi
	movl	%edi, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	-56(%ebp,%eax,4), %eax
	testl	%eax, %eax
	jne	.L4
	movl	-16(%ebp), %eax
	movl	$1, -56(%ebp,%eax,4)
	movl	$.LC0, %eax
	movl	-16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %ecx
	movl	%ecx, (%eax,%edx,4)
	addl	$1, -12(%ebp)
.L3:
	cmpl	$9, -12(%ebp)
	jle	.L5
	movl	8(%ebp), %eax
	movl	$0, 40(%eax)
	addl	$64, %esp
	popl	%ebx
	popl	%edi
	popl	%ebp
	ret
	.size	shuffle, .-shuffle
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
