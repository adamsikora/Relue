#include <iostream>
#include <iomanip>

#include <fstream>

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

const long long treshold = 40;

const long long pandig = (1i64 << 10i64) - 1i64;

unsigned long long finalSum = 0;

void process(long long last, long long potPandig, long long count) {
   if (potPandig == pandig) {
      ++finalSum;
   }
   if (count < treshold) {
      if (last > 0) {
         process(last - 1, potPandig | (1i64 << (last - 1i64)), count + 1);
      }
      if (last < 9) {
         process(last + 1, potPandig | (1i64 << (last + 1i64)), count + 1);
      }
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   for (long long i = 1; i < 10; ++i) {
      std::cout << i << std::endl;
      process(i, 1i64 << i, 1);
   }

   sw.stop();
   std::cout << "it took: " << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}