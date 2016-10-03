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

const long long treshold = 1000;



int main()
{
   long long finalSum = 0;
   StopWatch sw;
   sw.start();
   
   for (long long i = 3; i <= treshold; i++) {
      long long max = 2;
      for (long long j = 1; j <= 2*i; j += 2) {
         long long modulo = (2 * i * j) % (i*i);
         if (modulo > max)
            max = modulo;
      }
      finalSum += max;
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