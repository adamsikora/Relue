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


int main()
{
   ttmath::UInt<40> finalSum = 0;
   StopWatch sw;
   sw.start();

   ttmath::UInt<40> nul10("10000000000"), jednotka(1);
   
   for (int i = 0; i < 10; i++) {
      jednotka = jednotka * nul10;
   }
   jednotka /= 10;

   for (int k = 2; k < 100; k++) {
      if (static_cast<int>(sqrt(k)) * static_cast<int>(sqrt(k)) == k) {
         continue;
      }
      ttmath::UInt<40> target(k); target = target * jednotka * jednotka;

      ttmath::UInt<40> pomjednotka = jednotka;
      ttmath::UInt<40> cislo(static_cast<int>(sqrt(k))); cislo *= jednotka;
      for (int i = 0; i < 100; i++) {
         pomjednotka = pomjednotka / 10;
         for (ttmath::UInt<40> j = 1; j <= 10; j++) {
            ttmath::UInt<40> pokus = cislo + j * pomjednotka;
            if (pokus * pokus > target) {
               cislo = cislo + (j - 1) * pomjednotka;
               break;
            }
         }
      }
      std::cout << cislo << std::endl;
      for (int i = 0; i < 100; i++) {
         finalSum += cislo % 10;
         cislo /= 10;
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