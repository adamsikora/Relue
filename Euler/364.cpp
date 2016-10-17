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

int64_t calc(int64_t i2, int64_t i3, int64_t borders)
{
	int64_t result = mpc::moduloFactorial(i2 + i3 + 1);
	result *= mpc::moduloPermutation({ i2, i3 });
	result %= modulo;
	result *= (intExponent(2, i3, modulo) * mpc::moduloFactorial(i3 + borders)) % modulo;
	result %= modulo;
	result *= mpc::moduloFactorial(i2 + i3);
	result %= modulo;
	return result;
}

int64_t find(int64_t max)
{
	int64_t result = 0;

	for (int64_t i1 = (max - 1) / 2, i2 = 0; i2 <= (max - 1) / 3; ++i2, i1 = (max - 1 - 3*i2) / 2) {
		//std::cout << i1 << " " << i2 << std::endl;
		if ((2 * i1 + 3 * i2 + 1) == max) {
			if (i1 > 0) {
				result += calc(i1 - 1, i2, 2);
				result %= modulo;
				//orezane
			}
			result += calc(i1, i2, 0);
			result %= modulo;
			//full
		} else {
			result += 2 * calc(i1, i2, 1);
			result %= modulo;
		}
	}

	return result;
}

int main()
{
	sw.start();

	mpc::initialize(threshold, modulo);
	std::cout << "mpc initialized" << std::endl;

	finalSum = find(million);

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