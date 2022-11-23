/*
	void rotate_right ( unsigned long value[], size_t n );
						rdi						rsi
												
			int i => %rbx
*/


	.text
	.global rotate_right
rotate_right:
	push %r12
	push %r13
	push %rcx
	
	mov $0, %r10
	mov (%rdi, %r10, 8), %r10
	mov $1, %r11
	mov (%rdi, %r11, 8), %r11
	
	mov %rsi, %r12
	cmp $64, %r12
	jae for
	jmp for_end
	
for:
for_cond:
	cmp $64, %r12
	jb for_end
	
	mov $0, %rcx
	mov (%rdi, %rcx, 8), %r10
	mov $1, %rcx
	mov (%rdi, %rcx, 8), %r11
	
	mov $0, %rcx
	mov %r11, (%rdi, %rcx, 8)
	mov $1, %rcx
	mov %r10, (%rdi, %rcx, 8)
	
	sub $64, %r12
	jmp for_cond
for_end:
	cmp $0, %r12
	je rotate_right_end
	
	mov $0, %rcx
	mov (%rdi, %rcx, 8), %r10
	mov $1, %rcx
	mov (%rdi, %rcx, 8), %r11
	
	mov %r12, %rcx
	mov %r10, %r13
	shrd %cl, %r11, %r10
	shrd %cl, %r13, %r11
	mov $0, %rcx
	mov %r10, (%rdi, %rcx, 8)
	mov $1, %rcx
	mov %r11, (%rdi, %rcx, 8)
	
rotate_right_end:
	pop %rcx
	pop %r13
	pop %r12
	ret
	.section .note.GNU-stack
	
