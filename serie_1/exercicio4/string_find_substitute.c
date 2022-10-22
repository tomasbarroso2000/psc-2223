#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void string_find_substitute(char *string, char *string1, char *string2) {
	char buffer[100];
	int str1_len = strlen(string1);
	char *pch;
	pch = strstr (string, string1);
	while(pch) {
		strcat(buffer, string2);
		//buffer[pch - string] = '\0';
		for(int i = 0; i < pch - string; i++) {
			buffer[i] = string[i];
		}
		//strcat(buffer, (string[pch - string]));
		strcat(buffer, string2);
        strcat(buffer, pch + str1_len);
        strcpy(string, buffer);
        pch = strstr (string, string1);
	}
}*/

void string_find_substitute(char *string, char *string1, char *string2) {
	/*char buffer[100];
	int str1_len = strlen(string1);
	char *pch;
	pch = strstr (string, string1);
	while(pch) {
		pch = strstr (string, string1);
		strcat(buffer, string2);
		buffer[pch - string] = '\0';
		strcat(buffer, string2);
        strcat(buffer, pch + str1_len);
        strcpy(string, buffer);
        pch = strstr (string, string1);
	}*/
	char *p = strstr(string, string1);
    while (p != NULL) {
        size_t len1 = strlen(string1);
        size_t len2 = strlen(string2);
        if (len1 != len2)
            memmove(p + len2, p + len1, strlen(p + len1) + 1);
        memcpy(p, string2, len2);
        p = strstr(string, string1);
    }
}

/*int main() {
	char str[100] = "Aquele será o texto a ser substituido segunda linha";
	char w1[10] = "ele";
	char w2[10] = "ela";
	printf("Before: %s\n", str);
	string_find_substitute(str, w1, w2);
	printf("After: %s\n", str);
}*/
