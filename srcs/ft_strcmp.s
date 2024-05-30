section .text
	global ft_strcmp

ft_strcmp:
		push	rbp
		mov	rbp, rsp
		xor	rdx, rdx
		xor rcx, rcx

_strcmp_lol:
		xor rax, rax
		mov dl, BYTE [rsi + rcx]
		cmp	BYTE [rdi + rcx], dl
		jne	_done
		cmp	BYTE [rsi + rcx], 0
		je	_done
		cmp	BYTE [rdi + rcx], 0
		je	_done
		inc	rcx
		jmp	_strcmp_lol

_done:
		mov	al, BYTE [rdi + rcx]
		sub	rax, rdx
		pop rbp
		ret
