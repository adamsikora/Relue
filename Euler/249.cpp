#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <algorithm>

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
const long long trillion = thousand * billion;
const long long quadrillion = thousand * trillion;
const long long modulo = 10i64 * quadrillion;

long long finalSum = 0;

const long long treshold = 5000;

std::vector<long long> primes = getPrimes(treshold);

/*const ttmath::UInt<8> megaprime = "5397346292805549782720214077673687806275517530364350655459511599582614290";
const ttmath::UInt<4> root = "2323218950681478446587180516177954549";

const std::vector<unsigned> primes = {
   2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
   97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181 };

const size_t size = 4;

void recurse(ttmath::UInt<4> potPSR, size_t index)
{
   if (potPSR < root && potPSR > finalSum) {
      finalSum = potPSR;
   }
   if (potPSR < root && index < size) {
      recurse(potPSR*primes[index], index + 1);
      recurse(potPSR, index + 1);
   }
}*/

int main()
{
   StopWatch sw;
   sw.start();

   long long sum = 0;
   for (auto &it : primes) {
      sum += it;
   }
   ++sum;
   std::vector<long long> counts(sum, 0);
   counts[0] = 1;
   long long top = 1;
   for (auto &prime : primes) {
      std::vector<std::pair<long long, long long>> news;
      for (size_t i = 0; i < top; ++i) {
         if (counts[i] > 0) {
            news.emplace_back(i + prime, counts[i]);
         }
      }
      top = news.back().first + 1;
      for (auto &newbie : news) {
         counts[newbie.first] += newbie.second;
         counts[newbie.first] %= modulo;
      }
      std::cout << prime << std::endl;
   }

   std::vector<bool> isPrime;
   getPrimes(sum, isPrime);

   for (size_t i = 2; i < sum; ++i) {
      if (isPrime[i]) {
         finalSum += counts[i];
         finalSum %= modulo;
      }
   }

   //std::cout << megaprime << std::endl;
   //std::cout << root << std::endl;
   //
   //recurse(1, 0);

   sw.stop();
   std::cout << "it took: " << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   //answer << finalSum % ttmath::UInt<4>("10 000 000 000 000 000");
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}