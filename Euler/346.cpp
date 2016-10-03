#include <iostream>
#include <iomanip>

#include <sstream>

#include <set>

#include <math.h>

#include "primes.h"
#include "Clipboard.h"

class Delitele
{
public:
   Delitele() : pocet(0), soucin(1) {};

   long long pocet, soucin;
private:

};

int main() {
   long long upperBound = static_cast<long long> (1e12);
   long long upperBase = static_cast<long long> (sqrt(upperBound));

   std::set<long long> repunits;

   for (long long i = 2; i <= upperBase; i++) {
      long long j = i * i;
      long long repunit = j + i + 1;
      while (repunit < upperBound) {
         repunits.insert(repunit);
         j *= i;
         repunit += j;
      }
   }

   long long finalSum = 1;
   for (std::set<long long>::iterator it = repunits.begin(); it != repunits.end(); it++)
      finalSum += *it;

   std::cout << finalSum;
   std::stringstream answer;
   answer << finalSum;
   ClipboardIt(answer.str());

	std::cin.ignore();
	return EXIT_SUCCESS;
}