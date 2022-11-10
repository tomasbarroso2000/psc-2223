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
	mov	(%rdi, %rax), %cl
	cmp	$0, %cl
	jz	for_end
	add	$1, %rax
	jmp	for
for_end:
	ret

	.section .note.GNU-stack
