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

const long long target = 20;

unsigned long long finalSum = 0;

std::vector<std::vector<long long> > empty(10, std::vector<long long>(10, 0));
std::vector<std::vector<long long> > sums = empty;


int main()
{
   StopWatch sw;
   sw.start();

   for (int i = 0; i < 10; i++) {
      sums[i][i] = 1;
   }
   for (int digit = 1; digit < target; digit++) {
      std::vector<std::vector<long long> > newSums = empty;
      for (unsigned lastTwo = 0; lastTwo < 10; lastTwo++) {
         for (unsigned last = 0; last <= lastTwo; last++) {
            for (unsigned next = 0; next < 10; next++) {
               if (lastTwo + next < 10) {
                  newSums[last + next][next] += sums[lastTwo][last];
               }
            }
         }
      }
      sums = newSums;
   }
   for (unsigned lastTwo = 1; lastTwo < 10; lastTwo++) {
      for (unsigned last = 1; last <= lastTwo; last++) {
         finalSum += sums[lastTwo][last];
      }
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