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

long long maxN = 50 * million;

std::vector<long long> primes = getPrimes(static_cast<int>(sqrt(2 * maxN * maxN - 1)));

bool isPrime(long long potent)
{
	long long treshold = static_cast<long long>(sqrt(potent));

	for (auto it : primes) {
		if (it > treshold) {
			break;
		}
		else if (potent % it == 0) {
			return false;
		}
	}
	return true;
}

int main()
{
	StopWatch sw;
	sw.start();

	for (long long n = 2; n <= maxN; n++) {
		if (isPrime(2 * n*n - 1)) {
			finalSum++;
		}
		if (n % (million/100) == 0) {
			std::cout << n / (million/100) << "M\n";
		}
	}

   sw.stop();
   std::cout << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << long long(finalSum);
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}