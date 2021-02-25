global ft_strcmp
section .text:

ft_strcmp:
		push rbp
		mov rbp, rsp
		xor	rdx, rdx
		xor rcx, rcx

_strcmp:
		xor rax, rax
		mov dl, BYTE [rsi + rcx]
		cmp	BYTE [rdi + rcx], dl
		jne	_done
		cmp	BYTE [rsi + rcx], 0
		je	_done
		cmp	BYTE [rdi + rcx], 0
		je	_done
		inc	rcx
		jmp	_strcmp

_done:
		mov	al, BYTE [rdi + rcx]
		sub	rax, rdx
		pop rbp
		ret
