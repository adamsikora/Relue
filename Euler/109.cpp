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

const long long target = 100;
unsigned long long finalSum = 0;

int main()
{
   StopWatch sw;
   sw.start();

   std::vector<long long> doubles, alls;

   for (long long i = 1; i <= 20; i++) {
      alls.push_back(i);
      alls.push_back(2 * i);
      alls.push_back(3 * i);
      doubles.push_back(2 * i);
   }
   alls.push_back(0);
   alls.push_back(25);
   alls.push_back(50);
   doubles.push_back(50);

   for (std::vector<long long>::iterator i = doubles.begin(); i != doubles.end(); i++) {
      for (std::vector<long long>::iterator j = alls.begin(); j != alls.end(); j++) {
         for (std::vector<long long>::iterator k = alls.begin(); k != alls.end(); k++) {
            if (*j != *k || j <= k) {
               if (*j <= *k && *i + *j + *k < target) {
                  finalSum++;
               }
            }
         }
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