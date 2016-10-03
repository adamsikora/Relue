#include <iostream>
#include <iomanip>
#include <assert.h>
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
const long long modulo = billion;

long long finalSum = 0;

long long treshold = 20;

long long multiplier = 111111111;

std::vector<unsigned long long> getFactorial(long long to)
{
   std::vector<unsigned long long> result;
   result.push_back(1);
   for (long long i = 1; i < to; ++i) {
      result.push_back(result.back()*i);
   }
   return result;
}

std::vector<unsigned long long> factorials = getFactorial(treshold + 1);

void proceed(long long last, long long sum, long long index, std::vector<long long> multip)
{
   long long root = static_cast<long long>(sqrt(sum));
   if (root*root == sum && sum != 0) {
      unsigned long long multiplicity = factorials[treshold];
      unsigned long long sum = 0;
      unsigned long long checkSum = 0;
      
      for (size_t i = 0; i < 10; ++i) {
         sum += multip[i] * i;
         checkSum += multip[i];
         assert(multiplicity % factorials[multip[i]] == 0);
         multiplicity /= factorials[multip[i]];
      }
      assert(checkSum == treshold);
      multiplicity %= modulo*treshold;
      multiplicity *= sum;
      multiplicity %= modulo*treshold;
      assert(multiplicity % treshold == 0);
      multiplicity /= treshold;
      multiplicity *= multiplier;
      multiplicity %= modulo;
      finalSum += multiplicity;
      finalSum %= modulo;
   }
   if (index < treshold) {
      for (long long i = last; i < 10; ++i) {
         std::vector<long long> vec = multip;
         ++vec[i];
         --vec[0];
         proceed(i, sum + i*i, index + 1, std::move(vec));
      }
   }
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

   std::vector<long long> vec(10, 0);
   vec[0] = treshold;
   proceed(1, 0, 0, vec);

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