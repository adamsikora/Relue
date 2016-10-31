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
const uint64_t threshold = million;

StopWatch sw;

std::vector<int64_t> mdrs(threshold, 0);
std::vector<std::pair<int64_t, int64_t>> currFactors;

int64_t digitalRoot(int64_t input)
{
	while (input / 10 > 0) {
		int64_t inter = 0;
		while (input > 0) {
			inter += input % 10;
			input /= 10;
		}
		input = inter;
	}
	return input;
}

void recurse(int64_t index, int64_t current, int64_t divisor)
{
	if (divisor != 1) {
		int64_t newMax = digitalRoot(divisor) + mdrs[current / divisor];
		if (newMax > mdrs[current]) {
			mdrs[current] = newMax;
		}
	}
	if (index < currFactors.size()) {
		for (int64_t i = 0, factor = 1; i <= currFactors[index].second; ++i, factor *= currFactors[index].first) {
			recurse(index + 1, current, divisor * factor);
		}
	}
}

int64_t find(int64_t max)
{
	int64_t result = 0;
	auto factors = getFactors(threshold);
	std::cout << "factors got\n";

	for (int64_t i = 2; i < max; ++i) {
		currFactors = factors[i];
		recurse(0, i, 1);
		result += mdrs[i];
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