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

int64_t finalSum = 0;

const int64_t modulo = 982451653i64;
const int64_t threshold = 100 * trillion;

StopWatch sw;

int64_t twoToNm1;
int64_t twoTotwoNm2;

int64_t recurse(int64_t x1, int64_t x2, int64_t y1, int64_t y2)
{
	int64_t sx1 = (x1 - twoToNm1)*(x1 - twoToNm1);
	int64_t sx2 = (x2 - twoToNm1)*(x2 - twoToNm1);
	int64_t sy1 = (y1 - twoToNm1)*(y1 - twoToNm1);
	int64_t sy2 = (y2 - twoToNm1)*(y2 - twoToNm1);
	bool b1 = sx1 + sy1 <= twoTotwoNm2;
	bool b2 = sx1 + sy2 <= twoTotwoNm2;
	bool b3 = sx2 + sy1 <= twoTotwoNm2;
	bool b4 = sx2 + sy2 <= twoTotwoNm2;
	int64_t result;
	if (b1 == b2 && b2 == b3 && b3 == b4) {
		result = 2;
	} else {
		int64_t splitX = (x1 + x2) / 2;
		int64_t splitY = (y1 + y2) / 2;
		result = 1
			+ recurse(x1, splitX, y1, splitY)
			+ recurse(x1, splitX, splitY + 1, y2)
			+ recurse(splitX + 1, x2, y1, splitY)
			+ recurse(splitX + 1, x2, splitY + 1, y2);
	}
	return result;
}

int64_t find(int64_t n)
{
	twoToNm1 = intExponent(2, n - 1);
	twoTotwoNm2 = intExponent(2, 2 * n - 2);

	int64_t result = 1;

	result += recurse(0, twoToNm1 - 1, 0, twoToNm1 - 1);
	result += recurse(0, twoToNm1 - 1, twoToNm1, 2*twoToNm1 - 1);
	result += recurse(twoToNm1, 2 * twoToNm1 - 1, 0, twoToNm1 - 1);
	result += recurse(twoToNm1, 2 * twoToNm1 - 1, twoToNm1, 2 * twoToNm1 - 1);

	return result;
}

int main()
{
	sw.start();
	int64_t n = 3;
	int64_t dim = intExponent(2, n);
	int64_t twoToNm1 = intExponent(2, n - 1);
	int64_t twoTotwoNm2 = intExponent(2, 2*n - 2);
	for (int64_t y = 0; y < dim; ++y) {
		int64_t yPart = (y - twoToNm1)*(y - twoToNm1);
		for (int64_t x = 0; x < dim; ++x) {
			if ((x - twoToNm1)*(x - twoToNm1) + yPart <= twoTotwoNm2) {
				std::cout << "X";
			} else {
				std::cout << "O";
			}
		}
		std::cout << std::endl;
	}

	finalSum = find(24);

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