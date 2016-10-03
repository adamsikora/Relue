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

std::vector<long long> primes = getPrimes(10*million, isPrime);

int main()
{
	StopWatch sw;
	sw.start();

	long long layer = 2;
	long long lastStart = 2;
	long long currStart = 8;
	long long nextStart = 20;
	long long nnextStart = 38;

	long long count = 2;

	while (true) {
		if (isPrime[nextStart - 1 - currStart]) {
			if (isPrime[nextStart + 1 - currStart] && isPrime[nnextStart - 1 - currStart]) {
				count++;
				std::cout << count << " " << currStart << std::endl;
				if (count == 2000) {
					finalSum = currStart;
					break;
				}
			} 
			if (isPrime[nnextStart - 1 - nextStart] && isPrime[nextStart - 1 - lastStart]) {
				count++;
				std::cout << count << " " << nextStart - 1 << std::endl;
				if (count == 2000) {
					finalSum = nextStart - 1;
					break;
				}
			}
		}

		layer++;

		lastStart = currStart;
		currStart = nextStart;
		nextStart = nnextStart;
		nnextStart += 6 * (layer + 1);
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