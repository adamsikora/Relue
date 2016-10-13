/*
Adam Sikora
15.2.2014

*/

#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <math.h>

std::vector<int64_t> getPrimes(int64_t maxPrime);
std::vector<int64_t> getPrimes(int64_t maxPrime, std::vector<bool>& sieve);

std::vector<std::vector<std::pair<int64_t, int64_t>>> getFactors(int64_t max);
std::vector<std::vector<int64_t>> getJustFactors(int64_t max);

#endif //PRIMES_H