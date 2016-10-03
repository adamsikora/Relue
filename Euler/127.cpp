#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>

#include <set>
#include <map>
#include <vector>
#include <list>

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
const long long trillion = million * million;
const long long quadrillion = million * billion;

long long finalSum = 0;

long long gcd(long long a, long long b)
{
	if (a == b || b == 0) {
		return a;
	}
	else if (a > b) {
		return gcd(b, a);
	}
	else {
		return gcd(a, b % a);
	}
}

long long treshold = 120000;
std::vector<long long> primes = getPrimes(treshold);

StopWatch sw;

int main()
{	
	sw.start();

	std::vector<std::set<long long>> primeFactors(treshold, std::set<long long>());
	for (auto &it : primes) {
		for (long long i = 1; i*it < treshold; ++i) {
			primeFactors[i*it].insert(it);
		}
	}

	for (long long b = 2; b < treshold - 1; ++b) {
		for (long long a = 1, c = a + b; a < b && c < treshold; ++a, ++c) {
			if (gcd(a, b) == 1 && gcd(a, c) == 1 && gcd(b, c) == 1) {
				std::set<long long> factors = primeFactors[a];
				factors.insert(primeFactors[b].begin(), primeFactors[b].end());
				factors.insert(primeFactors[c].begin(), primeFactors[c].end());
				long long rad = 1;
				for (auto &it : factors) {
					rad *= it;
				}
				if (rad < c) {
					finalSum += c;
					std::cout << a << " " << b << " " << c << ": " << rad << std::endl;
				}
			}
		}
	}

	//std::cout << gcd(12, 654) << std::endl;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}