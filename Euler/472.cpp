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
#include <array>

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

ttmath::Int<64> finalSum = 0;

const int64_t modulo = 100 * million;
const int64_t threshold = trillion;

StopWatch sw;

int64_t naiveFind(int64_t max)
{
	int64_t result = 0;
	std::vector<int64_t> counts(max, 0);
	for (int64_t i = 3; i < max; ++i) {
		counts[i] = 1 + counts[i / 2] + counts[(i + 1) / 2 - 1];
	}

	for (int64_t i = 1; i <= max; ++i) {
		std::map<int64_t, int64_t> map;
		for (int64_t j = 1; j <= i; ++j) {
			int64_t count = 1;
			if (j > 2) {
				++count;
				count += counts[j - 2];
			}
			if (j < i - 1) {
				++count;
				count += counts[i - 1 - j];
			}
			if (map.count(count) > 0) {
				++map[count];
			} else {
				map[count] = 1;
			}
		}
		result += map.rbegin()->second;
		//std::cout << i << " " << map.rbegin()->first << " " << map.rbegin()->second << " " << result << std::endl;
	}
	return result;
}

ttmath::Int<64> find(ttmath::Int<64> max)
{
	ttmath::Int<64> result = 0; result = 29;

	ttmath::Int<64> breakPower = 3;
	ttmath::Int<64> breakExp = 8;
	ttmath::Int<64> nextBreak = breakExp + 2;
	ttmath::Int<64> index = nextBreak;

	while (true) {
		if (nextBreak <= max) {
			result += 8;
		} else {
			return result;
		}
		for (ttmath::Int<64> i = 2, pow = 1; i < breakPower; ++i, pow *= 2) {
			if (index + pow <= max) {
				result += pow*(pow + 1);
				index += pow;
			} else {
				ttmath::Int<64> p = max - index;
				result += p*(p + 1);
				return result;
			}
			if (index < max) {
				result += ttmath::Int<64>(4) * pow + 2;
				++index;
			} else {
				return result;
			}
			if (index + pow - 1 <= max) {
				result += pow*(pow + 1) - 2;
				index += pow - 1;
			} else {
				ttmath::Int<64> p = max - index;
				result += p*(p + 1) + ttmath::Int<64>(2) * p*(pow - p);
				return result;
			}
		}
		ttmath::Int<64> pow = breakExp / 4;
		if (index + pow <= max) {
			result += pow*(pow + 1);
			index += pow;
		} else {
			ttmath::Int<64> p = max - index;
			result += p*(p + 1);
			return result;
		}
		if (index < max) {
			result += ttmath::Int<64>(3) * (pow + 1);
			++index;
		} else {
			return result;
		}
		if (index + pow <= max) {
			result += (pow*(pow + 1)) / 2 + ttmath::Int<64>(2) * pow;
			index += pow;
		} else {
			ttmath::Int<64> p = max - index;
			result += (p*(p + 1))/2 + p*(pow - p + 2);
			return result;
		}

		++breakPower;
		breakExp *= 2;
		nextBreak = breakExp + 2;
		index = nextBreak;
	}

	return result;
}

int main()
{
	sw.start();

	//for (int64_t test = 10; test < 500; ++test) {
	//	int64_t naive = naiveFind(test);
	//	int64_t f = find(test);
	//	std::cout << test << " " << naive << " " << f << (naive != f ? " bad" : "") << std::endl;
	//}

	finalSum = find(threshold) % modulo;

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