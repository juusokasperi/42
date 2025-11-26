%include "nasm_os_defs.inc"
section .text
	global FN(ft_strlen)

; Input: rdi = pointer to null-terminated string
; Ouptut: rax = length of the string
; Safe version (NULL check at beginning)
; Removing the null check at beginning would match real strlen

; size_t ft_strlen(const char *str);
FN(ft_strlen):
	xor rax, rax	; Set rax to 0
	test rdi, rdi	; `if (!str)` check
	jz done			; Jump to done if str was null
	mov rax, rdi 	; Copy the start address (rdi) into rax (to use as iterator)
	jmp check_null	; Jump to the null check FIRST

next_char:
	inc rax		; Increment rax address

check_null:
	cmp byte [rax], 0	; Check the byte
	jne next_char
	sub rax, rdi ; Calculate length, current address (rax) - start address (rdi)

done:
	ret

GNU_STACK_NOTE
