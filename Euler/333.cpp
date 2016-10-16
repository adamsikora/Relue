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

std::vector<int64_t> nP;
std::vector<std::vector<int64_t>> numbers;
int64_t maximum;

void recurse(int64_t currVal, int64_t min2, int64_t max3)
{
	++nP[currVal];
	for (int64_t i = min2; i < numbers.size(); ++i) {
		for (int64_t j = 0; j <= max3; ++j) {
			if (currVal + numbers[i][j] <= maximum) {
				recurse(currVal + numbers[i][j], i + 1, j - 1);
			}
		}
	}
}

int64_t find(int64_t max)
{
	int64_t result = 0;
	maximum = max;
	nP = std::vector<int64_t>(max + 1, 0);
	int64_t max2 = 0;
	int64_t powered = 2;
	while (powered <= max) {
		powered *= 2;
		++max2;
	}
	int64_t max3 = 0;
	powered = 3;
	while (powered <= max) {
		powered *= 3;
		++max3;
	}

	numbers = std::vector<std::vector<int64_t>>(max2 + 1, std::vector<int64_t>(max3 + 1, -1));

	for (int64_t i = 0, powi = 1; i <= max2; ++i, powi *= 2) {
		for (int64_t j = 0, powj = 1; j <= max3; ++j, powj *= 3) {
			numbers[i][j] = powi*powj;
		}
	}

	recurse(0, 0, max3);

	auto primes = getPrimes(max);
	for (auto p : primes) {
		if (nP[p] == 1) {
			result += p;
		}
	}

	return result;
}

int main()
{
	sw.start();

	finalSum = find(1000000);
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