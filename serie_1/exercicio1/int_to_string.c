#include <stdio.h>
#include <string.h>

void string_reverse(char buffer[], size_t buffer_size);

/*void string_reverse(char buffer[], size_t buffer_size) {
	//int len = strlen(buffer);
	int size = buffer_size;
    for (size_t i = 0; i < size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
}*/

size_t get_size(char buffer[]);

/*size_t get_size(char buffer[]) {
	int result = 0, i;
	for(i = 0; buffer[i] != '\0'; i++) result++;
	return result;
}*/

char* convert_decimal(int value, int base, char res[]) {
	int index = 0, temp = value;
	//int is_negative = 0;
	
	if(temp == 0) {
		res[index++] = temp + '0';
	}
	
	while(temp > 0) {
		
		/*if(temp % base >= 8 && index == 0) {
			res[index++] = '-';
		} */
		
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

/*void test_ex1() {
	
	//Testing decimal conversions
	
	//Test 1 with octal value - expected result is 234
	char buffer1[3];
	size_t result = int_to_string(156, 8, buffer1, 4);
	printf("\nTest1: %ld \n", result);
	printf("\n Content Buffer 1: %s \n", buffer1);
	
	//Test 2 with binary value - expected result is 10101010
	char buffer2[3];
	size_t result2 = int_to_string(170, 2, buffer2, 9);
	printf("\nTest2: %ld \n", result2);
	printf("\n Content Buffer 2: %s \n", buffer2);
	
	//Test 3 with hexadecimal value - expected result is 0xAB
	char buffer3[3];
	size_t result3 = int_to_string(171, 16, buffer3, 3);
	printf("\nTest3: %ld \n", result3);
	printf("\n Content Buffer 3: %s \n", buffer3);
	
	//Test 4 with the use of the requested function int_to_string  - expected result is 352
	char buffer4[4];
	size_t result4 = int_to_string(234, 8, buffer4, 4);
	printf("\nTest4: %ld \n", result4);
	printf("\n Content Buffer 4: %s \n", buffer4);
}
*/
/*
int main(){
	char buffer2[3];
	size_t result2 = int_to_string(10, 2, buffer2, 9);
	printf("\nTest2: %ld \n", result2);
	printf("\n Content Buffer 2: %s \n", buffer2);
	
	return 0;
}*/
