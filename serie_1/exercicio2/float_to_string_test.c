/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2022/2023
 *	Primeira série de exercícios
 * 
 *	Programa de teste do 2º exercício
 * 
 *	Utilização:
 *
 *	$ gcc float_to_string_test.c float_to_string.c -o float_to_string_test -g -Wall
 * 
 *	$ ./float_to_string_test
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

size_t float_to_string(float value, char buffer[], size_t buffer_size);

struct {
	float value; char buffer[20]; size_t buffer_size;
	size_t result_size; char *result_string;
} test_array[] = {
	{.value = 3.5,  .buffer_size = 9,  .result_size = 8, .result_string = "3.500000"},
	{.value = -3.5, .buffer_size = 10, .result_size = 9, .result_string = "-3.500000"},
	{.value = 3.5,  .buffer_size = 3,  .result_size = 0},
	{.value = 3.5,  .buffer_size = 0,  .result_size = 0},
	{.value = 1.111111, .buffer_size = 9, .result_size = 8, .result_string = "1.111111"},
	{.value = 0.0,  .buffer_size = 9,  .result_size = 8, .result_string = "0.000000"},
};

void print_result(int i, size_t result_size) {
	if (result_size != test_array[i].result_size)
		printf("[%d] - Error, expected size = %zd, returned size = %zd\n",
			i, test_array[i].result_size, result_size);
	else if (result_size > 0 && strcmp(test_array[i].buffer, test_array[i].result_string) != 0)
		printf("[%d] - Error, expected string = %s, returned string = %s\n",
			i, test_array[i].result_string, test_array[i].buffer);
	else
		printf("[%d] - OK\n", i);
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		size_t result = float_to_string(test_array[i].value,
								test_array[i].buffer,
									test_array[i].buffer_size);
		print_result(i, result);
	}
}
