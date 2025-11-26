; ft_write.s
%include "nasm_os_defs.inc"

section .text
	global FN(ft_write)	; Expands to _ft_write on macOS
	extern ERRNO_FUNC	; Expands correctly on macOS or Linux

; ssize_t ft_write(int fd, const void *buf, size_t count)
FN(ft_write):
	mov rax, SYS_WRITE
	syscall
	CHECK_ERROR .error
	ret

.error:
	PREPARE_ERRNO
	push rax
	call ERRNO_FUNC
	pop rdx
	mov [rax], edx
	mov rax, -1
	ret

GNU_STACK_NOTE
