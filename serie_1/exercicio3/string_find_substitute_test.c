/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2022/2023
 *	Primeira série de exercícios
 *
 *	Programa de teste do 4º exercício
 *
 *	Utilização:
 *
 *	$ gcc string_find_substitute_test.c string_find_substitute.c -o string_find_substitute_test -g -Wall
 *
 *	$ ./string_find_substitute_test
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void string_find_substitute(char *string, char *string1, char *string2);

struct {
	char origin[100], *string1, *string2, *result;
} tests[] = {
	/* substituir uma ocorrência; dimensão igual */
	{
	"aaa bbb cccc\0xxxxxxxxxxxxxxxxx",
	"aaa b",
	"12345",
	"12345bb cccc",
	},
	/* substituir uma ocorrência; dimensão maior */
	{
		"aaa bbb cccc\0xxxxxxxxxxxxxxxxx",
		"aaa b",
		"1234567",
		"1234567bb cccc"
	},
	/* substituir uma ocorrência; dimensão menor */
	{
	"aaa bbb cccc\0xxxxxxxxxxxxxxxxx",
	"aaa b",
	"123",
	"123bb cccc",
	},
	/* substituir várias ocorrências; dimensão igual */
	{
	"aaa bbb ccccaaaa bb\0xxxxxxxxxxxxxxxxx",
	"aaa b",
	"12345",
	"12345bb cccca12345b",
	},
	/* substituir várias ocorrências; dimensão menor */
	{
	"aaa bbb ccccaaaa bb\0xxxxxxxxxxxxxxxxx",
	"aaa b",
	"123",
	"123bb cccca123b",
	},
	/* substituir várias ocorrências; dimensão maior */
	{
	"aaa bbb ccccaaaa bb\0xxxxxxxxxxxxxxxxx",
	"aaa b",
	"1234567",
	"1234567bb cccca1234567b",
	}
};

int error;

int main() {
	/*for (int i = 0; i < ARRAY_SIZE(tests); ++i) {
		string_find_substitute(tests[i].origin, tests[i].string1, tests[i].string2);
		if (strcmp(tests[i].origin, tests[i].result) == 0)
			;	//printf("[%d] - OK\n", i);
		else {
			printf("[%d] - Error, expected: %s, returned: %s\n",
					i, tests[i].origin, tests[i].result);
			error = 1;
		}
	}
	return error;*/
	char str[100] = "aaa b bb cccc\0xxxxxxxxxxxxxxxxx";
	char str1[10] = "aaa b";
	char str2[10] = "12345";
	printf("Before: %s\n", str);
	string_find_substitute(str, str1, str2);
	printf("After: %s\n", str);
}
