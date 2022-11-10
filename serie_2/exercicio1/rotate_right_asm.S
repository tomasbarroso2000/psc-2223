/*
	void rotate_right ( unsigned long value[], size_t n );
						rdi						rdx:rsi
												rdx:rax
			int i => %rbx
*/


	.text
	.global rotate_right
rotate_right:
	push %r15
	mov %rsi, %rax
	mov $64, %rbx
	mov $0, %rdx
	div %rbx
	
for:
	mov $0, %rbx
	
for_cond:
	cmp %rax, %rbx
	jae for_end
	
	mov $0, %r8
	mov (%rdi, %r8, 8), %r9
	inc %r8
	mov (%rdi, %r8, 8), %r10
	mov %r9, (%rdi, %r8, 8)
	dec %r8
	mov %r10, (%rdi, %r8, 8)
	
	inc %rbx
	jmp for_cond
for_end:

	cmp $0, %rdx
	je rotate_end
	mov $0, %r8
	mov (%rdi, %r8, 8), %r9
	inc %r8
	mov (%rdi, %r8, 8), %r10
	mov %rdx, %rcx
	mov %r10, %r11
	shrd %cl, %r9, %r10
	shrd %cl, %r11, %r9
	mov %r10, (%rdi, %r8, 8)
	dec %r8
	mov %r9, (%rdi, %r8, 8)
	
rotate_end:
	pop %r15
	ret

	.section .note.GNU-stack
