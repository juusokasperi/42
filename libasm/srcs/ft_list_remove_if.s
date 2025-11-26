; ft_list_remove_if.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_list_remove_if)
	extern FN(free)

; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
; rdi = begin_list
; rsi = data_ref
; rdx = cmp
; rcx = free_fct

FN(ft_list_remove_if):
	; Save the preserved registers to stack
	; Our stack is now aligned
	push rbx
	push r12
	push r13
	push r14
	push r15

	; Save our variables to preserved registers
	mov r12, rdi
	mov r13, rsi
	mov r14, rdx
	mov r15, rcx

	test r12, r12	; Check if begin_list is NULL
	jz .done

.loop:
	mov rbx, [r12]	; rbx = *cursor (current node)
	test rbx, rbx	; Are we at the end of list?
	jz .done

	mov rdi, [rbx]	; arg1 = curr->data
	mov	rsi, r13	; arg2 = data_ref
	call r14		; call cmp(curr->data, data_ref)

	test rax, rax		; Check result
	jz .remove_node		; if 0 -> match, remove.
	lea r12, [rbx + 8]	; cursor = &curr->next
	jmp .loop

.remove_node:
	mov rax, [rbx + 8]	 ; rax = curr->next
	mov [r12], rax		 ; *cursor = curr->next
	test r15, r15
	jz .free_node

	mov rdi, [rbx]		; arg1 = curr->data
	call r15			; call free_fct(data)

.free_node:
	mov rdi, rbx		; arg1 = current node
	call PLT(FN(free))	; call free(curr)

	jmp .loop

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret

GNU_STACK_NOTE
