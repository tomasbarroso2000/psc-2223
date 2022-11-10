/*
int multiple (const void *a, const void *b) {
	return (*(int *)a % *(int *)b) != 0;
}
*/

	.text
	.global	multiple
multiple:
	mov	(%rdi), %eax
	cltd
	idivl	(%rsi)
	test	%edx, %edx
	setne	%al
	movzbl	%al, %eax
	mov	$-1, %rdi
	mov	$-1, %rsi
	mov	$-1, %rdx
	mov	$-1, %rcx
	mov	$-1, %r8
	mov	$-1, %r9
	mov	$-1, %r10
	mov	$-1, %r11
	ret

	.section .note.GNU-stack
