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

unsigned long long finalSum = 0;
std::vector<ttmath::UInt<20>> times{ 0, 1, 2 };


void recurse(unsigned index, bool carry, std::vector<bool>& binary, unsigned maxIndex)
{
   if (index < maxIndex) {
      if (binary[index] == true) {
         if (carry) {
            recurse(index + 1, false, binary, maxIndex);
            recurse(index + 1, true, binary, maxIndex);
         }
         else {
            recurse(index + 1, false, binary, maxIndex);
         }
      }
      else {
         if (carry) {
            recurse(index + 1, true, binary, maxIndex);
         }
         else {
            recurse(index + 1, false, binary, maxIndex);
            recurse(index + 1, true, binary, maxIndex);
         }
      }
   }
   else if (!carry) {
      finalSum++;
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   std::vector<ttmath::UInt<20>> powers;
   powers.push_back(1);
   for (unsigned i = 0; i < 100; i++) {
      powers.push_back(powers.back() * 2);
   }

   std::string streshold = "1";
   for (unsigned i = 0; i < 25; i++) {
      streshold += "0";
   }
   ttmath::UInt<20> treshold(streshold);

   std::vector<bool> binary(100, false);

   unsigned i = 0;
   while (treshold / powers[i] > 0) {
      if ((treshold % powers[i + 1]) / powers[i] != 0) {
         binary[i] = true;
      }
      i++;
   }

   for (unsigned j = 0; j < i; j++) {
      std::cout << binary[j];
   }
   std::cout << std::endl << i << std::endl;

   std::vector<long long> noCarry(100, 0);
   std::vector<long long> carry(100, 0);
   noCarry[0] = carry[0] = 1;

   for (unsigned j = 1; j < i; j++) {
      if (binary[j]) {
         noCarry[j] = noCarry[j - 1] + carry[j - 1];
         carry[j] = carry[j - 1];
      }
      else {
         noCarry[j] = noCarry[j - 1];
         carry[j] = noCarry[j - 1] + carry[j - 1];
      }
   }
   finalSum = noCarry[i - 1];

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}