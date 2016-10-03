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

double finalSum = 0;

long long mod = 100 * million;

int main()
{
	StopWatch sw;
	sw.start();

	long long base = 1777;
	long long exp = 1855;

	long long interexp = base;
	for (long long i = 1; i < exp; i++) {
		std::cout << i << std::endl;
		long long mezi = base;
		for (long long j = 1; j < interexp; j++) {
			mezi = (mezi * base) % mod;
		}
		interexp = mezi;
	}
	finalSum = interexp;

   sw.stop();
   std::cout << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << long long(finalSum);
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}