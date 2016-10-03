#include <iostream>
#include <iomanip>

#include <sstream>

#include <set>
#include <map>
#include <vector>

#include <math.h>

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

int main() {
   int upperBound = 100000000;
   int upperToSquare = static_cast<int> (sqrt(upperBound)) + 1;

   std::vector<bool> candidates(upperBound, false);

   for (int i = 1; i < upperToSquare; i++) {
      int j = i + 1;
      int sum = i * i + j * j;
      while (sum < upperBound) {
         candidates[sum] = true;
         j++;
         sum += j * j;
      }
   }
   std::cout << "sums of squares ready\n";

   long long finalSum = 0;
   int maxnumb = 10, digits = 1;

   for (int i = 0; i < upperBound; i++)
   if (candidates[i]){
      if (i / maxnumb) {
         maxnumb *= 10; digits++;
      }
      if (isPalindrome(i, digits))
         finalSum += i;
   }

   std::stringstream answer;
   answer << finalSum;
   std::cout << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
	return EXIT_SUCCESS;
}