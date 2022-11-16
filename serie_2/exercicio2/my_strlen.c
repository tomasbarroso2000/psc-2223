#include <stdio.h> //remove when done
#include <stdlib.h>

/*size_t my_strlen(const char *string) {
	return strlen(string);
}*/

size_t my_strlen(const char *string);

char str1[100] = "";
char str2[100] = "a";
char str3[100] = "aaa";
char str4[100] = "aaaaaaaaaaaaaaaaa";

char *str[4] = {str1, str2, str3, str4};

int main() {
	/*char str1[20] = "";
	printf("size: %ld\n", my_strlen(str1));
	char str2[20] = "a";
	printf("size: %ld\n", my_strlen(str2));
	char str3[20] = "aaa";
	printf("size: %ld\n", my_strlen(str3));
	char str4[100] = "aaaaaaaaaaaaaaaaa";
	printf("size: %ld\n", my_strlen(str4));*/
	
	printf("size1: %ld\n", my_strlen(str[0]));
	printf("size2: %ld\n", my_strlen(str[1]));
	printf("size3: %ld\n", my_strlen(str[2]));
	printf("size4: %ld\n", my_strlen(str[3]));
}
