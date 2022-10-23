#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void string_reverse(char buffer[], size_t buffer_size);
size_t get_size(char buffer[]);

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size);
size_t float_to_string(float value, char buffer[], size_t buffer_size);

int mini_sprintf(char *str, const char *format, ...) {
	va_list ap;
	int count = 0;
	char cval;
	char *p, *sval; 
	int ival; 
	double dval; 
	va_start(ap, format);
	int normal_len = 0;
	for (; *format; format++) { 
		char temp[100] = "";
		int result = 0;
		if (*format != '%') { 
			temp[0] = *format;
			strcat(str, temp);
			count += 1;
		 continue; 
		} 
		 switch (*++format) { 
			case 'd': 
				 ival = va_arg(ap, int); 
				 result = int_to_string(ival, 10, temp, sizeof ival);
				 count += result;
				 strcat(str, temp);
				break; 
			case 'f': 
				 dval = va_arg(ap, double); 
				 result = float_to_string(dval, temp, 9);
				 count += result;
				 strcat(str, temp);
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
				break; 
			}
			case 'x':
				ival = va_arg(ap, int); 
				result = int_to_string(ival, 16, temp, sizeof ival);
				count += result;
				strcat(str, temp);
				break;
			 default: 
				putchar(*p); 
				break; 
		} 
	}
	 va_end(ap); 
	 return count; 
}
