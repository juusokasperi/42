; ft_strdup.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_strdup)
	extern FN(ft_strlen)
	extern FN(ft_strcpy)
	extern FN(malloc)

; char *ft_strdup(const char *s1);
; rdi = src

FN(ft_strdup):
	push rdi					; push s1 to stack to save it
	call FN(ft_strlen)			; rax = length of s1
	inc rax						; len + 1 for NULL terminator
	mov rdi, rax				; argument for malloc (size)
	call PLT(FN(malloc))	; rax = new ptr or 0 if failed
	cmp rax, 0
	je .error					; if 0, malloc failed

	mov rdi, rax				; put new pointer in rdi (dst for strcpy)
	pop rsi						; pop s1 from stack to rsi (src for strcpy)
	call FN(ft_strcpy)
	ret

.error:
	; Malloc failed
	pop rdi				; Clear s1 from stack
	ret					; malloc has already set rax to 0

GNU_STACK_NOTE
