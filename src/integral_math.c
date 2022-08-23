#include "integral_math.h"

#define NUM_LUT_ENTRIES(lut) (sizeof(lut) / sizeof(lut[0]))

static const int __lut_rd[] = {
	0,
	1,
	1,
	1, // 3
	2,
	2,
	2,
	2,
	2, // 8
	3,
	3,
	3,
	3,
	3,
	3,
	3, // 15
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4, // 24
	5,
};

static const int __lut_ru[] = {
	0,
	1,
	2,
	2, // 3
	2,
	3,
	3,
	3,
	3, // 8
	3,
	4,
	4,
	4,
	4,
	4,
	4, // 15
	4,
	5,
	5,
	5,
	5,
	5,
	5,
	5,
	5, // 24
	5,
};

static const int __lut_rn[] = {
	0,
	1,
	1,
	2, // 3
	2,
	2,
	2,
	3,
	3, // 8
	3,
	3,
	3,
	3,
	4,
	4,
	4, // 15
	4,
	4,
	4,
	4,
	4,
	5,
	5,
	5,
	5, // 24
	5,
};

int integral_sqrt_rd(int a) {
	if (a < 0)
		return -1;
	if ((unsigned int) a < NUM_LUT_ENTRIES(__lut_rd))
		return __lut_rd[a];
	int i;
	for (i = 5; i < a / 2; i++) {
		if ((i + 1) * (i + 1) > a)
			break;
	}
	return i;
}

int integral_sqrt_ru(int a) {
	if (a < 0)
		return -1;
	if ((unsigned int) a < NUM_LUT_ENTRIES(__lut_ru))
		return __lut_ru[a];
	int i;
	for (i = 6; i < a / 2; i++) {
		int square = i * i;
		if (square == a)
			break;
		if (square > a) {
			i++;
			break;
		}
	}
	return i;
}

int integral_sqrt_rn(int a) {
	if (a < 0)
		return -1;
	if ((unsigned int) a < NUM_LUT_ENTRIES(__lut_rn))
		return __lut_rn[a];
	int this;
	int next = 5 * 5;
	int i;
	for (i = 5; i < a / 2; i++) {
		this = next;
		next = (i + 1) * (i + 1);
		if (next >= a) {
			if (next - a <= a - this)
				i++;
			break;
		}
	}
	return i;
}

