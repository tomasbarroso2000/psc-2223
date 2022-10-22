#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void string_reverse(char buffer[], size_t buffer_size) {
	//int len = strlen(buffer);
	int size = buffer_size;
    for (size_t i = 0; i < size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
}

size_t get_size(char buffer[]) {
	int result = 0, i;
	for(i = 0; buffer[i] != '\0'; i++) result++;
	return result;
}
