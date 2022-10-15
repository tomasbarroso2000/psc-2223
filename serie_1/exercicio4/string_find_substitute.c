#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_find_substitute(char *string, char *string1, char *string2) {
	char buffer[100];
	int str1_len = strlen(string1);
	char *pch;
	pch = strstr (string, string1);
	while(pch) {
		strcat(buffer, string2);
		buffer[pch - string] = '\0';
		strcat(buffer, string2);
        strcat(buffer, pch + str1_len);
        strcpy(string, buffer);
        pch = strstr (string, string1);
	}
}


/*int main() {
	char str[100] = "aaa bbb cccc\0xxxxxxxxxxxxxxxxx";
	char w1[10] = "aaa b";
	char w2[10] = "123";
	printf("Before: %s\n", str);
	string_find_substitute_v2(str, w1, w2);
	printf("After: %s\n", str);
}*/
