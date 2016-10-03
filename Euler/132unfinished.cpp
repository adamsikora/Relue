#include <iostream>
#include <iomanip>

#include <sstream>

#include <set>
#include <map>
#include <vector>

#include <math.h>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const long long maxPrime = 150000000;
std::vector<long long> primes = getPrimes(maxPrime+1);

const long long repunit = 11111111;
const long long base =   100000000;
const long long iterations = 1000000/*000000*/ / 8;

int main() {
   long long finalSum = 0;
   StopWatch sw;
   sw.start();
   std::cout << "primes ready\n";

   int nHits = 0;
   int i = 0;
   while (i < maxPrime) {
      i++;
      long long prime = primes[i];
      long long remainder = 0;
      for (long long j = 0; j < iterations; j++) {
         remainder = (remainder*base + repunit) % prime;
      }
      if (remainder == 0) {
         nHits++;
         std::cout << std::setw(2) << nHits << std::setw(6) << prime << std::endl;
         finalSum += prime;
         if (nHits == 40) {
            std::cin.ignore();
            break;
         }
      }
   }

   /*int maxPrime = 1000000;
   std::vector<bool> isprime(maxPrime, true);
   int ceiling = static_cast<int> (sqrt(maxPrime));
   for (int i = 2; i <= ceiling; i++) {
      if (isprime[i] == true) {
         int j = 2 * i;
         while (j <= maxPrime) {
            isprime[j] = false;
            j += i;
         }
      }
   }
   std::cout << "primes ready" << std::endl;

   int i = 1;
   int nRightOnes = 0;
   while (true) {
      i += 2;
      if (i % 5 == 0)
         continue;
      int repunit = 1;
      int count = 1;
      while (repunit % i) {
         repunit = (repunit % i) * 10 + 1;
         count++;
      }
      if ((i - 1) % count == 0) {
         if (!isprime[i]) {
            nRightOnes++;
            std::cout << std::setw(2) << nRightOnes << std::setw(10) << i << std::endl;
            finalSum += i;
            if (nRightOnes == 25)
               break;
         }
      }
   }*/

   /*int i = 1000001 - 2;
   int maxcount = 0;
   while (true) {
      i += 2;
      if (i % 5 == 0)
         continue;
      int repunit = 1;
      int count = 1;
      while (repunit % i) {
         repunit = (repunit % i)*10 + 1;
         count++;
      }
      if (count > maxcount) {
         std::cout << std::setw(10) << i << " divisible repunit has digits: " << std::setw(10) << count << std::endl;
         maxcount = count;
         if (count > 1000000) {
            finalSum = i;
            break;
         }
      }
   }*/

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}