#include "IntegerExponent.h"

int64_t intExponent(int64_t base, int64_t power, int64_t modulo)
{
	int64_t result = 1;

	if (power > 0) {
		int64_t currentPower = base % modulo;
		for (int64_t i = 0; 1i64 << i <= power; ++i) {
			if (power & (1i64 << i)) {
				result *= currentPower;
				result %= modulo;
			}
			currentPower *= currentPower;
			currentPower %= modulo;
		}
	}

	return result;
}