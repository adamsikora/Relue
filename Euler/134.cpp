#include <iostream>
#include <iomanip>

#include <math.h>

#include "primes.h"

int main() {
   std::vector<long long> primes(getPrimes(1000020));
   std::vector<long long>::iterator it = primes.end() - 2;
   while (*it > 1000000) {
      primes.pop_back();
      it = primes.end() - 2;
   }
   std::cout << primes.back() << std::endl;

   long long finalSum = 0;

   long long greaterRound = 10;

   for (std::vector<long long>::iterator it = primes.begin() + 3; it != primes.end(); it++) {
      long long p1 = *(it - 1), p2 = *it;

      if (p1 >= greaterRound) {
         greaterRound *= 10;
      }
      long long greaterModulo = greaterRound % p2, intermediateModulo = p1, multiplicationFactor = 0;

      long long i = 1;
      while (intermediateModulo != 0) {
         multiplicationFactor = (i * p2 - p1) / greaterModulo;
         intermediateModulo = (multiplicationFactor * greaterModulo + p1) % p2;
         i++;
      }
      long long rightOne = multiplicationFactor * greaterRound + p1;
      finalSum += rightOne;

      //std::cout << "found comp of " << p1 << " and " << p2 << " is " << rightOne << std::endl;
   }

   std::cout << finalSum;

	std::cin.ignore();
	return EXIT_SUCCESS;
}