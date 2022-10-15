#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void string_reverse(char buffer[], size_t buffer_size);
size_t get_size(char buffer[]);

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size);
size_t float_to_string(float value, char buffer[], size_t buffer_size);

int mini_sprintf(char *str, const char *format, ...) {
	va_list ap; /* points to each unnamed arg in turn */ 
	int count = 0;
	char cval;
	char *p, *sval; 
	int ival; 
	double dval; 
	va_start(ap, format); /* make ap point to 1st unnamed arg */
	for (; *format; format++) { 
		if (*format != '%') { 
		 putchar(*format); 
		 continue; 
		} 
		char temp[100] = "";
		int result = 0;
		 switch (*++format) { 
			case 'd': 
				 ival = va_arg(ap, int); 
				 result = int_to_string(ival, 10, temp, sizeof ival);
				 count += result;
				 strcat(str, temp);
				 printf("Result d: %d\n", result);
				break; 
			case 'f': 
				 dval = va_arg(ap, double); 
				 result = float_to_string(dval, temp, 9);
				 count += result;
				 strcat(str, temp);
				 printf("Result f: %d\n", result);
				 break; 
			case 'c': 
				 cval = va_arg(ap, int); 
				 temp[0] = cval;
				 count += 1;
				 strcat(str, temp);
				 break; 
			case 's': {
				int size = 0;
				for (sval = va_arg(ap, char *); *sval; sval++, size++) {
					temp[size] = *sval;
				}
				count += size;
				strcat(str, temp);
				printf("Result s: %d\n", size);
				break; 
			}
			case 'x':
				ival = va_arg(ap, int); 
				result = int_to_string(ival, 16, temp, sizeof ival);
				count += result;
				strcat(str, temp);
				printf("Result x: %d\n", result);
				break;
			 default: 
				putchar(*p); 
				break; 
		} 
		strcat(str, " ");
		count++;
	} 
	 va_end(ap); /* clean up when done */ 
	 return count - 1; //contabilizar o espaço dado a mais quando se escreve no buffer quando é o ultimo valor
}

int main() {
	printf("Hello World\n");
	char temp[100] = "";
	char format[100] = "%x %d %c %s %f";
	int res = mini_sprintf(temp, format, 10, 2, 'H', "Hello C", 4.4);
	printf("End: %s\n", temp);
	printf("Size total: %d", res);
}
