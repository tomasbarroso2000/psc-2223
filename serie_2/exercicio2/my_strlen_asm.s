/*
size_t my_strlen(const char str[]) {
size_t my_strlen(const char *str) {
                             rdi
	size_t i;
	       rax
	for (i = 0; str[i]; ++i)
	    ;
	return i;
}
*/
	.text
	.global my_strlen
my_strlen:
	mov	$0, %rax
	mov $0, %r9
for:
	mov $255, %r8
	mov	(%rdi, %rax, 8), %rcx
	
inner_for:
	cmp $0, %r8
	je inner_for_end
	mov %rcx, %r10
	and %r8, %r10
	cmp $0, %r10
	je for_end
	shl $8, %r8
	inc %r9
	jmp inner_for
inner_for_end:
	add	$1, %rax
	jmp	for
for_end:
	mov %r9, %rax 
	ret

	.section .note.GNU-stack
