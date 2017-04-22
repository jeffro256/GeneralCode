_itoa_vitaut_5:                         ## @itoa_vitaut_5
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	addq	$11, %rdi
	movq	%rdi, -24(%rbp)
	cmpl	$0, -12(%rbp)
	setl	%al
	andb	$1, %al
	movb	%al, -25(%rbp)
	movq	-24(%rbp), %rdi
	movb	$0, (%rdi)
	testb	$1, -25(%rbp)
	je	LBB4_2
## BB#1:
	imull	$-1, -12(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB4_2:
	jmp	LBB4_3
LBB4_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jb	LBB4_5
## BB#4:                                ##   in Loop: Header=BB4_3 Depth=1
	leaq	_str100p(%rip), %rax
	movl	$100, %ecx
	movl	-12(%rbp), %edx
	movl	%edx, -32(%rbp)
	movq	-24(%rbp), %rsi
	addq	$-2, %rsi
	movq	%rsi, -24(%rbp)
	movl	-12(%rbp), %edx
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	movl	%edx, %eax
	xorl	%edx, %edx
	divl	%ecx
	movl	%eax, -12(%rbp)
	movl	-32(%rbp), %eax
	imull	$100, -12(%rbp), %ecx
	subl	%ecx, %eax
	movl	%eax, %eax
	movl	%eax, %esi
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movw	(%rdi,%rsi,2), %r8w
	movq	-24(%rbp), %rsi
	movw	%r8w, (%rsi)
	jmp	LBB4_3
LBB4_5:
	leaq	_str100p(%rip), %rax
	movq	-24(%rbp), %rcx
	addq	$-2, %rcx
	movq	%rcx, -24(%rbp)
	movl	-12(%rbp), %edx
	movl	%edx, %ecx
	movw	(%rax,%rcx,2), %si
	movq	-24(%rbp), %rax
	movw	%si, (%rax)
	testb	$1, -25(%rbp)
	je	LBB4_7
## BB#6:
	cmpl	$10, -12(%rbp)
	setb	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	movq	-24(%rbp), %rsi
	movq	%rsi, %rdi
	addq	$-1, %rdi
	movq	%rdi, -24(%rbp)
	movb	$45, -1(%rsi,%rdx)
LBB4_7:
	cmpl	$10, -12(%rbp)
	setb	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	addq	-24(%rbp), %rdx
	movq	%rdx, %rax
	popq	%rbp
	retq
	.cfi_endproc
