/*
Adam Sikora
15.2.2014

*/

#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <math.h>

void initializePrimes(int64_t maxPrime);

std::vector<int64_t> getPrimes(int64_t maxPrime);
std::vector<int64_t> getPrimes(int64_t maxPrime, std::vector<bool>& sieve);

std::vector<std::vector<std::pair<int64_t, int64_t>>> getFactors(int64_t max);
std::vector<std::vector<int64_t>> getJustFactors(int64_t max);

std::vector<std::pair<int64_t, int64_t>> factorInteger(int64_t toFactor);

std::vector<std::pair<int64_t, int64_t>> mergeFactors(std::vector<std::pair<int64_t, int64_t>> f, std::vector<std::pair<int64_t, int64_t>> s);


#endif //PRIMES_H