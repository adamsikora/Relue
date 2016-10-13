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
const uint64_t billion = thousand * million;
const uint64_t trillion = million * million;
const uint64_t quadrillion = million * billion;

int64_t finalSum = 0;

const uint64_t modulo = 1000000009ui64;
const uint64_t threshold = 1i64 << 50i64;

StopWatch sw;

int64_t naiveFind()
{
	int64_t result = 0;

	int64_t sqrtMax = int64_t(sqrt(threshold));
	auto primes = getPrimes(sqrtMax);
	for (int64_t i = 1; i <= threshold; ++i) {
		bool squareFree = true;
		for (auto p : primes) {
			if (i % (p*p) == 0) {
				squareFree = false;
				break;
			}
		}
		if (squareFree) {
			++result;
		}
	}

	return result;
}

int64_t sqrtMax = int64_t(sqrt(threshold));
const auto primes = getPrimes(sqrtMax);

void recurse(int64_t index, int64_t count, int64_t current)
{
	if (primes[index] * primes[index] <= threshold / current) {
		int64_t next = current * primes[index] * primes[index];
		if (count % 2 == 0)
			finalSum -= threshold / next;
		else {
			finalSum += threshold / next;
		}
		if (index + 1 < primes.size()) {
			recurse(index + 1, count, current);
			recurse(index + 1, count + 1, next);
		}
	}
}

void find()
{
	std::cout << "primes got\n";
	recurse(0, 0, 1);
}

int main()
{
	sw.start();

	finalSum = threshold;
	find();
	//std::cout << naiveFind() << " = " << finalSum << std::endl;

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