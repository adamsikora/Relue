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


int main() {
   long long finalSum = 0;
   StopWatch sw;
   sw.start();

   int i = 1000001 - 2;
   int maxcount = 0;
   while (true) {
      i += 2;
      if (i % 5 == 0)
         continue;
      int repunit = 1;
      int count = 1;
      while (repunit % i) {
         repunit = (repunit % i)*10 + 1;
         count++;
      }
      if (count > maxcount) {
         std::cout << std::setw(10) << i << " divisible repunit has digits: " << std::setw(10) << count << std::endl;
         maxcount = count;
         if (count > 1000000) {
            finalSum = i;
            break;
         }
      }
   }

   sw.stop();
   std::cout << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}