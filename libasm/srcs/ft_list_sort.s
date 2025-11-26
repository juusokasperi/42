; ft_list_sort.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_list_sort)

; void ft_list_sort(t_list **begin_list, int (*cmp)())
; rdi = list head
; rsi = compare function

FN(ft_list_sort):
	push rbx
	push r12
	push r13
	push r14
	push r15

	; Null checks
	test rdi, rdi
	jz .done
	test rsi, rsi
	jz .done
	mov rax, [rdi]
	test rax, rax
	jz .done

	mov rbx, rdi	; Save begin_list pointer
	mov r13, rsi	; Save compare function pointer
	xor r12, r12	; sorted_list = null

; rbx -> begin_list pointer
; r13 -> compare function pointer
; r12 -> sorted_list (null)
; r14 -> detached node (first in begin_list so the unsorted list)
; r15 -> used as 'prev' node

.consume_unsorted:
	mov r14, [rbx]	; take the first node of begin_list
	test r14, r14	; check for NULL
	jz .done

	mov rax, [r14 + 8]		; r14->next into rax
	mov [rbx], rax			; move to rbx (so one is consumed)

	test r12, r12			; if sorted_list is empty, insert r14 to head
	jz .insert_at_head

	mov rdi, [r14]			; move contents of r14 to rdi
	mov rsi, [r12]			; move contents of r12 to rsi
	call r13				; compare
	cmp eax, 0
	jle .insert_at_head		; if 0 or smaller, insert r14 to head

	mov r15, r12			; use r15 as prev node
.scan_loop:
	mov rcx, [r15 + 8]		; rcx is the node we compare against
	test rcx, rcx			; check if null (would be at end of list)
	jz .insert_after_prev

	push rcx				; save rcx
	sub rsp, 8				; align stack
	mov rdi, [r14]
	mov rsi, [rcx]
	call r13				; compare the detached node against rcx
	add rsp, 8
	pop rcx
	cmp eax, 0
	jle .insert_after_prev	; if <= 0, we have found our insertion point

	mov r15, rcx			; otherwise, set rcx as prev node, call loop again
	jmp .scan_loop

.insert_at_head:
	mov [r14 + 8], r12		; detached_node->next points to sorted list head
	mov r12, r14			; detached_node becomes sorted list
	jmp .consume_unsorted

.insert_after_prev:
	mov rcx, [r15 + 8]		; temp = prev->next
	mov [r14 + 8], rcx		; detached->next = temp
	mov [r15 + 8], r14		; prev->next = detached
	jmp .consume_unsorted

.done:
	mov [rbx], r12
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret

GNU_STACK_NOTE
