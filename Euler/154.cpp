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

const int64_t modulo = 982451653i64;
const int64_t threshold = 100 * trillion;

StopWatch sw;

int64_t find(int64_t depth, int64_t mul)
{
	int64_t result = 0;

	std::vector<std::pair<int64_t, int64_t>> multiplicities(depth + 1, { 0, 0 });
	for (int64_t i = 2; i <= depth; ++i) {
		int64_t mul2 = 0;
		int64_t pow2 = 2;
		while (i / pow2 > 0) {
			mul2 += i / pow2;
			pow2 *= 2;
		}
		int64_t mul5 = 0;
		int64_t pow5 = 5;
		while (i / pow5 > 0) {
			mul5 += i / pow5;
			pow5 *= 5;
		}
		multiplicities[i] = { mul2, mul5 };
	}

	auto mulTotal = multiplicities[depth];
	for (int64_t i = 0; i <= depth; ++i) {
		if (i % 1000 == 0) {
			std::cout << i << std::endl;
		}
		auto mulI = multiplicities[i];
		for (int64_t j = 0; j <= depth - i; ++j) {
			auto mulJ = multiplicities[j];
			auto mulK = multiplicities[depth - i - j];
			if (mulTotal.first - mulI.first - mulJ.first - mulK.first >= mul && mulTotal.second - mulI.second - mulJ.second - mulK.second >= mul) {
				++result;
			}
		}
	}

	return result;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;

	//for (int i = 4; i < 10; ++i) {
	//	std::cout << find(i) << std::endl;
	//}

	finalSum = find(200000, 12);

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