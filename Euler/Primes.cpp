#include "Primes.h"

std::vector<long long> getPrimes(int maxPrime) {

   std::vector<bool> potentialPrimes(maxPrime + 1, true);
   potentialPrimes[0] = potentialPrimes[1] = false;

   int ceiling = static_cast<int> (sqrt(maxPrime));
   for (int i = 2; i <= ceiling; i++) {
      if (potentialPrimes[i]) {
         int j = 2 * i;
         while (j <= maxPrime) {
            potentialPrimes[j] = false;
            j += i;
         }
      }
   }

   std::vector<long long> primes;
   for (int i = 2; i <= maxPrime; i++)
   if (potentialPrimes[i] == 1)
      primes.push_back(i);
   return primes;
}

std::vector<long long> getPrimes(int maxPrime, std::vector<bool>& sieve) {

   std::vector<bool> potentialPrimes(maxPrime + 1, true);
   potentialPrimes[0] = potentialPrimes[1] = false;

   int ceiling = static_cast<int> (sqrt(maxPrime));
   for (int i = 2; i <= ceiling; i++) {
      if (potentialPrimes[i]) {
         int j = 2 * i;
         while (j <= maxPrime) {
            potentialPrimes[j] = false;
            j += i;
         }
      }
   }
   sieve = potentialPrimes;

   std::vector<long long> primes;
   for (int i = 2; i <= maxPrime; i++)
   if (potentialPrimes[i] == 1)
      primes.push_back(i);
   return primes;
}
