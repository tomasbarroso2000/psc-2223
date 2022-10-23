#include <stdio.h>
#include <string.h>

void string_reverse(char buffer[], size_t buffer_size);

size_t get_size(char buffer[]);

char* convert_decimal(int value, int base, char res[]) {
	int index = 0, temp = value;
	
	if(temp == 0) {
		res[index++] = temp + '0';
	}
	
	while(temp > 0) {
		
		if(temp % base >= 0 && temp % base <= 9)
			res[index++] = (temp % base) + '0';
		else 
			res[index++] = (temp % base) - 10 + 'a';
			
		temp /= base;
		
	}
	res[index] = '\0';
	return res;
}

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size) {
	if(base <= 0) return 0;
	
	int temp = value;
	if (temp == -1) {
		buffer[0] = '-';
		buffer[1] = '1';
		return get_size(buffer);
	}
	
	convert_decimal(value, base, buffer);
	size_t size = get_size(buffer);
	if(buffer_size <= size) return 0;
	string_reverse(buffer, size);
	return size;
}
