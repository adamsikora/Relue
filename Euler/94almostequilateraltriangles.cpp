#include <iostream>
#include <iomanip>

#include <sstream>

#include <set>
#include <map>
#include <vector>

#include <math.h>

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

std::vector<long long> primes = getPrimes(static_cast<int> (sqrt(1e10)) + 1);

inline bool isSquare(long long candidate) {
   long long root = static_cast<long long> (sqrt(candidate));
   if (root * root == candidate ||
      (root - 1) * (root - 1) == candidate ||
      (root + 1) * (root + 1) == candidate)
      return true;
   else
      return false;
}

const unsigned long long treshold(333333333);

int main() {
   long long finalSum = 0;

   for (long long i = 2; i <= 333333334 / 2; i++) {
      long long j = 2*i - 1;
      if (isSquare(j*j - i*i))
         finalSum += 2 * (i + j);
   }
   for (long long i = 1; i <= 333333332 / 2; i++) {
      long long j = 2*i + 1;
      if (isSquare(j*j - i*i))
         finalSum += 2 * (i + j);
   }

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}