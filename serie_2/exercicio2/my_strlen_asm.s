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
	push %r12
	push %r13
	push %r14
	push %rcx
	 
	mov	$0, %rax					#rax = 0
	mov $0, %r12					#r12 = 0
for:
	mov $255, %r13					#r13 = 255
	mov	(%rdi, %r12, 8), %rcx		#rcx = str[r12]
	
inner_for:
	cmp $0, %r13					
	je inner_for_end				#r13 == 0
	mov %rcx, %r14					#r14 = rcx
	and %r13, %r14					#r14 = r14 & r13 => r14 & 0x00FF
	cmp $0, %r14					
	je for_end						#r14 == 0
	shl $8, %r13					#r13 << 256
	inc %rax						
	jmp inner_for
inner_for_end:
	inc	%r12					    #r12++
	jmp	for
for_end:
	
	pop %rcx
	pop %r14
	pop %r13
	pop %r12
	ret

	.section .note.GNU-stack
