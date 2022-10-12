#include <stdio.h>
#include <string.h>

/*void string_find_substitute(char *string, char *string1, char *string2) {
	char *find;
	find = strstr(string, string1);
	int str2_len = strlen(string2);
	while (find != NULL) {
		memcpy(find, string2, str2_len);
		find = strstr(string, string1);
	}
}*/

int str_split(char *string, char *delim, char *result[]) {
	int count = 0;
	char *ptr = strtok(string, delim);

	while(ptr != NULL) {
		result[count] = ptr;
		count++;
		ptr = strtok(NULL, delim);
	}
	return count;
}

void string_find_substitute(char *string, char *string1, char *string2) {
	/*char delim[] = " ";
	char result[100] = "";
	char *ptr = strtok(string, delim);

	while(ptr != NULL)
	{
		if(strcmp(ptr, string1) == 0) {
			printf("'%s'\n", ptr);
			printf("equal\n");
			strcat(result, string2);
			//memcpy(result, string2, sizeof(string2));
		} else {
			printf("'%s'\n", ptr);
			printf("not equal %ld \n",sizeof(ptr));
			//memcpy(result, ptr, sizeof(string2));
			strcat(result, ptr);
		}
		ptr = strtok(NULL, delim);
	}
	memmove(string, result, sizeof(string));*/
	char result[100] = "";
	char *final[100] = {};
	char delimiter[2] = " ";
	int size = str_split(string, delimiter, final);
	for(int i = 0; i < size; i++) {
		
		if(!strcmp(final[i], string1)) {
			//strcpy(result, string2);
			strcat(result, string2);
			//printf("sub\n");
		} else {
			//strcpy(result, final[i]);
			strcat(result, final[i]);
			//printf("not sub\n");
		}
		
		if(i < size - 1) {
			strcat(result, delimiter);
		}
		
	}
	strcpy(string, result);
}

/*int main() {
	char str[30] = "Hello big World";
	char str1[10] = "big";
	char str2[10] = "small";
	printf("Before: %s\n", str);
	string_find_substitute(str, str1, str2);
	printf("After: %s\n", str);
	//char *final[100];
	char str[30] = "Hello big World";
	char delimiter[2] = " ";
	
	int result = str_split(str, delimiter, final);
	printf("result: %d\n", result);
	for(int i = 0; i < result; i++) {
		printf("word %d: %s\n", i, final[i]);
	}
	return 0;
}*/
