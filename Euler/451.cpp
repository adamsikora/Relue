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
const uint64_t threshold = 20 * million;

StopWatch sw;

std::vector<int64_t> shifts(threshold + 1, std::numeric_limits<int64_t>::max());
std::vector<std::pair<int64_t, int64_t>> currFactors;

void recurse(int64_t index, int64_t current, int64_t shift)
{
	if (current <= threshold) {
		if (shifts[current] > shift) {
			shifts[current] = shift;
		}
		if (index < currFactors.size()) {
			for (int64_t i = 0, n = 1; i <= currFactors[index].second; ++i, n *= currFactors[index].first) {
				recurse(index + 1, current * n, shift);
			}
		}
	}
}

int64_t find(int64_t max)
{
	int64_t result = 0;
	auto factors = getFactors(threshold);
	std::cout << "factors got\n";

	for (int64_t i = 2; i < threshold; ++i) {
		if (i % (100 * thousand) == 0) {
			std::cout << i << std::endl;
		}
		currFactors = mergeFactors(factors[i - 1], factors[i + 1]);
		recurse(0, 1, i);
	}

	for (int64_t i = 3; i <= threshold; ++i) {
		if (shifts[i] == std::numeric_limits<int64_t>::max()) {
			std::cout << "bad\n";
		}
		if (i <= shifts[i]) {
			std::cout << "badbad\n";
		}
		result += i - shifts[i];
	}

	return result;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;
	//std::cout << find(10000) << std::endl;

	finalSum = find(threshold);

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