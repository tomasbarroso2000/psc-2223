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
	
	mov $0, %r10					#r10 = 0
	mov (%rdi, %r10, 8), %r10		#r10 = value[0]
	mov $1, %r11					#r11 = 1
	mov (%rdi, %r11, 8), %r11		#r11 = value[1]
	
	mov %rsi, %r12					#r12 = rsi	
	cmp $64, %r12					
	jb for_end							#r12 < 64
	
	#caso n seja maior ou igual a 128
for_cond:
	cmp $64, %r12					
	jb for_end						#r12 < 64
	
	mov $0, %rcx					#rcx = 0
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
	
	mov $0, %rcx					#rcx = 0
	mov (%rdi, %rcx, 8), %r10		#r10 = value[0]
	mov $1, %rcx					#rcx = 1
	mov (%rdi, %rcx, 8), %r11		#r11 = value[1]
	
	mov %r12, %rcx					#rcx = r12 = n - 64					
	mov %r10, %r13					#r13 = r10 = value[0]
	shrd %cl, %r11, %r10			#rotate to r10
	shrd %cl, %r13, %r11			#rotate to r11
	mov $0, %rcx					#rcx = 0
	mov %r10, (%rdi, %rcx, 8)		#value[0] = r10
	mov $1, %rcx					#rcx = 1
	mov %r11, (%rdi, %rcx, 8)		#value[1] = r11
	
rotate_right_end:
	pop %rcx
	pop %r13
	pop %r12
	ret
	.section .note.GNU-stack
	
