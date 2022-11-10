#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

const char *register_name[] = { "", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);

extern void rotate_right(unsigned long value[], size_t n);

struct {
	unsigned nbits;
	unsigned long input[2];
	unsigned long output[2];
} test_array[] = {
	{4, {0xAFD5923475892300, 0xA629783EDF00B434},
	    {0x4AFD592347589230, 0x0A629783EDF00B43} },

	{64, {0xAFD5923475892300, 0xA629783EDF00B434},
	     {0xA629783EDF00B434, 0xAFD5923475892300} },

	{68, {0xAFD5923475892300, 0xA629783EDF00B434},
	     {0x0A629783EDF00B43, 0x4AFD592347589230} },
};

int main() {
	for (size_t i = 0; i < ARRAY_SIZE(test_array); i++) {
		unsigned long value[] = {test_array[i].input[0], test_array[i].input[1]};
		size_t received_result;
		int result = invoke_and_test(&received_result, (void (*)())rotate_right, 2,
						value, test_array[i].nbits);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
			break;
		}
		if (value[0] != test_array[i].output[0] || value[1] != test_array[i].output[1]) {
			printf("\nBefore:   %016lx %016lx\n", test_array[i].input[1], test_array[i].input[0]);
			printf("After:    %016lx %016lx\n", value[1], value[0]);
			printf("Expected: %016lx %016lx\n", test_array[i].output[1], test_array[i].output[0]);
		}
	}
}

