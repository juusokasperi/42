; ft_read.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_read)	; Expands to _ft_read on macOS
	extern ERRNO_FUNC	; Expands correctly on macOS or Linux

; ssize_t ft_read(int fd, const void *buf, size_t count)
FN(ft_read):
	mov rax, SYS_READ
	syscall
	CHECK_ERROR .error
	ret

.error:
	PREPARE_ERRNO
	push rax
	call PLT(ERRNO_FUNC)
	pop rdx
	mov [rax], edx
	mov rax, -1
	ret

GNU_STACK_NOTE
