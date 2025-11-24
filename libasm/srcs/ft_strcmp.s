; ft_strcmp.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_strcmp)

; int ft_strcmp(const char *s1, const char *s2)
; rdi = s1
; rsi = s2

FN(ft_strcmp):
	xor rax, rax ; Clear rax

.loop:
	mov al, byte [rdi]	; Load char from s1
	mov dl, byte [rsi]	; Load char from s2

	cmp al, 0			; Check for end of s1
	je .done			; 	If 0, exit

	cmp al, dl			; Compare the characters al and dl
	jne .done			;	If different, exit

	inc rdi				; al != 0 && al == dl, continue.
	inc rsi
	jmp .loop

.done:
	movzx eax, al
	movzx edx, dl
	sub eax, edx
	ret
