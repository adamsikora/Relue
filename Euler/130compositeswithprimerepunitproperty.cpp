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

std::vector<long long> primes = getPrimes(1000000);
int primeIndex = 0;



int main() {
   long long finalSum = 0;
   StopWatch sw;
   sw.start();

   int maxPrime = 1000000;
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
   }

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
   std::cout << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}