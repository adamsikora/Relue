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

std::vector<bool> isPrime;

std::vector<long long> primes = getPrimes(100000, isPrime);

int main()
{
	StopWatch sw;
	sw.start();

	long long treshold = 64 *million + 1;

	std::vector<long long> squares(treshold, 1);

	for (long long i = 2; i < treshold; i++) {
		long long square = i * i;
		if (i % million == 0) {
			std::cout << i % million << "M\n";
		}
		for (long long dividee = i; dividee < treshold;  dividee += i) {
			squares[dividee] += square;
		}
	}

	for (long long i = 1; i < treshold; i++) {
		long long root = static_cast<long long>(sqrt(squares[i]));
		if (root * root == squares[i]) {
			std::cout << i << " " << squares[i] << std::endl;
			finalSum += i;
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