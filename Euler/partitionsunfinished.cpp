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

const long long treshold = 10000;

std::vector<std::vector<long long> > recs(treshold, std::vector<long long>(treshold, -1));

inline int recursion(long long nCoins, long long maxPerStack)
{
   if (nCoins == 1)
      return 1;

   if (maxPerStack > nCoins)
      std::cout << "badcall\n", std::cin.ignore();

   if (recs[nCoins][maxPerStack] == -1) {
      long long toReturn = 0;

      for (long long i = 1; i <= min(nCoins, maxPerStack); i++) {
         if (i == nCoins)
            toReturn += 1;
         else
            toReturn += recursion(nCoins - i, min(i, min(nCoins - i, maxPerStack)));
      }
      recs[nCoins][maxPerStack] = toReturn;
   }

   return recs[nCoins][maxPerStack];
}

int main()
{
   long long finalSum = 0;
   StopWatch sw;
   sw.start();
   
   long long nWays = 0;
   long long nCoins = 1;
   while (nCoins < treshold) {
      nWays = recursion(nCoins, nCoins);
      if (nCoins % 100 == 0)
         std::cout << nCoins << std::endl;
      std::cout << std::setw(6) << nCoins << " has partitions: " << std::setw(8) << nWays << std::endl;
      std::cin.ignore();
      if (nWays % million == 0) {
         finalSum = nWays;
         break;
      }
      nCoins++;
   }

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}