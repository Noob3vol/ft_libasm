global ft_strlen
section .text

inc_bit:
	inc rax
	jmp count_bit

ft_strlen:
	xor rax, rax

count_bit:
	cmp BYTE [rdi + rax], 0
	jne inc_bit
	ret
