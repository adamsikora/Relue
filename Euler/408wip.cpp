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

const uint64_t modulo = 1000000007ui64;
const uint64_t threshold = 10*million;

StopWatch sw;

void countEmUp(int64_t a, int64_t b, int64_t c, int64_t max, int64_t& result)
{
	if (a*a <= max && b*b <= max) {
		int64_t aa = a;
		int64_t bb = b;
		int64_t aa2 = aa*aa;
		int64_t bb2 = bb*bb;
		while (aa2 <= max && bb2 <= max) {
			std::cout << aa2 << " " << bb2 << std::endl;
			int64_t base = mpc::moduloFactorial(aa2 + bb2, aa2);
			int64_t rest = mpc::moduloFactorial(2*max - (aa2 + bb2), max - aa2);
			//std::cout << base << " " << rest << std::endl;
			//std::cout << 2 * max - (aa2 + bb2) << " " << max - aa2 << std::endl;

			result += modulo - (2 * base*rest) % modulo;
			result %= modulo;

			aa += a;
			bb += b;
			aa2 = aa*aa;
			bb2 = bb*bb;
		}
		for (auto &it : pythagoreanTripleGeneratingMatrices) {
			countEmUp(
				it[0][0] * a + it[0][1] * b + it[0][2] * c,
				it[1][0] * a + it[1][1] * b + it[1][2] * c,
				it[2][0] * a + it[2][1] * b + it[2][2] * c,
				max, result
			);
		}
	}
}

int64_t find(int64_t max)
{
	int64_t result = mpc::moduloFactorial(2*max, max);
	countEmUp(3,4,5,max,result);
	return result;
}

// todo solve interaction between two different nonadmissive points

int main()
{
	sw.start();

	mpc::initialize(2*threshold, modulo);
	std::cout << "mpc initialized" << std::endl;

	//std::cout << mpc::moduloFactorial(7,1) << std::endl;
	std::cout << find(1000) << std::endl;
	std::cout << countPrimitiveTriplesUpToC(10000) << std::endl;

	//finalSum = naiveFind(1000);
	
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