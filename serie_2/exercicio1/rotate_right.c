#include <stddef.h>
#include <limits.h>

#define	LONG_BIT (sizeof (long) * CHAR_BIT)

void rotate_right(unsigned long value[], size_t n) {
	if (n >= 64) {
		unsigned long tmp = value[0];
		value[0] = value[1];
		value[1] = tmp;
		n -= 64;
	}
	unsigned long mask = (1 << n) - 1;
	unsigned long lower = (value[0] >> n) + ((value[1] & mask) << (LONG_BIT - n));
	unsigned long higher = (value[1] >> n) + ((value[0] & mask) << (LONG_BIT - n));
	value[0] = lower;
	value[1] = higher;
}
