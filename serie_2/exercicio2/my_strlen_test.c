#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

size_t my_strlen(const char *str);
#if 0
{
	int len;
	for (len = 0; str[len] != 0; ++len)
		;
	return len;
}
#endif

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);

struct {
	const char *string;
	size_t expected_len;
} test_array[] = {
	{"", 0},
	{"a", 1},
	{"aaa", 3},
	{"aaaaaaaaaaaaaaaaa", 17},
};

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		size_t received_result;
		int result = invoke_and_test(&received_result, (void (*)())my_strlen, 1,
			test_array[i].string);
		if (result != 0)
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
		size_t expected_result = strlen(test_array[i].string);
		if (received_result != expected_result)
			printf("expected_result: %zd, received_result: %zd\n",
				expected_result, received_result);
	}
}
