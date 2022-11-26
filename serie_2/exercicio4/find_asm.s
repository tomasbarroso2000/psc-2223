/*
size_t find (void *array, size_t array_size, size_t elem_size,
					%rdi			%rsi				%rdx
		int (*predicate)(const void *, const void *), const void *context,
				%rcx												%r8
		void *result[], size_t result_size ) {
				%r9					%r10
	char *iter, *last = (char *)array + array_size * elem_size;
	void **result_iter = result;
	for (iter = array; iter < last ; iter += elem_size) {
		if (predicate(iter, context) == 0) {
			*result_iter++ = iter;
			if (--result_size == 0)
				break;
		}
	}
	return result_iter - result;
}
*/


	.text
	.global	find
find:
	push %rbx
	push %rbp
	push %r12
	push %r13
	push %r14
	push %r15
	
	mov $0, %rax
	mov %rdi, %rbx		/*array*/
	mov %rsi, %rbp		/*array_size*/
	mov %rdx, %r12		/*elem_size*/
	mov %rcx, %r13		/*predicate*/
	mov %r8, %r14		/*context*/
	mov %r9, %r15		/*result*/
	mov 56(%rsp), %r10	/*result_size*/
	
	dec %rbp
	mov %r12, %rax
	mul %rbp
	lea (%rbx, %rax), %r8	/* last */
	lea (%r15), %r9 		/*result_iter*/
	
for:
	mov %rbx, %r11			/*iter = array*/
for_cond:
	cmp %r8, %r11
	jg for_end
	
	mov %r11, %rdi
	mov %r14, %rsi
	
	push %r8
	push %r9
	push %r10
	push %r11
	call *%r13			/*predicate*/
	pop %r11
	pop %r10
	pop %r9
	pop %r8
	
if:
	cmp $0, %rax
	jne if_end
	lea (%r9), %rdx		/*result_iter*/
	mov %r11, (%rdx)	/*result_iter = iter*/
	lea 8(%rdx), %r9	/*result_iter++*/
	
	dec %r10			/*--result_size*/
	cmp $0, %r10		
	je for_end
if_end:
	
	add %r12, %r11		/*iter += elem_size*/
	jmp for_cond
for_end:
	mov %r9, %rax
	sub %r15, %rax
	shr $3, %rax
	
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbp
	pop %rbx
	
	ret

	.section .note.GNU-stack
