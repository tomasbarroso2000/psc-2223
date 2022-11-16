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
for:
	mov	(%rdi, %rax, 4), %ecx
	cmp	$0, %ecx
	jz	for_end
	lea (%rdi, %rax, 4), %r8
	add	$1, %rax
	jmp	for
for_end:
	cmp $0, %rax
	jz	my_strlen_end
	
	mov $3, %r9
	mov $0, %r10
for2:
	mov	(%r8, %r9), %cl
	cmp	$0, %cl
	jnz my_strlen_end
	inc %r10
	dec %r9
	jmp for2
my_strlen_end:
	shl $2, %rax
	sub %r10, %rax
	ret

	.section .note.GNU-stack
