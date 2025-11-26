; ft_atoi_base.s
%include "nasm_os_defs.inc"

%macro CHECK_FORBIDDEN_CHARS 1	; Check for +, -, whitespace
	; Argument %1 is the register to check
	cmp %1, 43		; +
		je .error
	cmp %1, 45		; -
		je .error
	JUMP_IF_SPACE %1, .error
%endmacro

%macro JUMP_IF_SPACE 2
	; Arg %1 is the register to check
	; Arg %2 is the label to jump to if it IS a space
	cmp %1, 32		; Space
		je %2
	cmp %1, 9		; If less than 9, not space
		jl %%not_space
	cmp %1, 13		; If greater than 13, not space
		jg %%not_space
	jmp %2			; If we got here, it is a space
%%not_space:
	; Fall through if not space
%endmacro

section .text
	global FN(ft_atoi_base)

; int ft_atoi_base(const char *str, const char *base);
; rdi = str
; rsi = base

FN(ft_atoi_base):
	test rdi, rdi		; NULL checks
	jz .error
	test rsi, rsi
	jz .error

	push rdi
	push rsi
	call _check_base
	pop rsi
	pop rdi

	cmp rax, 0
	je .error

	mov r8, rax		; save the length of base to r8 for math
	mov r10, 1		; store the sign
	xor rax, rax	; initialize rax to 0

.skip_whitespace:
	mov r9b, byte [rdi]
	JUMP_IF_SPACE r9b, .inc_ws
	jmp .check_signs

.inc_ws:
	inc rdi
	jmp .skip_whitespace

.check_signs:
	mov r9b, byte [rdi]
	cmp r9b, '+'
	je .next_sign
	cmp r9b, '-'
	jne .convert_loop
	neg r10
.next_sign:
	inc rdi
	jmp .check_signs

.convert_loop:
	movzx rdx, byte [rdi]	; Load char from number string to rdx
	test rdx, rdx
	je .done

	; Since everything is stored in scratch registers,
	; save them to stack before calling helper function
	push rdi				; Current position
	push r8					; Base length
	push r10				; Sign
	push rax				; Current result

	mov dil, dl				; Arg 1 (character to find, dil = first byte of rdi)
							; Arg 2 (rsi (base) is already in correct register)
	call _get_base_index
	mov rcx, rax			; Move the found index to rcx so we can pop the result back to rax

	pop rax
	pop r10
	pop r8
	pop rdi

	cmp rcx, -1				; Was the index found in base?
	je .done				; If -1, it was not, return

	; MATH part
	; Formula: result = (result * base_len) + index
	; Registers; rax = result, r8 = len, rcx = index
	imul rax, r8			; rax * r8
	add rax, rcx			; rax + rcx
	inc rdi
	jmp .convert_loop

.done:
	imul rax, r10			; result * sign (1 or -1)
	ret

.error:
	xor rax, rax
	ret

; =================================================
; --------------- GET_BASE_INDEX ------------------
; Helper function for finding the index of the char
; in base str. Returns -1 on fail, index on success
; =================================================

; In:  dil (char), rsi (base string)
; Out: rax (index or -1)
_get_base_index:
	xor rcx, rcx		; i = 0

.search_loop:
	mov al, byte [rsi + rcx]
	cmp al, 0
	je .not_found
	cmp al, dil
	je .found
	inc rcx
	jmp .search_loop

.found:
	mov rax, rcx
	ret

.not_found:
	mov rax, -1
	ret

; =================================================
; ------------------- CHECK_BASE ------------------
; Helper function for checking the validity of base
; Returns 0 on failure, length of base on success
; =================================================

_check_base:
	xor rcx, rcx	; i =0

.outer_loop:
	mov al, byte [rsi + rcx]
	cmp al, 0
	je .success
	CHECK_FORBIDDEN_CHARS al
	mov rdx, rcx
	inc rdx

.inner_loop:
	mov bl, byte [rsi + rdx]	; base[j]
	cmp bl, 0					; if base[j] === 0, at end of string
	je .next_outer_char
	cmp al, bl					; check for duplicate characters
	je .error
	inc rdx
	jmp .inner_loop

.next_outer_char:
	inc rcx
	jmp .outer_loop

.success:
	cmp rcx, 2
	jl .error
	mov rax, rcx
	ret

.error:
	xor rax, rax
	ret

GNU_STACK_NOTE
