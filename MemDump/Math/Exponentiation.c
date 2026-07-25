#include "Exponentiation.h"

int Exponent(int base, int degree) {
	int res = 1;
	for (int i = 0; i < degree; i++) {
		res *= base;
	}
	return res;
}