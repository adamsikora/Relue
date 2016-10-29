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
const uint64_t threshold = billion;

StopWatch sw;

int64_t find(int64_t max)
{
	//finalSum = (max - 1) / 2; // trivial cases

	std::vector<bool> is(max, false);

	for (int64_t a = 2; a < max; ++a) {
		int64_t b = a;
		for (; b < max; ++b) {
			int64_t curr = a*b*(a*b - 1) / (a + b);
			if (curr >= max) {
				break;
			}
			if ((a*b - 1) % (a + b) == 0) {
			 is[curr] = true;
			}
		}
		if (b == a) {
			break;
		}
	}
	int64_t count = 0;
	for (int64_t i = 0; i < is.size(); ++i) {
		if (is[i]) {
			++count;
			//std::cout << i << std::endl;
		}
	}
	return count;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;
	//std::cout << naiveFind(threshold) << std::endl;

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