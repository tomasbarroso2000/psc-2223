
/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2022/2023
 *	Primeira série de exercícios
 *
 *	Programa de teste do 3º exercício
 *
 *	Utilização:
 *
 *	$ gcc mini_sprintf_test.c mini_sprintf.c ../utils.c ../exercicio1/int_to_string.c ../exercicio2/float_to_string.c -lm -o mini_sprintf
 *
 *	$ ./mini_sprintf
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int mini_sprintf(char *buffer, const char *format, ...);

typedef union {
	int i;
	float f;
	char c;
	char *s;
} Value;

struct {
	char buffer[20]; size_t buffer_size; char *format; Value values[4];
	size_t result_size; char *result_string;
} test_array[] = {
	{.buffer_size = 2, .format = "%d", .values = {2}, .result_size = 1, .result_string = "2"},
	{.buffer_size = 4, .format = "%d %c", .values = {2, 'a'}, .result_size = 3, .result_string = "2 a"},
	{.buffer_size = 11, .format = "aa %x bb %s", .values = {10, [1].s = "YY"}, .result_size = 10, .result_string = "aa a bb YY"},
	{.buffer_size = 4, .format = "%d %c", .values = {2, 'a'}, .result_size = 3, .result_string = "2 a"},

	/* Testes envolvendo floats */
	{.buffer_size = 9, .format = "%f", .values = {[0].f = 3.5}, .result_size = 8, .result_string = "3.500000"},
	{.buffer_size = 13, .format = "%s %f", .values = {[0].s = "aaa", [1].f = 4.4}, .result_size = 12, .result_string = "aaa 4.400000"},
};

int error;

void print_result(int i, size_t result_size) {
	if (result_size != test_array[i].result_size) {
		printf("[%d] - Error, expected size = %zd, returned size = %zd\n",
			i, test_array[i].result_size, result_size);
		error = 1;
	}
	else if (result_size > 0 && strcmp(test_array[i].buffer, test_array[i].result_string) != 0) {
		printf("[%d] - Error, expected string = %s, returned string = %s\n",
			i, test_array[i].result_string, test_array[i].buffer);
			error = 1;
	}
	else
		printf("[%d] - OK\n", i);
}


int main() {
	int i;
	size_t result;
	for (i = 0; i < ARRAY_SIZE(test_array) - 2; ++i) {
		result = mini_sprintf(test_array[i].buffer,
								test_array[i].format,
								test_array[i].values[0],
								test_array[i].values[1],
								test_array[i].values[2],
								test_array[i].values[3]);
		print_result(i, result);
	}

	i = ARRAY_SIZE(test_array) - 2;
	result = mini_sprintf(test_array[i].buffer,
								test_array[i].format,
								test_array[i].values[0].f,
								test_array[i].values[1]);
	print_result(i, result);
	i = ARRAY_SIZE(test_array) - 1;
	result = mini_sprintf(test_array[i].buffer,
							test_array[i].format,
							test_array[i].values[0],
							test_array[i].values[1].f);
	print_result(i, result);

	return error;
}
