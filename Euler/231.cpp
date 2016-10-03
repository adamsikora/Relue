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

const long long thousand = 1000;
const long long million = thousand * thousand;
const long long billion = thousand * million;

const long long num = 20 * million;
const long long firstden = 15 * million;
const long long secondden = num - firstden;

std::vector<long long> primes = getPrimes(num + 1000);

int main()
{
   long long finalSum = 0;
   StopWatch sw;
   sw.start();

   std::cout << primes.size() << " primes ready\n";

   unsigned i = 0;
   while (primes[i] <= num) {
      long long del = primes[i];
      while (del <= num) {
         finalSum += (num / del) * primes[i];
         del *= primes[i];
      }
      i++;
   }
   std::cout << finalSum << std::endl;
   i = 0;
   while (primes[i] <= firstden) {
      long long del = primes[i];
      while (del <= firstden) {
         finalSum -= (firstden / del) * primes[i];
         del *= primes[i];
      }
      i++;
   }
   std::cout << finalSum << std::endl;
   i = 0;
   while (primes[i] <= secondden) {
      long long del = primes[i];
      while (del <= secondden) {
         finalSum -= (secondden / del) * primes[i];
         del *= primes[i];
      }
      i++;
   }
   std::cout << finalSum << std::endl;

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}