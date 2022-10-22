#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_find_substitute(char *string, char *string1, char *string2) {
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
