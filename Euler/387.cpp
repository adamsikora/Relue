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

const long long treshold = 100000000000000i64;

unsigned long long finalSum = 0;

auto primes = getPrimes(billion);

bool isPrime(long long candidate)
{
   std::vector<long long>::iterator it = primes.begin();
   while (*it < static_cast<long long>(sqrt(candidate) + 10)) {
      if (candidate % *it == 0 && candidate > *it) {
         return false;
      }
      it++;
   }
   return true;
}

void recurse(long long number, long long sumOfdigits, bool wasPrime)
{
   for (long long i = 0; i < 10; i++) {
      long long newNumber = number * 10 + i;
      if (newNumber < treshold) {
         if (wasPrime && isPrime(newNumber)) {
            /*std::cout << newNumber << std::endl;
            std::cin.ignore();*/
            finalSum += newNumber;
         }
         if (newNumber % (sumOfdigits + i) == 0) {
            //std::cout << "postupuje: " << newNumber << std::endl;
            recurse(newNumber, sumOfdigits + i, isPrime(newNumber / (sumOfdigits + i)));
         }
      }
      else {
         break;
      }
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   /*for (int i = 1; i < 20; i++)
   std::cout << i << " " << isPrime(i) << std::endl;*/

   for (long long i = 1; i < 10; i++) {
      std::cout << i << std::endl;
      recurse(i, i, false);
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