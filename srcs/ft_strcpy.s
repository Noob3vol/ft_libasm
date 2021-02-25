global ft_strcpy

section .text
ft_strcpy:
	push	rbp
	mov		rbp, rsp
	xor		rax, rax

cpy_str:
	mov		dl, BYTE [rsi + rax]
	mov		BYTE [rdi + rax], dl
	cmp		BYTE [rdi + rax], 0
	jnz		str_crawling
	pop		rbp
	ret

str_crawling:
	inc rax
	jmp	cpy_str
