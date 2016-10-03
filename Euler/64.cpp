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

const long long treshold = 10000;

std::vector<long long> primes = getPrimes(million);

inline long long gcd(long long first, long long second)
{
   long long GCD = 1;
   for (int i = 0; primes[i] <= min(first, second);) {
      if (first % primes[i] == 0 && second % primes[i] == 0) {
         GCD *= primes[i];
         first /= primes[i];
         second /= primes[i];
      }
      else
         i++;
   }
   return GCD;
}

int main()
{
   long long finalSum = 0;
   StopWatch sw;
   sw.start();
   
   for (long long i = 2; i <= treshold; i++) {
      if (static_cast<long long>(sqrt(i)) * static_cast<long long>(sqrt(i)) == i)
         continue;
      long long a0 = static_cast<long long>(sqrt(i));
      long long firstnum = a0;
      long long firstdenom = i - a0*a0;
      long long a1 = static_cast<long long>((sqrt(i) + firstnum) / firstdenom);
      firstnum = a1*firstdenom - firstnum;

      long long num = firstnum;
      long long denom = firstdenom;
      long long a = a1;
      long long iterations = 1;

      //std::cout << std::setw(5) << i << "  rozvoj je  ";

      bool out = true;
      do {
         long long lastnum = num;
         long long lastdenom = denom;
         long long lasta = a;

         denom = (i - lastnum*lastnum) / lastdenom;
         if ((i - lastnum*lastnum) % lastdenom)
            std::cout << "ajajaj\n";
         a = static_cast<long long>(lastdenom / (sqrt(i) - lastnum));
         num = denom * a - lastnum;
         //std::cout << a;

         iterations++;
         out = (num != firstnum) || (denom != firstdenom) || (a != a1);
      } while (out);
      //std::cout << std::endl;
      if (iterations % 2 == 0) {
         finalSum++;
      }
   }

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}