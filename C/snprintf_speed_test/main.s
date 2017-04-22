	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_itoa_vitaut
	.align	4, 0x90
_itoa_vitaut:                           ## @itoa_vitaut
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	addq	$10, %rdi
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	movb	$0, (%rdi)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jb	LBB0_3
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	_str100p(%rip), %rax
	movl	$100, %ecx
	movl	-12(%rbp), %edx
	movl	%edx, -28(%rbp)
	movq	-24(%rbp), %rsi
	addq	$-2, %rsi
	movq	%rsi, -24(%rbp)
	movl	-12(%rbp), %edx
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	movl	%edx, %eax
	xorl	%edx, %edx
	divl	%ecx
	movl	%eax, -12(%rbp)
	movl	-28(%rbp), %eax
	imull	$100, -12(%rbp), %ecx
	subl	%ecx, %eax
	movl	%eax, %eax
	movl	%eax, %esi
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movw	(%rdi,%rsi,2), %r8w
	movq	-24(%rbp), %rsi
	movw	%r8w, (%rsi)
	jmp	LBB0_1
LBB0_3:
	leaq	_str100p(%rip), %rax
	movq	-24(%rbp), %rcx
	addq	$-2, %rcx
	movq	%rcx, -24(%rbp)
	movl	-12(%rbp), %edx
	movl	%edx, %ecx
	movw	(%rax,%rcx,2), %si
	movq	-24(%rbp), %rax
	movw	%si, (%rax)
	cmpl	$10, -12(%rbp)
	setb	%dil
	andb	$1, %dil
	movzbl	%dil, %edx
	movslq	%edx, %rax
	addq	-24(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_itoa_vitaut_2
	.align	4, 0x90
_itoa_vitaut_2:                         ## @itoa_vitaut_2
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	addq	$10, %rdi
	movq	%rdi, -24(%rbp)
	cmpl	$0, -12(%rbp)
	setl	%al
	andb	$1, %al
	movb	%al, -25(%rbp)
	movq	-24(%rbp), %rdi
	movb	$0, (%rdi)
	testb	$1, -25(%rbp)
	je	LBB1_2
## BB#1:
	imull	$-1, -12(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB1_2:
	jmp	LBB1_3
LBB1_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jl	LBB1_5
## BB#4:                                ##   in Loop: Header=BB1_3 Depth=1
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
	cltd
	idivl	%ecx
	movl	%eax, -12(%rbp)
	movl	-32(%rbp), %eax
	imull	$100, -12(%rbp), %ecx
	subl	%ecx, %eax
	movslq	%eax, %rsi
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movw	(%rdi,%rsi,2), %r8w
	movq	-24(%rbp), %rsi
	movw	%r8w, (%rsi)
	jmp	LBB1_3
LBB1_5:
	leaq	_str100p(%rip), %rax
	movq	-24(%rbp), %rcx
	addq	$-2, %rcx
	movq	%rcx, -24(%rbp)
	movslq	-12(%rbp), %rcx
	movw	(%rax,%rcx,2), %dx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
	testb	$1, -25(%rbp)
	je	LBB1_7
## BB#6:
	cmpl	$10, -12(%rbp)
	setl	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	movq	-24(%rbp), %rsi
	movq	%rsi, %rdi
	addq	$-1, %rdi
	movq	%rdi, -24(%rbp)
	movb	$45, -1(%rsi,%rdx)
LBB1_7:
	cmpl	$10, -12(%rbp)
	setl	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	addq	-24(%rbp), %rdx
	movq	%rdx, %rax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_itoa_vitaut_3
	.align	4, 0x90
_itoa_vitaut_3:                         ## @itoa_vitaut_3
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	addq	$10, %rdi
	movq	%rdi, -24(%rbp)
	cmpl	$0, -12(%rbp)
	setl	%al
	andb	$1, %al
	movb	%al, -25(%rbp)
	movq	-24(%rbp), %rdi
	movb	$0, (%rdi)
	testb	$1, -25(%rbp)
	je	LBB2_2
## BB#1:
	imull	$-1, -12(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB2_2:
	jmp	LBB2_3
LBB2_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jl	LBB2_5
## BB#4:                                ##   in Loop: Header=BB2_3 Depth=1
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
	cltd
	idivl	%ecx
	movl	%eax, -12(%rbp)
	movl	-32(%rbp), %eax
	imull	$100, -12(%rbp), %ecx
	subl	%ecx, %eax
	movslq	%eax, %rsi
	movq	-40(%rbp), %rdi         ## 8-byte Reload
	movw	(%rdi,%rsi,2), %r8w
	movq	-24(%rbp), %rsi
	movw	%r8w, (%rsi)
	jmp	LBB2_3
LBB2_5:
	leaq	_str100p(%rip), %rax
	movq	-24(%rbp), %rcx
	addq	$-2, %rcx
	movq	%rcx, -24(%rbp)
	movslq	-12(%rbp), %rcx
	movw	(%rax,%rcx,2), %dx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
	testb	$1, -25(%rbp)
	je	LBB2_7
## BB#6:
	cmpl	$10, -12(%rbp)
	setl	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	movq	-24(%rbp), %rsi
	movq	%rsi, %rdi
	addq	$-1, %rdi
	movq	%rdi, -24(%rbp)
	movb	$45, -1(%rsi,%rdx)
LBB2_7:
	cmpl	$10, -12(%rbp)
	setl	%al
	andb	$1, %al
	movzbl	%al, %ecx
	movslq	%ecx, %rdx
	addq	-24(%rbp), %rdx
	movq	%rdx, %rax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_itoa_vitaut_4
	.align	4, 0x90
_itoa_vitaut_4:                         ## @itoa_vitaut_4
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
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
	je	LBB3_2
## BB#1:
	imull	$-1, -12(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB3_2:
	jmp	LBB3_3
LBB3_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -12(%rbp)
	jb	LBB3_5
## BB#4:                                ##   in Loop: Header=BB3_3 Depth=1
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
	jmp	LBB3_3
LBB3_5:
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
	je	LBB3_7
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
LBB3_7:
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

	.globl	_itoa_vitaut_5
	.align	4, 0x90
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

	.section	__TEXT,__literal4,4byte_literals
	.align	2
LCPI5_0:
	.long	1232348160              ## float 1.0E+6
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp15:
	.cfi_def_cfa_offset 16
Ltmp16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp17:
	.cfi_def_cfa_register %rbp
	subq	$256, %rsp              ## imm = 0x100
	xorl	%eax, %eax
	movl	%eax, %edi
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -8(%rbp)
	movl	$0, -36(%rbp)
	callq	_time
	movl	%eax, %edx
	movl	%edx, %edi
	callq	_srand
	callq	_clock
	movq	%rax, -48(%rbp)
	movq	$0, -72(%rbp)
LBB5_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$100000000, -72(%rbp)   ## imm = 0x5F5E100
	jge	LBB5_4
## BB#2:                                ##   in Loop: Header=BB5_1 Depth=1
	leaq	-32(%rbp), %rdi
	movq	%rdi, -96(%rbp)         ## 8-byte Spill
	callq	_rand
	movq	-96(%rbp), %rdi         ## 8-byte Reload
	movl	%eax, %esi
	callq	_itoa_vitaut_4
	movq	%rax, -104(%rbp)        ## 8-byte Spill
## BB#3:                                ##   in Loop: Header=BB5_1 Depth=1
	movq	-72(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -72(%rbp)
	jmp	LBB5_1
LBB5_4:
	leaq	L_.str(%rip), %rdi
	leaq	L_.str.1(%rip), %rsi
	movl	$100000000, %eax        ## imm = 0x5F5E100
	movl	%eax, %edx
	movss	LCPI5_0(%rip), %xmm0    ## xmm0 = mem[0],zero,zero,zero
	movq	%rdi, -112(%rbp)        ## 8-byte Spill
	movq	%rsi, -120(%rbp)        ## 8-byte Spill
	movq	%rdx, -128(%rbp)        ## 8-byte Spill
	movss	%xmm0, -132(%rbp)       ## 4-byte Spill
	callq	_clock
	movq	%rax, -56(%rbp)
	movq	-48(%rbp), %rdx
	movq	%rax, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rdi
	shrq	%rdi
	movl	%esi, %ecx
	andl	$1, %ecx
	movl	%ecx, %esi
	orq	%rdi, %rsi
	subq	%rdx, %rax
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm0, %xmm0
	cvtsi2ssq	%rax, %xmm1
	movss	%xmm1, -136(%rbp)       ## 4-byte Spill
	movss	%xmm0, -140(%rbp)       ## 4-byte Spill
	js	LBB5_16
## BB#15:
	movss	-136(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -140(%rbp)       ## 4-byte Spill
LBB5_16:
	movss	-140(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	-132(%rbp), %xmm1       ## 4-byte Reload
                                        ## xmm1 = mem[0],zero,zero,zero
	divss	%xmm1, %xmm0
	movss	%xmm0, -60(%rbp)
	cvtss2sd	-60(%rbp), %xmm0
	movq	-112(%rbp), %rdi        ## 8-byte Reload
	movq	-120(%rbp), %rsi        ## 8-byte Reload
	movq	-128(%rbp), %rdx        ## 8-byte Reload
	movb	$1, %al
	callq	_printf
	movl	%eax, -144(%rbp)        ## 4-byte Spill
	callq	_clock
	movq	%rax, -48(%rbp)
	movq	$0, -80(%rbp)
LBB5_5:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$100000000, -80(%rbp)   ## imm = 0x5F5E100
	jge	LBB5_8
## BB#6:                                ##   in Loop: Header=BB5_5 Depth=1
	leaq	-32(%rbp), %rdi
	movq	%rdi, -152(%rbp)        ## 8-byte Spill
	callq	_rand
	movq	-152(%rbp), %rdi        ## 8-byte Reload
	movl	%eax, %esi
	callq	_itoa_vitaut_5
	movq	%rax, -160(%rbp)        ## 8-byte Spill
## BB#7:                                ##   in Loop: Header=BB5_5 Depth=1
	movq	-80(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -80(%rbp)
	jmp	LBB5_5
LBB5_8:
	leaq	L_.str(%rip), %rdi
	leaq	L_.str.2(%rip), %rsi
	movl	$100000000, %eax        ## imm = 0x5F5E100
	movl	%eax, %edx
	movss	LCPI5_0(%rip), %xmm0    ## xmm0 = mem[0],zero,zero,zero
	movq	%rdi, -168(%rbp)        ## 8-byte Spill
	movq	%rsi, -176(%rbp)        ## 8-byte Spill
	movq	%rdx, -184(%rbp)        ## 8-byte Spill
	movss	%xmm0, -188(%rbp)       ## 4-byte Spill
	callq	_clock
	movq	%rax, -56(%rbp)
	movq	-48(%rbp), %rdx
	movq	%rax, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rdi
	shrq	%rdi
	movl	%esi, %ecx
	andl	$1, %ecx
	movl	%ecx, %esi
	orq	%rdi, %rsi
	subq	%rdx, %rax
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm0, %xmm0
	cvtsi2ssq	%rax, %xmm1
	movss	%xmm1, -192(%rbp)       ## 4-byte Spill
	movss	%xmm0, -196(%rbp)       ## 4-byte Spill
	js	LBB5_18
## BB#17:
	movss	-192(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -196(%rbp)       ## 4-byte Spill
LBB5_18:
	movss	-196(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	-188(%rbp), %xmm1       ## 4-byte Reload
                                        ## xmm1 = mem[0],zero,zero,zero
	divss	%xmm1, %xmm0
	movss	%xmm0, -60(%rbp)
	cvtss2sd	-60(%rbp), %xmm0
	movq	-168(%rbp), %rdi        ## 8-byte Reload
	movq	-176(%rbp), %rsi        ## 8-byte Reload
	movq	-184(%rbp), %rdx        ## 8-byte Reload
	movb	$1, %al
	callq	_printf
	movl	%eax, -200(%rbp)        ## 4-byte Spill
	callq	_clock
	movq	%rax, -48(%rbp)
	movq	$0, -88(%rbp)
LBB5_9:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$100000000, -88(%rbp)   ## imm = 0x5F5E100
	jge	LBB5_12
## BB#10:                               ##   in Loop: Header=BB5_9 Depth=1
	leaq	-32(%rbp), %rdi
	movq	%rdi, -208(%rbp)        ## 8-byte Spill
	callq	_rand
	movq	-208(%rbp), %rdi        ## 8-byte Reload
	movl	%eax, %esi
	callq	_itoa
	movq	%rax, -216(%rbp)        ## 8-byte Spill
## BB#11:                               ##   in Loop: Header=BB5_9 Depth=1
	movq	-88(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -88(%rbp)
	jmp	LBB5_9
LBB5_12:
	leaq	L_.str(%rip), %rdi
	leaq	L_.str.3(%rip), %rsi
	movl	$100000000, %eax        ## imm = 0x5F5E100
	movl	%eax, %edx
	movss	LCPI5_0(%rip), %xmm0    ## xmm0 = mem[0],zero,zero,zero
	movq	%rdi, -224(%rbp)        ## 8-byte Spill
	movq	%rsi, -232(%rbp)        ## 8-byte Spill
	movq	%rdx, -240(%rbp)        ## 8-byte Spill
	movss	%xmm0, -244(%rbp)       ## 4-byte Spill
	callq	_clock
	movq	%rax, -56(%rbp)
	movq	-48(%rbp), %rdx
	movq	%rax, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rdi
	shrq	%rdi
	movl	%esi, %ecx
	andl	$1, %ecx
	movl	%ecx, %esi
	orq	%rdi, %rsi
	subq	%rdx, %rax
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm0, %xmm0
	cvtsi2ssq	%rax, %xmm1
	movss	%xmm1, -248(%rbp)       ## 4-byte Spill
	movss	%xmm0, -252(%rbp)       ## 4-byte Spill
	js	LBB5_20
## BB#19:
	movss	-248(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -252(%rbp)       ## 4-byte Spill
LBB5_20:
	movss	-252(%rbp), %xmm0       ## 4-byte Reload
                                        ## xmm0 = mem[0],zero,zero,zero
	movss	-244(%rbp), %xmm1       ## 4-byte Reload
                                        ## xmm1 = mem[0],zero,zero,zero
	divss	%xmm1, %xmm0
	movss	%xmm0, -60(%rbp)
	cvtss2sd	-60(%rbp), %xmm0
	movq	-224(%rbp), %rdi        ## 8-byte Reload
	movq	-232(%rbp), %rsi        ## 8-byte Reload
	movq	-240(%rbp), %rdx        ## 8-byte Reload
	movb	$1, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	(%rdx), %rdx
	cmpq	-8(%rbp), %rdx
	movl	%eax, -256(%rbp)        ## 4-byte Spill
	jne	LBB5_14
## BB#13:                               ## %SP_return
	xorl	%eax, %eax
	addq	$256, %rsp              ## imm = 0x100
	popq	%rbp
	retq
LBB5_14:                                ## %CallStackCheckFailBlk
	callq	___stack_chk_fail
	.cfi_endproc

	.section	__TEXT,__const
	.align	4                       ## @str100p
_str100p:
	.short	12336                   ## 0x3030
	.short	12592                   ## 0x3130
	.short	12848                   ## 0x3230
	.short	13104                   ## 0x3330
	.short	13360                   ## 0x3430
	.short	13616                   ## 0x3530
	.short	13872                   ## 0x3630
	.short	14128                   ## 0x3730
	.short	14384                   ## 0x3830
	.short	14640                   ## 0x3930
	.short	12337                   ## 0x3031
	.short	12593                   ## 0x3131
	.short	12849                   ## 0x3231
	.short	13105                   ## 0x3331
	.short	13361                   ## 0x3431
	.short	13617                   ## 0x3531
	.short	13873                   ## 0x3631
	.short	14129                   ## 0x3731
	.short	14385                   ## 0x3831
	.short	14641                   ## 0x3931
	.short	12338                   ## 0x3032
	.short	12594                   ## 0x3132
	.short	12850                   ## 0x3232
	.short	13106                   ## 0x3332
	.short	13362                   ## 0x3432
	.short	13618                   ## 0x3532
	.short	13874                   ## 0x3632
	.short	14130                   ## 0x3732
	.short	14386                   ## 0x3832
	.short	14642                   ## 0x3932
	.short	12339                   ## 0x3033
	.short	12595                   ## 0x3133
	.short	12851                   ## 0x3233
	.short	13107                   ## 0x3333
	.short	13363                   ## 0x3433
	.short	13619                   ## 0x3533
	.short	13875                   ## 0x3633
	.short	14131                   ## 0x3733
	.short	14387                   ## 0x3833
	.short	14643                   ## 0x3933
	.short	12340                   ## 0x3034
	.short	12596                   ## 0x3134
	.short	12852                   ## 0x3234
	.short	13108                   ## 0x3334
	.short	13364                   ## 0x3434
	.short	13620                   ## 0x3534
	.short	13876                   ## 0x3634
	.short	14132                   ## 0x3734
	.short	14388                   ## 0x3834
	.short	14644                   ## 0x3934
	.short	12341                   ## 0x3035
	.short	12597                   ## 0x3135
	.short	12853                   ## 0x3235
	.short	13109                   ## 0x3335
	.short	13365                   ## 0x3435
	.short	13621                   ## 0x3535
	.short	13877                   ## 0x3635
	.short	14133                   ## 0x3735
	.short	14389                   ## 0x3835
	.short	14645                   ## 0x3935
	.short	12342                   ## 0x3036
	.short	12598                   ## 0x3136
	.short	12854                   ## 0x3236
	.short	13110                   ## 0x3336
	.short	13366                   ## 0x3436
	.short	13622                   ## 0x3536
	.short	13878                   ## 0x3636
	.short	14134                   ## 0x3736
	.short	14390                   ## 0x3836
	.short	14646                   ## 0x3936
	.short	12343                   ## 0x3037
	.short	12599                   ## 0x3137
	.short	12855                   ## 0x3237
	.short	13111                   ## 0x3337
	.short	13367                   ## 0x3437
	.short	13623                   ## 0x3537
	.short	13879                   ## 0x3637
	.short	14135                   ## 0x3737
	.short	14391                   ## 0x3837
	.short	14647                   ## 0x3937
	.short	12344                   ## 0x3038
	.short	12600                   ## 0x3138
	.short	12856                   ## 0x3238
	.short	13112                   ## 0x3338
	.short	13368                   ## 0x3438
	.short	13624                   ## 0x3538
	.short	13880                   ## 0x3638
	.short	14136                   ## 0x3738
	.short	14392                   ## 0x3838
	.short	14648                   ## 0x3938
	.short	12345                   ## 0x3039
	.short	12601                   ## 0x3139
	.short	12857                   ## 0x3239
	.short	13113                   ## 0x3339
	.short	13369                   ## 0x3439
	.short	13625                   ## 0x3539
	.short	13881                   ## 0x3639
	.short	14137                   ## 0x3739
	.short	14393                   ## 0x3839
	.short	14649                   ## 0x3939

	.align	2                       ## @itoa_vitaut_5.nullIndex
_itoa_vitaut_5.nullIndex:
	.long	11                      ## 0xb

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"'%s' did %ld loops in %f seconds.\n"

L_.str.1:                               ## @.str.1
	.asciz	"itoa_vitaut_4(buffer, rand())"

L_.str.2:                               ## @.str.2
	.asciz	"itoa_vitaut_5(buffer, rand())"

L_.str.3:                               ## @.str.3
	.asciz	"itoa(buffer, rand())"


.subsections_via_symbols
