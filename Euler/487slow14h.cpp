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
uint64_t threshold = 100*million;

StopWatch sw;

int64_t naiveS(int64_t max, int64_t power, int64_t modulo)
{
	int64_t result = 0;

	for (int64_t i = 1; i <= max; ++i) {
		for (int64_t j = 1; j <= i; ++j) {
			result += intExponent(j, power, modulo);
			result %= modulo;
		}
	}

	return result;
}

int64_t S(int64_t max, int64_t power, int64_t modulo)
{
	int64_t result = 0;

	const int64_t high = std::min(modulo, max + 1);
	for (int64_t i = 1; i < high; ++i) {
		int64_t exponed = intExponent(i, power, modulo);
		int64_t l = max / modulo + ((max % modulo >= i) ? 1 : 0);
		l %= modulo;
		int64_t rest = (max + 1 - i) % modulo;
		result += (((exponed * l) % modulo) * rest) % modulo;
		result %= modulo;
	}

	return result;
}

//int64_t find(int64_t max)
//{
//	int64_t result = 0;
//
//	auto primes = getPrimes(max);
//	for (int64_t i : primes) {
//		int64_t primeExp = max / i;
//		int64_t iExp = i * i;
//		while (iExp <= max) {
//			primeExp += max / iExp;
//			iExp *= i;
//		}
//		int64_t d = intExponent(i, 2*primeExp, modulo);
//		result += result * d;
//		result %= modulo;
//	}
//
//	return result;
//}

int main()
{
	sw.start();

	std::vector<int64_t> rightResults{ naiveS(4, 1, 3), naiveS(100, 4, trillion), naiveS(100, 4, 4), naiveS(100, 4, 5), naiveS(100, 4, 6) };
	std::vector<int64_t> calculated{ S(4, 1, 3), S(100, 4, trillion), S(100, 4, 4), S(100, 4, 5), S(100, 4, 6) };

	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i]/* % modulo*/ << " = " << rightResults[i]/* % modulo*/ << std::endl;
		if (calculated[i]/* % modulo*/ != rightResults[i]/* % modulo*/) {
			right = false;
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	if (right) {
		std::cout << "Tests passed successfully" << std::endl;
	} else {
		std::cout << "Tests failed" << std::endl;
	}
	sw.start();

	int64_t start = 2 * billion;
	int64_t end = start + 2000;

	std::vector<int64_t> primes = getPrimes(int64_t(sqrt(3 * billion)));
	std::vector<int64_t> realPrimes;
	for (int64_t i = start; i <= end; ++i) {
		bool prime = true;
		for (int64_t p : primes) {
			if (i % p == 0) {
				prime = false;
				break;
			}
		}
		if (prime) {
			realPrimes.push_back(i);
		}
	}
	std::cout << "got primes\n";
	for (auto p : realPrimes) {
		std::cout << p << "  " << sw.getElapsedFromStart() << std::endl;
		finalSum += S(trillion, 10 * thousand, p);
	}

	//finalSum = find(threshold);

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