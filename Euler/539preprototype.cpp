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
const uint64_t billion = thousand * million; // 10^9
const uint64_t trillion = million * million; // 10^12
const uint64_t quadrillion = million * billion; // 10^15
const uint64_t quintillion = billion * billion; // 10^18

int64_t finalSum = 0;

const uint64_t modulo = 1000000009ui64;
const uint64_t threshold = 1i64 << 50i64;

StopWatch sw;

int64_t naiveFind(int64_t max)
{
	int64_t result = 0;

	for (int64_t i = 1; i <= max; ++i) {
		std::vector<int64_t> remaining;
		for (int64_t j = 1; j <= i; ++j) {
			remaining.push_back(j);
		}
		bool odd = true;
		while (remaining.size() > 1) {
			std::vector<int64_t> newRemaining;
			if (odd) {
				for (int64_t i = 1; i < remaining.size(); i += 2) {
					newRemaining.push_back(remaining[i]);
				}
			} else {
				for (int64_t i = remaining.size() - 2; i >= 0; i -= 2) {
					newRemaining.push_back(remaining[i]);
				}
				std::reverse(newRemaining.begin(), newRemaining.end());
			}
			if (2 * newRemaining.size() != remaining.size() && 2 * newRemaining.size() + 1 != remaining.size()) {
				std::cout << "bad";
			}
			remaining = newRemaining;
			odd = !odd;
		}
		std::cout << i << " " << remaining[0] << std::endl;
		result += remaining[0];
	}

	return result;
}

int64_t find(int64_t max)
{
	int64_t result = max;

	const int64_t powerer = 4;
	int64_t power = 1;
	int64_t position = 1;
	while (power <= (max-position) / powerer) {
		power *= powerer;
		position += power;
		result += (((max - position) % modulo)*(power % modulo)) % modulo;
		result %= modulo;
	}

	return result;
}

int main()
{
	sw.start();

	finalSum = naiveFind(1000);
	
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