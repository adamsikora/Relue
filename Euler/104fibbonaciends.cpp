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

const long long treshold(1000000000);

inline bool pandigCheck(long long toCheck) {
   int test = 0;
   for (int i = 0; i < 10; i++) {
      test += 1 << (toCheck % 10);
      toCheck /= 10;
   }
   if (test == 1023)
      return true;
   else
      return false;
}

int main() {
   long long prev(1), curr(1), next(0);
   int accuracy = 10;
   std::vector<long long> prevTop(accuracy, 0), currTop(accuracy, 0), nextTop(accuracy, 0);
   prevTop.back() = treshold;
   currTop.back() = treshold;
   long long finalSum(2);

   while (true) {

      next = (prev + curr) % treshold;
      prev = curr;
      curr = next;

      for (int i = 0; i < accuracy; i++)
         nextTop[i] = currTop[i] + prevTop[i];
      for (int i = 0; i < accuracy - 1; i++) {
         if (nextTop[i] >= treshold) {
            nextTop[i + 1] += nextTop[i] / treshold;
            nextTop[i] %= treshold;
         }
      }
      if (nextTop.back() >= treshold) {
         for (int i = 0; i < accuracy - 1; i++) {
            nextTop[i] += (nextTop[i + 1] % 10) * treshold;
            nextTop[i] /= 10;
            currTop[i] += (currTop[i + 1] % 10) * treshold;
            currTop[i] /= 10;
         }
         nextTop.back() /= 10;
         currTop.back() /= 10;
      }
      prevTop = currTop;
      currTop = nextTop;

      //std::cout << currTop.back();
      //std::cin.ignore();

      finalSum++;
      if (pandigCheck(curr) && pandigCheck(currTop.back())) {
         std::cout << curr << "   " << currTop.back() << std::endl;
         break;
      }
   }

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}