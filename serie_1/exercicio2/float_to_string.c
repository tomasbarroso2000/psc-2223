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

void string_reverse(char buffer[], size_t buffer_size) {
	//int len = strlen(buffer);
	int size = buffer_size;
    for (size_t i = 0; i < size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
}

size_t get_number_size(int number) {
	int value = number, total = 0;
	while(value != 0) {
		value /= 10;
		total++;
	}
	return total;
}

size_t get_size(char buffer[]) {
	int result = 0, i;
	for(i = 0; buffer[i] != '\0'; i++) result++;
	return result;
}

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
	//printf("\nCount: %d\n", count);
	
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
	//printf("number_size: %d \n", size);
	
	//printf("Integer number %d | size: %ld\n", integer, get_number_size(integer));
	//printf("Decimal %d | size: %ld\n", decimal, get_number_size(decimal));
	if(decimal != 0) {
		while(decimal != 0) {
			str[dcount] = (decimal % 10) + '0';
			decimal /= 10;
			dcount++;
		}
	} else {
		//remove from buffer size comma, integer part and terminator \n
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
			//printf("divide %d\n", (temp % 10));
			if((integer % 10) < 0) {
				str[count + dcount] = (temp % 10) * (-1) + '0';
			} else {
				str[count + dcount] = (temp % 10) + '0';
			}
			//integer /= 10;
			temp /= 10;
			count++;
		}
	} else {
		str[count + dcount] = '0';
	}
	//printf("Integer number %d | size: %ld\n", integer, get_number_size(integer));
	if(integer < 0) { 
		str[count + dcount] = '-';
		size_decimal++;
	}
	int end_size = get_size(str);
	//printf("middle string before: %s\n", str);
	string_reverse(str, end_size);
	//printf("middle string: %s\n", str);
	
	
	//printf("Final str: %s\n", str);
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
	
	//printf("\nResultf_to_str %d : %d \n", value1, decimal2);
	
	int result = int_to_str(value1, decimal2, buffer, buffer_size);
	
	return result;
}

/*
int main() {
	union Float b;
	b.real = 3.0;

	print_bin((b.integer >> 31) & 1, 1);	// sinal
	putchar(' ');
	print_bin((b.integer >> 23) & 0xff, 8);	// expoente
	putchar(' ');
	print_bin(b.integer & 0x7fffff, 23);	// mantissa 
	
	printf("\n signal\n: %d",(b.integer >> 31) & 1);
	printf("\n exponent\n: %d",(b.integer >> 23) & 0xff);
	printf("\n antissa\n: %0.9f",get_mantisse(b.integer & 0x7fffff));
	
	int signal = ((b.integer >> 31) & 1);
	int exponent = (b.integer >> 23) & 0xff;
	float mantisse = get_mantisse(b.integer & 0x7fffff);
	
	if (signal == 0) signal = 1;
	else signal = -1;
	
	printf("\n signal\n: %d", signal);
	printf("\n exponent\n: %d", exponent);
	printf("\n antissa\n: %0.9f", mantisse);
	
	//int value1 = (-1) * signal * pow(2, exponent - 127) * (1 + mantisse);
	//int decimal = ((signal * pow(2, exponent - 127) * (1 + mantisse)) - value1);
	//int decimal2 = (((signal * pow(2, exponent - 127) * (1 + mantisse)) - value1) - decimal) * pow(10, 6);
	int value1 = signal * pow(2, exponent - 127) * (1 + mantisse);
	int decimal2 = (pow(2, exponent - 127) * (1 + mantisse) - (signal * value1)) * pow(10, 6);
	
	printf("\nResult %d : %d \n", value1, decimal2);
	//char buffer[20];
	
	//float_to_string(-18.625, buffer, 6);//Através do buffer_size é possivel saber quantas casas decimais sobram e arredonda-se assim
	
	char str[9];
	printf("Antes: %s\n", str);
	int a = float_to_string(-3.5, str, 9);
	printf("Depois: %s\n", str);
}*/
