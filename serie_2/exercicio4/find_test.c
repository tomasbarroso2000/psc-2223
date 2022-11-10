#include <stdio.h>
#include <string.h>

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };
int invoke_and_test(void *, void (*)(), int, ...);

#define ARRAY_SIZE(a)	(sizeof(a)/sizeof(a[0]))

size_t find(void *array, size_t array_size, size_t elem_size,
	int (*predicate)(const void *, const void *), const void *context,
	void *result[], size_t result_size);

int ints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int *result[ARRAY_SIZE(ints)];

#if 1
int multiple (const void *a, const void *b);
#else
int multiple (const void *a, const void *b) {
	return (*(int *)a % *(int *)b) != 0;
}
#endif


int mmc = 3;

struct {
	int *array;
	size_t array_size;
	int *result[10];
	size_t result_size;
	int *expected_result[10];
	size_t expected_result_size;
} test_array[] = {
	{ ints, ARRAY_SIZE(ints), {}, ARRAY_SIZE(result), {&ints[0], &ints[3], &ints[6], &ints[9]}, 4 },
	{ ints, ARRAY_SIZE(ints), {}, 3, {&ints[0], &ints[3], &ints[6]}, 3 },
	{ ints, ARRAY_SIZE(ints), {}, 1, {&ints[0]}, 1 },
	{ ints + 1, ARRAY_SIZE(ints) - 1, {}, ARRAY_SIZE(result), {&ints[3], &ints[6], &ints[9]}, 3 },
	{ ints + 1, 2, {}, ARRAY_SIZE(result), {}, 0 },
};

int error;

void print_result(size_t i, size_t result_size) {
	if (result_size != test_array[i].expected_result_size) {
		printf("[%zd] - Error, expected size = %zd, returned size = %zd\n",
			i, test_array[i].expected_result_size, result_size);
		error = 1;
	}
	else {
		for (size_t j = 0; j < test_array[i].expected_result_size; ++j)
			if (test_array[i].result[j] != test_array[i].expected_result[j]) {
				printf("[%zd] - result[%zd] = %p, expected_result[%zd] = %p\n",
					i, j, test_array[i].result[j], j, test_array[i].expected_result[j]);
				error = 1;
			}
	}
//	else
//		printf("[%d] - OK\n", i);
}

#if 0

int main() {
	size_t n_match;
	int result = invoke_and_test(&n_match, (void (*)())find, 7,
		test_array[0].array, test_array[0].array_size, sizeof(test_array[0].array[0]),
		multiple, &mmc,
		(void **)test_array[0].result, test_array[0].result_size);
}
#endif

#if 1
int main () {
	for (size_t i = 0; i < ARRAY_SIZE(test_array); ++i) {
		size_t n_match;
		int result = invoke_and_test(&n_match, (void (*)())find, 7,
			test_array[i].array, test_array[i].array_size, sizeof(test_array[i].array[0]),
			multiple, &mmc,
			(void **)test_array[i].result, test_array[i].result_size);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
			error = 1;
			break;
		}
		print_result(i, n_match);
	}
	return error;
}

#endif
