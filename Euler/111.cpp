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

inline bool isPrime(long long candidate) {
   for (std::vector<long long>::iterator it = primes.begin(); it != primes.end() && candidate > *it; it++)
   if (candidate % *it == 0)
      return false;
   return true;
}

int main() {
   std::vector<long long> base{
   1000000000,
   1111111111,
   2222222222,
   3333333333,
   4444444444,
   5555555555,
   6666666666,
   7777777777,
   8888888888,
   9999999999
   };
   int digits = 4;

   std::vector<long long> sums(10, 0);

   for (int i = 1; i < 10; i++)
   for (int j = 1; j < 10; j++) {
      if (isPrime(i*base[0] + j)) {
         sums[0] += i*base[0] + j;
      }
   }

   for (int i = 1; i < 10; i++)
   for (int j = 0; j < 10; j++)
   for (long long k = 1; k <= base[0]; k *= 10) {
      if (j == 0 && k == base[0])
         continue;
      if (isPrime(base[i] - i * k + j * k))
         sums[i] += base[i] - i * k + j * k;
   }
   
   for (int i = 1; i < 10; i++)
   if (sums[i] == 0) {
      for (int j = 0; j < 10; j++)
      for (long long k = 10; k <= base[0]; k *= 10) {
         if (j == 0 && k == base[0])
            continue;
         for (int l = 0; l < 10; l++)
         for (long long m = 1; m < k; m *= 10) {
            if (isPrime(base[i] - i * k + j * k - i * m + l * m))
               sums[i] += base[i] - i * k + j * k - i * m + l * m;
         }
      }
   }

   long long finalSum = 0;
   for (int i = 0; i < 10; i++) {
      if (sums[i] == 0)
         std::cout << "spatne "<< i << "\n";  
      finalSum += sums[i];
   }

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}