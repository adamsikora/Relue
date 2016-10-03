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

long long treshold = 1000000000000i64;

unsigned long long finalSum = 0;



int main()
{
   StopWatch sw;
   sw.start();

   long long lastFive = 1;
   long long trail = 0;
   for (long long i = 1; i <= treshold; i++) {
      long long j = i;
      while (j % 10 == 0) {
         j /= 10;
      }
      while (j % 5 == 0) {
         j /= 5;
         trail++;
      }
      while (trail > 0 && j % 2 == 0) {
         j /= 2;
         trail--;
      }
      lastFive *= j;
      lastFive %= 100000;
   }
   /*std::cout << lastFive << std::endl;

   for (int i = 0; i < 1; i++) {
      long long tenthPower = 1;
      for (int j = 0; j < 10; j++) {
         tenthPower *= lastFive;
         tenthPower %= 100000;
      }
      lastFive = tenthPower;
   }*/
   finalSum = lastFive;

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}