#include <algorithm>
#include <math.h>

#include "Primes.h"

std::vector<int64_t> getPrimes(int64_t maxPrime)
{

	std::vector<bool> potentialPrimes(maxPrime + 1, true);
	potentialPrimes[0] = potentialPrimes[1] = false;

	int64_t ceiling = static_cast<int64_t> (sqrt(maxPrime));
	for (int64_t i = 2; i <= ceiling; i++) {
		if (potentialPrimes[i]) {
			int64_t j = 2 * i;
			while (j <= maxPrime) {
				potentialPrimes[j] = false;
				j += i;
			}
		}
	}

	std::vector<int64_t> primes;
	for (int64_t i = 2; i <= maxPrime; i++)
		if (potentialPrimes[i] == 1)
			primes.push_back(i);
	return primes;
}

std::vector<int64_t> getPrimes(int64_t maxPrime, std::vector<bool>& sieve)
{

	std::vector<bool> potentialPrimes(maxPrime + 1, true);
	potentialPrimes[0] = potentialPrimes[1] = false;

	int64_t ceiling = static_cast<int64_t> (sqrt(maxPrime));
	for (int64_t i = 2; i <= ceiling; i++) {
		if (potentialPrimes[i]) {
			int64_t j = 2 * i;
			while (j <= maxPrime) {
				potentialPrimes[j] = false;
				j += i;
			}
		}
	}
	sieve = potentialPrimes;

	std::vector<int64_t> primes;
	for (int64_t i = 2; i <= maxPrime; i++)
		if (potentialPrimes[i] == 1)
			primes.push_back(i);
	return primes;
}

std::vector<std::vector<std::pair<int64_t, int64_t>>> getFactors(int64_t max)
{
	std::vector<int64_t> primes = getPrimes(max);
	std::vector<std::vector<std::pair<int64_t, int64_t>>> result(max + 1, std::vector<std::pair<int64_t, int64_t>>());

	for (int64_t p : primes) {
		int64_t number = p;
		while (number <= max) {
			int64_t interNumber = number / p;
			int64_t exponent = 1;
			while (interNumber % p == 0) {
				++exponent;
				interNumber /= p;
			}
			result[number].push_back({ p, exponent });
			number += p;
		}
	}

	return result;
}

std::vector<std::vector<int64_t>> getJustFactors(int64_t max)
{
	std::vector<int64_t> primes = getPrimes(max);
	std::vector<std::vector<int64_t>> result(max + 1, std::vector<int64_t>());

	for (int64_t p : primes) {
		int64_t number = p;
		while (number <= max) {
			result[number].push_back(p);
			number += p;
		}
	}

	return result;
}

std::vector<int64_t> primes;

void initializePrimes(int64_t maxPrime)
{
	primes = getPrimes(maxPrime);
}

std::vector<std::pair<int64_t, int64_t>> factorInteger(int64_t toFactor)
{
	std::vector<std::pair<int64_t, int64_t>> result;
	int64_t sqrti = int64_t(sqrt(toFactor));
	for (int64_t p : primes) {
		if (toFactor == 1) {
			break;
		}
		if (p > sqrti) {
			break;
		}
		int64_t exponent = 0;
		while (toFactor % p == 0) {
			toFactor /= p;
			++exponent;
		}
		if (exponent > 0) {
			result.push_back({ p, exponent });
		}
	}
	if (toFactor > 1) {
		result.push_back({ toFactor, 1 });
	}
	return result;
}
