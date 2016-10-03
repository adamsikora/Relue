/*
Adam Sikora
15.2.2014

*/

#ifndef PRIMES_H
#define PRIMES_H

#include <vector>
#include <math.h>

std::vector<long long> getPrimes(int maxPrime);
std::vector<long long> getPrimes(int maxPrime, std::vector<bool>& sieve);

#endif //PRIMES_H