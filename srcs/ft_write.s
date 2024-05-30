section .text
	global ft_write
	extern __errno_location

ft_write:
	push		rbp   ; preserve calling stack frame
	mov		rbp, rsp	; set calling base stack to current base frame
	xor		rbx, rbx	; set a register for setting _errno

_write_syscall:
	mov		rax, 1
	syscall
	cmp		rax, 0
	jge		_end

_set_error_ret:
	mov		rbx, rax
	neg		rbx
	mov		rax, -1

_set_errno:
	push	rax
	call	__errno_location
	mov		[rax], rbx
	pop		rax

_end:
	pop		rbp
	ret
