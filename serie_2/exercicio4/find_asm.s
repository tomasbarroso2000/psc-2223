/*
size_t find (void *array, size_t array_size, size_t elem_size,
		int (*predicate)(const void *, const void *), const void *context,
		void *result[], size_t result_size ) {
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

	ret

	.section .note.GNU-stack
