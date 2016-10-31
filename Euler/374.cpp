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

const int64_t modulo = 982451653i64;
const int64_t threshold = 100 * trillion;

StopWatch sw;

int64_t find(int64_t max)
{
	int64_t ceil = 2 * int64_t(sqrt(max)) + 5;
	std::vector<int64_t> inverses(ceil, 0);
	std::vector<int64_t> inverseSums(ceil, 0);
	for (int64_t i = 2; i < ceil; ++i) {
		int64_t inverse = intExponent(i, modulo - 2, modulo);
		inverses[i] = inverse;
		inverseSums[i] = (inverseSums[i - 1] + inverse) % modulo;
	}
	std::cout << "inverses initialized\n";

	int64_t runningCount = 4;
	int64_t result = 2 * 2 + 3 * 2;
	int64_t m = 2;
	int64_t factorial = 2 * 3 * 4;
	for (;;++m) {
		if (runningCount + 1 + m <= max) {
			result += (((factorial * inverseSums[m + 2]) % modulo) * m) % modulo;
			result %= modulo;

			runningCount += 1 + m;
		} else {
			break;
		}
		if (runningCount < max) {
			factorial *= m + 3;
			factorial %= modulo;

			result += ((factorial * ((inverses[2] * inverses[m + 2]) % modulo) % modulo) * m) % modulo;
			result %= modulo;

			++runningCount;
		} else {
			break;
		}
	}
	int64_t position = m + 2;
	while (runningCount < max) {
		result += (((factorial * inverses[position--]) % modulo) * m) % modulo;
		result %= modulo;

		++runningCount;
	}
	return result;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;

	//for (int i = 4; i < 10; ++i) {
	//	std::cout << find(i) << std::endl;
	//}

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