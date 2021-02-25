	.text
	.intel_syntax noprefix
	.file	"main.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	xor	eax, eax
	lea	rcx, [rbp - 14]
	mov	dword ptr [rbp - 4], 0
	mov	rdx, rcx
	mov	rdi, rdx
	mov	esi, eax
	mov	edx, 10
	mov	dword ptr [rbp - 20], eax # 4-byte Spill
	mov	qword ptr [rbp - 32], rcx # 8-byte Spill
	call	memset
	mov	edi, dword ptr [rbp - 20] # 4-byte Reload
	mov	rsi, qword ptr [rbp - 32] # 8-byte Reload
	mov	edx, 5
	call	ft_read
	lea	rsi, [rbp - 14]
	movabs	rdi, offset .L.str
	mov	qword ptr [rbp - 40], rax # 8-byte Spill
	mov	al, 0
	call	printf
	xor	r8d, r8d
	mov	dword ptr [rbp - 44], eax # 4-byte Spill
	mov	eax, r8d
	add	rsp, 48
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%s"
	.size	.L.str, 3


	.ident	"clang version 9.0.0-2~ubuntu18.04.2 (tags/RELEASE_900/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym ft_read
	.addrsig_sym printf
