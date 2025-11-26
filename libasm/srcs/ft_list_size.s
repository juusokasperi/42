; ft_list_size.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_list_size)

; int ft_list_size(t_list *lst)
; rdi = lst (pointer to current node)
FN(ft_list_size):
	xor rax, rax		; Set rax to 0

.size_loop:
	test rdi, rdi		; if (!lst)
	jz .end
	inc rax
	mov rdi, [rdi + 8]	; lst = lst->next
	jmp .size_loop

.end:
	ret

GNU_STACK_NOTE
