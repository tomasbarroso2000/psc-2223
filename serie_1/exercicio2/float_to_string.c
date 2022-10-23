#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int to_decimal(int value) {
	int binary = value, decimal = 0, base = 1, remainder;

    int temp = binary;
    while(temp > 0)
    {
        remainder = temp % 10;
        decimal = decimal + remainder * base;
        temp = temp / 10;
        base = base * pow(2, -1);
    }
    return decimal;
}

void string_reverse(char buffer[], size_t buffer_size);


size_t get_number_size(int number) {
	int value = number, total = 0;
	while(value != 0) {
		value /= 10;
		total++;
	}
	return total;
}

size_t get_size(char buffer[]);

int convert(int n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}

union Float {
	int integer;
	float real;
};

void print_bin(int x, int n) {
	unsigned mask = 1 << (n - 1);
	for (int i = 0; i < n; ++i, mask >>= 1)
		printf("%c", (x & mask) ? '1' : '0');
}

float get_mantisse(int value) {
	float dec = 0;
	int count = -1;
	
	unsigned mask = 1 << (22);
	for (int i = 0; i < 23; ++i, mask >>= 1) {
		if(value & mask) {
			dec += pow(2, count);
		}
		count--;
	}

	  return dec;
}

int int_to_str(int integer, int decimal, char str[], int buffer_size) {
	int size_decimal = get_number_size(decimal), count = 0, dcount = 0;
	if(decimal != 0) {
		while(decimal != 0) {
			str[dcount] = (decimal % 10) + '0';
			decimal /= 10;
			dcount++;
		}
	} else {
		while(buffer_size-3 > 0) {
			str[dcount] = '0';
			dcount++;
			buffer_size--;
		}
	}
	int temp = integer;
	str[dcount++] = '.';
	if(temp != 0) {
		while(temp != 0 ) {
			if((integer % 10) < 0) {
				str[count + dcount] = (temp % 10) * (-1) + '0';
			} else {
				str[count + dcount] = (temp % 10) + '0';
			}
			temp /= 10;
			count++;
		}
	} else {
		str[count + dcount] = '0';
	}
	
	if(integer < 0) { 
		str[count + dcount] = '-';
		size_decimal++;
	}
	int end_size = get_size(str);
	string_reverse(str, end_size);
	return end_size;
}

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
	if(buffer_size < 9) return 0;
	
	union Float b;
	b.real = value;
	
	int signal = ((b.integer >> 31) & 1);
	int exponent = (b.integer >> 23) & 0xff;
	float mantisse = get_mantisse(b.integer & 0x7fffff);
	
	if (signal == 0) signal = 1;
	else signal = -1;
	
	int value1 = signal * pow(2, exponent - 127) * (1 + mantisse);
	int decimal2 = (pow(2, exponent - 127) * (1 + mantisse) - (signal * value1)) * pow(10, 6);
	
	int result = int_to_str(value1, decimal2, buffer, buffer_size);
	
	return result;
}

