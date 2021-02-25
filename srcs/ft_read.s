	extern	__errno_location
	global ft_read

section	.text

ft_read:
	push	rbp
	mov		rbp, rsp
	xor rax, rax
	xor	rbx, rbx
	syscall
	cmp rax, 0
	jge	_set_errno

_failure:
	mov	rbx, rax
	neg	rbx
	mov	rax, -1

_set_errno:
	push	rax
	call	__errno_location
	mov		DWORD [rax], ebx
	pop		rax
	pop		rbp
	ret
