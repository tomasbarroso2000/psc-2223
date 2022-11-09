#include <stdio.h>
#include <stdlib.h>

void rotate_right ( unsigned long value[], size_t n );

int main() {
	int i;
	unsigned long value[] = {0x0000000000000000, 0xAFD5923475892300};
	printf("Result before\n");
	for(i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
		printf("[%i] = 0x%.16lX\n", i, value[i]);
	}
	rotate_right(value, 64);
	printf("Result after\n");
	for(i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
		printf("[%i] = 0x%.16lX\n", i, value[i]);
	}
}
