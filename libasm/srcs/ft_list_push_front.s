; ft_list_push_front.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_list_push_front)

; void	ft_list_push_front(t_list **lst, t_list *new)
; rdi = lst (pointer to head pointer)
; rsi = new (pointer to new node)
FN(ft_list_push_front):
	test rsi, rsi			; if (!new) return;
	jz .done
	test rdi, rdi			; if (!lst) return;
	jz .done

	mov rcx, [rdi]			; move (*lst) into rcx
	mov [rsi + 8], rcx		; move rcx into new->next
	mov [rdi], rsi			; write the address of new into the memory at lst

.done:
	ret

GNU_STACK_NOTE
