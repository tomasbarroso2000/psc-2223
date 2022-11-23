#include <stdio.h>

#include "dataset_a.h"

const char *register_name[] = { "", "rbp", "rbx", "r15", "r14", "r13", "r12" };

int invoke_and_test(void *, void (*)(), int, ...);

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

Data zero = { "zero", 0 };
Data um = { "um", 1 };
Data dois = { "dois", 2 };
Data tres = { "tres", 3 };
Data quatro = { "quatro", 4 };
Data cinco = { "cinco", 5 };
Data seis = { "seis", 6 };
Data sete = { "sete", 7 };
Data oito = { "oito", 8 };
Data nove = { "nove", 9 };
Data dez = { "dez", 10 };
Data onze = { "onze", 11 };
Data doze = { "doze", 12 };
Data treze = { "treze", 13 };

Data *pares[] =   { &zero, &dois, &quatro, &seis,  &oito, &dez,  &doze };
Data *impares[] = { &um,   &tres, &cinco,  &sete,  &nove, &onze, &treze };
Data *primos[] =  { &um,   &dois, &tres,   &cinco, &sete, &onze, &treze };

int dummy;

Dataset sets[] = {
	{&dummy, ARRAY_SIZE(pares), pares },
	{&dummy, ARRAY_SIZE(impares), impares },
	{&dummy, ARRAY_SIZE(primos), primos },
};

struct {
	Dataset *set1, *set2;
	unsigned index;
	int expected_result;
} test_array[] = {
	{&sets[0], &sets[2], 1, 1},
	{&sets[0], &sets[2], 3, 0},
	{&sets[1], &sets[2], 5, 1},
	{&sets[1], &sets[2], 6, 1},
	{&sets[1], &sets[2], 4, 0},
};

int compare_data_value ( Dataset *set1, Dataset *set2, unsigned index );

int main() {
	for (size_t i = 0; i < ARRAY_SIZE(test_array); i++) {
		int received_result;
		int result = invoke_and_test(&received_result, (void (*)())compare_data_value,
					3, test_array[i].set1, test_array[i].set2, test_array[i].index);
		if (result != 0) {
			printf("Your function currupted %s, that is a calee saved register\n",
				register_name[result]);
			break;
		}
		if (received_result != test_array[i].expected_result) {
			printf("[%zd] - Received: %d Expected: %d\n",
				i, received_result, test_array[i].expected_result);
		}
	}
}
