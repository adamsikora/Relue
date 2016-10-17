#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

#include <algorithm>
#include <limits>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>

#include <math.h>

//#include <boost/circular_buffer.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/functional/hash.hpp>
//#include <boost/rational.hpp>
//#include <boost/bimap.hpp>
//#include <boost/bimap/set_of.hpp>
//#include <boost/bimap/multiset_of.hpp>
//#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"
#include "PythagoreanTriples.h"
#include "IntegerExponent.h"
#include "ModuloPrimeCombinations.h"

#include "StopWatch.h"

#undef min
#undef max

struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

const uint64_t thousand = 1000;
const uint64_t million = thousand * thousand;
const uint64_t billion = thousand * million; // 10^9
const uint64_t trillion = million * million; // 10^12
const uint64_t quadrillion = million * billion; // 10^15
const uint64_t quintillion = billion * billion; // 10^18

int64_t finalSum = 0;

const uint64_t modulo = 100000007ui64;
const uint64_t threshold = 75*million;

StopWatch sw;

int64_t naiveFind(int64_t max)
{
	int64_t result = 0;
	for (int64_t a = 1; a < max / 3; ++a) {
		for (int64_t b = a; b < max / 2; ++b) {
			int64_t c2 = a*a + b*b + 1;
			int64_t c = int64_t(sqrt(c2));
			if (c*c == c2 && a + b + c <= max) {
				++result;
			}
		}
	}
	return result;
}

std::vector<std::pair<int64_t, int64_t>> factors;

void recurse(int64_t a, int64_t divisor, int64_t max, int64_t index)
{
	if (divisor < max / divisor) {
		if (index == factors.size()) {
			if ((divisor + max / divisor) % 2 == 0) {
				int64_t b = (max / divisor - divisor) / 2;
				int64_t c = (max / divisor + divisor) / 2;
				if (a <= b && b <= c && a + b + c <= threshold) {
					++finalSum;
				}
			}
		}
		if (index < factors.size()) {
			for (int64_t i = 0, power = 1; i <= factors[index].second; ++i, power *= factors[index].first) {
				recurse(a, divisor * power, max, index + 1);
			}
		}
	}
}

void find(int64_t max)
{
	//finalSum = (max - 1) / 2; // trivial cases

	for (int64_t a = 2; a < max / 3; ++a) {
		if (a % 10000 == 0) {
			std::cout << a << std::endl;
		}
		int64_t a2m1 = a * a + 1;
		factors = factorInteger(a2m1);
		recurse(a, 1, a2m1, 0);
	}
}

int main()
{
	sw.start();

	initializePrimes(threshold);
	std::cout << "primes initialized" << std::endl;
	//std::cout << naiveFind(threshold) << std::endl;

	find(threshold);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::ofstream file;
	file.open("Euler.txt");
	file << answer.str();
	file.close();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}