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

const int treshold = million + 1;

class Amicable {
public:
   Amicable() : sumOfDivisors(0), lenght(0) {};
   int sumOfDivisors;
   int lenght;
};

int main()
{
   ttmath::UInt<40> finalSum = 0;
   StopWatch sw;
   sw.start();

   std::vector<Amicable> amic(treshold, Amicable());
   amic[0].lenght = amic[1].lenght = -1;

   for (int i = 1; i < treshold; i++) {
      if (i % 10000 == 0)
         std::cout << "first phase " << i << std::endl;
      int sumofDivisors = 0;
      int j = i / 2;
      while (j > 0) {
         if (i % j == 0) {
            sumofDivisors += j;
         }
         j--;
      }
      amic[i].sumOfDivisors = sumofDivisors;
      if (sumofDivisors == 1 || sumofDivisors == i || sumofDivisors > treshold - 1) {
         amic[i].lenght = -1;
      }
   }

   int longest = 0;
   for (int i = 1; i < treshold; i++) {
      if (i % 10000 == 0)
         std::cout << "first phase " << i << std::endl;
      if (amic[i].lenght == 0) {
         std::set<int> chain;
         int curlenght = 1;
         chain.insert(i);
         int next = amic[i].sumOfDivisors;
         while (amic[next].lenght == 0) {
            curlenght++;
            chain.insert(next);
            next = amic[next].sumOfDivisors;
            if (next == i) {
               for (std::set<int>::iterator it = chain.begin(); it != chain.end(); it++)
                  amic[*it].lenght = curlenght;
               if (curlenght > longest) {
                  longest = curlenght;
                  finalSum = i;
               }
               goto jump;
            }
            if (chain.count(next)) {
               amic[i].lenght = -1;
               goto jump;
            }
         }
         for (std::set<int>::iterator it = chain.begin(); it != chain.end(); it++)
            amic[*it].lenght = -1;
      jump:;
      }
   }

   std::cout << longest << std::endl;

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}