; nasm_os_defs.inc

%ifidn __OUTPUT_FORMAT__, macho64
	; macOS config
	%define SYS_WRITE	0x2000004	; ID 4, class 2
	%define SYS_READ	0x2000003
	%define FN(x)		_ %+ x		; Helper: Prepend underscore
	%define ERRNO_FUNC	___error
	%define PLT(x)	x
	%define GNU_STACK_NOTE

	%macro CHECK_ERROR 1
		jc %1			; Jump if Carry to label %1
	%endmacro

	%macro PREPARE_ERRNO 0
						; Do nothing (rax is already positive)
	%endmacro

%elifidn __OUTPUT_FORMAT__, elf64
	; Linux config
	%define SYS_WRITE	1
	%define SYS_READ	0
	%define FN(x)		x
	%define ERRNO_FUNC	__errno_location
	%define PLT(x)	x wrt ..plt
	%define GNU_STACK_NOTE section .note.GNU-stack noalloc noexec nowrite
	%macro CHECK_ERROR 1
		cmp rax, 0
		jl %1
	%endmacro

	%macro PREPARE_ERRNO 0
		neg rax			; Linux returns negative, we need positive (negate it)
	%endmacro
%else
	%error "Unknown output format, use -f macho64 or -f elf64"
%endif
