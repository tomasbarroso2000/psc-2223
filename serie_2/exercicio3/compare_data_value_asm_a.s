/*
int compare_data_value ( Dataset *set1, Dataset *set2, unsigned index ) {
								%rdi			%rsi		%rdx
	if (index >= set1->length || index >= set2->length
		|| NULL == set1->data[index] || NULL == set2->data[index])
		return -1;
	return set1->data[index]->value == set2->data[index]->value;
}
*/

	.text
	.global	compare_data_value
	.equ length, 8
	.equ data, 16
	.equ NULL, 0
	.equ value, 8
compare_data_value:
	mov %rdx, %rcx
	mov length(%rdi), %r8
	cmp %rdx, %r8
	jb compare_data_value_end_error
	mov length(%rsi), %r8
	cmp %rdx, %r8
	jb compare_data_value_end_error
	mov data(%rdi), %r8
	mov (%r8, %rdx, 8), %r9 
	cmp $NULL, %r9
	je compare_data_value_end_error
	mov data(%rsi), %r8
	mov (%r8, %rdx, 8), %r10
	cmp $NULL, %r10
	je compare_data_value_end_error
	
	mov value(%r9), %r9
	mov value(%r10), %r10
	cmp %r9, %r10
	je end_with_one
	mov $0, %rax
	jmp end
end_with_one:
	mov $1, %rax
	jmp end
compare_data_value_end_error:
	mov $-1, %rax 
end:
	ret
	.section .note.GNU-stack
