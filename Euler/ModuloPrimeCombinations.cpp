#include <numeric>

#include "ModuloPrimeCombinations.h"
#include "IntegerExponent.h"

namespace mpc {

	std::vector<int64_t> moduloFactorials;
	std::vector<int64_t> moduloDenomFactorials;
	int64_t moduloP;
	// both must be initialized before

	void initialize(int64_t max, int64_t modulo)
	{
		moduloP = modulo;
		moduloFactorials = std::vector<int64_t>(max + 1, 0);
		moduloDenomFactorials = std::vector<int64_t>(max + 1, 0);
		moduloFactorials[0] = 1;
		moduloDenomFactorials[0] = 1;
		int64_t num = 1, denom = 1;
		for (int64_t i = 1; i <= max; ++i) {
			num *= i;
			num %= modulo;
			moduloFactorials[i] = num;

			denom *= intExponent(i, modulo - 2, modulo);
			denom %= modulo;
			moduloDenomFactorials[i] = denom;
		}
	}

	int64_t naiveModuloCombination(int64_t n, int64_t k, int64_t modulo) // could fail on big numbers
	{
		int64_t res = 1;
		for (int64_t i = n; i > n - k; --i) {
			res *= i;
		}
		for (int64_t i = 1; i <= k; ++i) {
			res /= i;
		}
		return res % modulo;
	}

	int64_t moduloCombination(int64_t n, int64_t k)
	{
		return (((moduloFactorials[n] * moduloDenomFactorials[k]) % moduloP) * moduloDenomFactorials[n - k]) % moduloP;
	}

	int64_t moduloPermutation(std::vector<int64_t> ns)
	{
		int64_t all = std::accumulate(ns.begin(), ns.end(), 0);
		int64_t result = moduloFactorials[all];
		for (int64_t n : ns) {
			result *= moduloDenomFactorials[n];
			result %= moduloP;
		}
		return result;
	}

	int64_t moduloFactorial(int64_t n)
	{
		return moduloFactorials[n];
	}

}