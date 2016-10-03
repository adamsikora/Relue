#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>

#include <set>
#include <unordered_set>
#include <map>
#include <vector>
#include <list>

#include <math.h>

#include "boost\circular_buffer.hpp"

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const long long thousand = 1000;
const long long million = thousand * thousand;
const long long billion = thousand * million;
const long long trillion = million * million;
const long long quadrillion = million * billion;

long long finalSum;

long long threshold = million;

std::vector<bool> isPrime;
std::vector<long long> primes = getPrimes(threshold, isPrime);

StopWatch sw;

int main()
{	
	sw.start();

	long long first = 1;
	long long second = 1;
	long long plus = 6;

	while (second < threshold) {
		second += plus;
		plus += 6;
		first = first + second;
		if (isPrime[second]) {
			++finalSum;
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}