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


int main()
{
   StopWatch sw;
   sw.start();

   unsigned right = 0, tested = 25;
   unsigned first = 1, second = 1, third = 1;
   while (right < 124) {
      tested += 2;
      unsigned f = first, s = second, t = third;
      unsigned count = 0;
      while (count < tested * tested * tested + 10) {
         unsigned next = f + s + t;
         if (next % tested == 0) {
            goto wrong;
         }
         f = s; s = t; t = next % tested;
         if (f == first && s == second && t == third) {
            break;
         }
         count++;
      }
      right++;
      std::cout << right << "  " << tested << std::endl;
   wrong:;
   }
   finalSum = tested;

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}