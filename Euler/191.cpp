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

const long long target = 30;

long long finalSum = 0;

void iterate(long long days, long long absents, bool late)
{
   if (days == target) {
      finalSum++;
   }
   else {
      if (absents < 2) {
         iterate(days + 1, absents + 1, late);
      }
      if (!late) {
         iterate(days + 1, 0, true);
      }
      iterate(days + 1, 0, late);
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   iterate(0, 0, false);

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}