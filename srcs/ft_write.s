section .text
	global ft_write
	extern __errno_location

ft_write:
	push	rbp   ; preserve calling stack frame
	mov		rbp, rsp	; set calling base stack to current base frame
	xor		rbx, rbx	; set a register for setting _errno

_write_syscall:
	mov		rax, 1
	syscall
	cmp		rax, 0
	jge		_set_errno

_set_error_ret:
	mov		ebx, eax
	neg		ebx
	mov		rax, 0

_set_errno:
	push	rax
	call	__errno_location
	mov		DWORD [rax], ebx
	pop		rax

_end:
	pop		rbp
	ret
