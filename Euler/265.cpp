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

const long long number = 5;
const long long nCombination = 1 << number;

long long finalSum = 0;

void circle(long long rotation, long long potent, std::set<long long> taken)
{
   //std::cout << potent << "  " << std::endl;
   if (rotation < nCombination) {
      potent *= 2;
      if (!taken.count(potent % nCombination)) {
         std::set<long long> next = taken;
         next.insert(potent % nCombination);
         circle(rotation + 1, potent, next);
      }
      potent += 1;
      if (!taken.count(potent % nCombination)) {
         std::set<long long> next = taken;
         next.insert(potent % nCombination);
         circle(rotation + 1, potent, next);
      }
   }
   if (rotation == nCombination) {
      long long test = potent;
      bool right = true;
      for (int i = 1; i < number; i++) {
         test *= 2;
         if (taken.count(test % nCombination)) {
            right = false;
            break;
         }
         else {
            taken.insert(test % nCombination);
         }
      }
      //std::cout << "tryresult is " << right << std::endl;
      if (right) {
         std::cout << potent << std::endl;
         finalSum += potent;
      }
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   long long potent = 1;
   circle(number + 1, potent, std::set<long long>{0, potent});

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}