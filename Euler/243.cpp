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

const long long target = billion;
const long long step = 2 * 2 * 2 * 3 * 5 * 7 * 11 * 13;
unsigned long long finalSum = 0;

std::vector<long long> primes = getPrimes(million);

long long nDivisors(unsigned left, long long dividee, long long divisor,
   std::vector<long long>::iterator last, std::vector<long long>::iterator end)
{
   long long toReturn = 0;
   if (left == 0) {
      return dividee / divisor;
   }
   else {
      for (std::vector<long long>::iterator it = last; it < end; it++) {
         if (divisor % *it != 0) {
            toReturn += nDivisors(left - 1, dividee, divisor * *it, it, end);
         }
      }
   }
   return toReturn;
}

double getNonDivisors(long long number)
{
   long long nonDivisors = number;

   std::vector<long long> divisors;
   
   for (std::vector<long long>::iterator it = primes.begin(); it != primes.end() && *it <= number / step; it++) {
      if (number % *it == 0) {
         divisors.push_back(*it);
      }
   }
   for (unsigned i = 1; i <= divisors.size(); i++) {
      if (i % 2 == 1) {
         nonDivisors -= nDivisors(i, number, 1, divisors.begin(), divisors.end());
      }
      else {
         nonDivisors += nDivisors(i, number, 1, divisors.begin(), divisors.end());
      }
   }

   return static_cast<double> (nonDivisors);
}

int main()
{
   StopWatch sw;
   sw.start();

   std::cout << primes.size() << std::endl;


   double lastTarget = 1.0;
   double targetResilience = /*4.0 / 10.0*/ 15499.0 / 94744.0;
   long long number = step;
   while (number < target) {
      double nonDivisors = getNonDivisors(number);
      if (nonDivisors / (number - 1) < lastTarget) {
         std::cout << number << "   " << nonDivisors / (number - 1) << std::endl;
         lastTarget = nonDivisors / (number - 1);
         if (nonDivisors / (number - 1) < targetResilience) {
            finalSum = number;
            break;
         }
      }
      number += step;
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