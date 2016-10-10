#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

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
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

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

boost::multiprecision::cpp_int finalSum = 0;

const uint64_t modulo = 100000007i64;
//uint64_t threshold = 10*million;

StopWatch sw;

int64_t encode(int64_t decimal) {
	switch (decimal) {
	case 0: return 0b1111101;
	case 1: return 0b0101000;
	case 2: return 0b0110111;
	case 3: return 0b0101111;
	case 4: return 0b1101010;
	case 5: return 0b1001111;
	case 6: return 0b1011111;
	case 7: return 0b1101100;
	case 8: return 0b1111111;
	case 9: return 0b1101111;
	}
}

int64_t singleStepSavings(int64_t f, int64_t s) {
	int64_t result = 0;
	while (f > 0 && s > 0) {
		int64_t bits = encode(f % 10) & encode(s % 10);
		int64_t nBits = 0;
		while (bits > 0) {
			if (bits % 2 == 1) {
				++nBits;
			}
			bits /= 2;
		}
		result += nBits;
		f /= 10;
		s /= 10;
	}
	return result;
}

int64_t find()
{
	int64_t result = 0;
	std::vector<int64_t> primes = getPrimes(20 * million);
	int64_t last = -1;
	for (auto prime : primes) {
		if (prime > 10 * million) {
			int64_t descend = prime;
			if (last != -1) {
				//std::cout << last << std::endl;
				//std::cin.ignore();
				//result += singleStepSavings(descend, last);
			}
			while (descend >= 10) {
				int64_t digitSum = 0;
				int64_t temp = descend;
				while (temp) {
					digitSum += temp % 10;
					temp /= 10;
				}
				result += singleStepSavings(descend, digitSum);
				descend = digitSum;
			}
			last = descend;
		}
	}

	return result * 2;
}

int main()
{
	sw.start();

	for (int i = 0; i < 10; ++i) {
		int64_t encoded = encode(i);
		std::cout << i << ":" << std::endl;
		std::cout << " " << ((encoded & (1 << 2)) ? "-" : " ") << std::endl;
		std::cout << ((encoded & (1 << 6)) ? "|" : " ") << " " << ((encoded & (1 << 5)) ? "|" : " ") << std::endl;
		std::cout << " " << ((encoded & (1 << 1)) ? "-" : " ") << std::endl;
		std::cout << ((encoded & (1 << 4)) ? "|" : " ") << " " << ((encoded & (1 << 3)) ? "|" : " ") << std::endl;
		std::cout << " " << ((encoded & (1 << 0)) ? "-" : " ") << std::endl;
		std::cout << std::endl;
	}

	//std::cout << savedInDescend(137) << " = " << 5 << std::endl;
	//std::cout << savedInDescend(90) << " = " << 5 << std::endl;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	sw.start();

	finalSum = find();

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