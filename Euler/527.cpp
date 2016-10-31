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

double finalSum = 0;

const int64_t modulo = 982451653i64;
const int64_t threshold = 100 * trillion;

StopWatch sw;

std::vector<int64_t> counts;

double b(int64_t max)
{
	int64_t result = 0;

	std::map<int64_t, int64_t> segments{ {max, 1} };
	while (!segments.empty()) {
		std::map<int64_t, int64_t> newSegments;
		for (auto& it : segments) {
			result += it.first * it.second;
			int64_t mid = (1 + it.first) / 2;
			int64_t left = mid - 1;
			if (left > 0) {
				if (newSegments.count(left) > 0) {
					newSegments[left] += it.second;
				} else {
					newSegments[left] = it.second;
				}
			}
			int64_t right = it.first - mid;
			if (right > 0) {
				if (newSegments.count(right) > 0) {
					newSegments[right] += it.second;
				} else {
					newSegments[right] = it.second;
				}
			}
		}
		segments = newSegments;
	}

	return double(result) / max;
}

double r(int64_t max)
{
	double currR = 1;
	double sumCurrR = 1;
	for (int64_t l = 2; l <= max; ++l) {
		//std::cout << currR << std::endl;
		currR = 1 + (double(2) * double(sumCurrR) / double(l)) / double(l);
		sumCurrR += l*currR;
	}

	return currR;
}

int main()
{
	sw.start();

	for (int64_t i = 0, s = 1; i < 14; ++i, s *= 28) {
		counts.push_back(s);
	}

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;

	//for (int i = 4; i < 10; ++i) {
	//	std::cout << find(i) << std::endl;
	//}

	finalSum = r(10 * billion) - b(10 * billion);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer.precision(8);
	answer << std::fixed << finalSum;
	std::ofstream file;
	file.open("Euler.txt");
	file << answer.str();
	file.close();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}