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
   int upperBound = 10000001;

   std::vector<long long> primes(getPrimes(upperBound));
   std::cout << "primes ready\n";

   std::vector<Delitele> delitele(upperBound);

   for (std::vector<long long>::iterator it = primes.begin(); it != primes.end(); it++) {
      long long i = *it;
      while (i < upperBound) {
         if (delitele[i].pocet == 2)
            delitele[i].pocet = 10;
         if (delitele[i].pocet < 2) {
            delitele[i].pocet++;
            delitele[i].soucin *= *it;
         }
         i += *it;
      }
   }
   std::cout << "delitele ready\n";

   std::set<long long> counted;
   long long finalSum = 0;

   for (int i = upperBound - 1; i > 0; i--) {
      if (delitele[i].pocet == 2 && !counted.count(delitele[i].soucin)) {
         counted.insert(delitele[i].soucin);
         //std::cout << i << " deli " << delitele[i].soucin << std::endl;
         finalSum += i;
      }
   }
   std::cout << finalSum;
   std::stringstream answer;
   answer << finalSum;
   ClipboardIt(answer.str());

	std::cin.ignore();
	return EXIT_SUCCESS;
}