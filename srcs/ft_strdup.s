extern	malloc
extern	__errno_location
global	ft_strdup

section .text

ft_strdup:
	push		rbp
	mov		rbp, rsp
	xor		rcx, rcx
	jmp		count_byte

inc_rcx:
	inc		rcx
count_byte:
	cmp		BYTE [rdi + rcx], 0
	jne		inc_rcx
	inc		rcx

	push		rdi
	mov		rdi, rcx
	push		rcx
	call		malloc
	pop		rcx
	pop		rdi
	cmp		rax, 0
	je		return

	;	_init_cpy_loop:
	;					xor				rcx, rcx
	;	
	;	_copy_char:
	;					mov				dl, BYTE [rdi + rcx]
	;					mov				BYTE [rax + rcx], dl
	;					cmp				dl, 0
	;					je				return
	;					inc				rcx
	;					jmp				_copy_char
	;	

cpy_str:

	dec		rcx
	mov		dl,	BYTE [rdi + rcx]
	mov		BYTE [rax + rcx], dl
	cmp		rcx, 0
	jne		cpy_str

return:
	mov		rsp, rbp
	pop		rbp
	ret
