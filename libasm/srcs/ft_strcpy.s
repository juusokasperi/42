; ft_strcpy.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_strcpy)

; char *ft_strcpy(char *dst, const char *src)
; rdi = dst
; rsi = src

FN(ft_strcpy):
	; Copy the original dst to rax to be used as the return value
	mov rax, rdi

.loop:
	; Load byte from src to dl (lower 8 bits of rdx)
	mov dl, byte [rsi]
	; Store byte from dl into dst
	mov byte [rdi], dl
	; Check if we copied the null terminator
	cmp dl, 0
	je .done

	; Increment pointers
	inc rdi
	inc rsi
	jmp .loop

.done:
	; rax already holds the starting point of dst
	ret

GNU_STACK_NOTE
