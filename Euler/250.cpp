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

const long long treshold = 250250;

long long modPow(long long base, long long exponent, long long modulo)
{
   std::vector<long long> twos;
   long long start = base;
   twos.push_back(start);
   for (long long i = 1; (1i64 << i) <= exponent; ++i) {
      start *= start;
      start %= modulo;
      twos.push_back(start);
   }
   long long result = 1;
   for (long long i = 0; (1i64 << i) <= exponent; ++i) {
      if ((1i64 << i) & exponent) {
         result *= twos[i];
         result %= modulo;
      }
   }
   return result;
}

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

   std::vector<long long> powers(250, 0);

   for (long long i = 1; i <= treshold; ++i) {
      ++powers[modPow(i, i, 250)];
   }

   std::vector<long long> counts(250, 0);
   for (long long i = 0; i < 250; ++i) {
      for (long long j = 0; j < powers[i]; ++j) {
         std::vector<long long> subCounts(250, 0);
         ++subCounts[i];
         for (long long k = 0; k < 250; ++k) {
            subCounts[(i + k) % 250] += counts[k];
         }
         for (long long k = 0; k < 250; ++k) {
            counts[k] += subCounts[k];
            counts[k] %= modulo;
         }
      }
      std::cout << i << std::endl;
   }
   finalSum = counts[0];

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