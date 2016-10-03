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

const long long treshold = 100 * million;
const long long powers[] = { 0, 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11 };
unsigned long long finalSum = 0;



std::vector<std::pair<int, int>> toCheck{ std::pair<int, int>(0, 1), std::pair<int, int>(0, 4), std::pair<int, int>(0, 6),
std::pair<int, int>(1, 6), std::pair<int, int>(2, 5), std::pair<int, int>(3, 6),
std::pair<int, int>(4, 6), std::pair<int, int>(8, 1), };

bool test(unsigned first, unsigned second)
{
   if (first & (1 << 9) && !(first & (1 << 6))) {
      first += 1 << 6;
   }
   if (second & (1 << 9) && !(second & (1 << 6))) {
      second += 1 << 6;
   }
   for (auto it = toCheck.begin(); it != toCheck.end(); it++) {
      if (!(((first & (1 << it->first)) && (second & (1 << it->second)))
         || ((first & (1 << it->second)) && (second & (1 << it->first))))) {
         return false;
      }
   }
   return true;
}

std::vector<unsigned> firstNumbers;
std::vector<unsigned> secondNumbers;

void createSets(unsigned firstLength, unsigned firstSet, std::vector<unsigned>::iterator fit,
                unsigned secondLength, unsigned secondSet, std::vector<unsigned>::iterator sit, bool duplicityProtection = false)
{
   if (firstLength < 6) {
      for (auto it = fit; it != firstNumbers.end(); it++) {
         createSets(firstLength + 1, firstSet + (1 << *it), it + 1, secondLength, secondSet, sit, duplicityProtection);
      }
   }
   else if (secondLength < 6) {
      for (auto it = sit; it != secondNumbers.end(); it++) {
         createSets(firstLength, firstSet, fit, secondLength + 1, secondSet + (1 << *it), it + 1, duplicityProtection);
      }
   }
   else if ((duplicityProtection && firstSet < secondSet) || !duplicityProtection) {
      if (test(firstSet, secondSet)) {
         finalSum++;
      }
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   firstNumbers = std::vector<unsigned>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   secondNumbers = std::vector<unsigned>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   createSets(0, 0, firstNumbers.begin(), 0, 0, secondNumbers.begin(), true);

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}