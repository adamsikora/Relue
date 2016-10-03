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
//#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

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

/*boost::multiprecision::cpp_int*/ uint64_t finalSum = 0;

uint64_t modulo = 500500507;

StopWatch sw;

std::vector<int64_t> primes;

int64_t find(int64_t threshold)
{
	std::vector<int64_t> results(threshold + 1, 0);

	std::unordered_map<std::pair<int64_t, int64_t>, int64_t, pairhash> hash;
	for (int64_t prime : primes) {
		if (prime > threshold) {
			break;
		}
		int64_t number = prime;
		int64_t power = 1;
		int64_t poweredPrime = prime;
		while (poweredPrime <= threshold) {
			hash[{prime, power}] = number;
			number += prime;
			++power;
			poweredPrime *= prime;
			int64_t interNumber = number / prime;
			while (poweredPrime <= threshold && interNumber % prime == 0) {
				hash[{prime, power}] = number;
				interNumber /= prime;
				++power;
				poweredPrime *= prime;
			}
		}
	}

	for (int64_t prime : primes) {
		int64_t number = prime;
		while (number <= threshold) {
			int64_t power = 1;
			int64_t interNumber = number / prime;
			while (interNumber % prime == 0) {
				interNumber /= prime;
				++power;
			}
			if (hash.find({ prime, power }) == hash.end()) {
				std::cout << "Failed\n";
			}
			int64_t max = hash[{prime, power}];
			if (max >= results[number]) {
				results[number] = max;
			}
			number += prime;
		}
	}


	int64_t result = 0;
	for (int64_t i = 2; i <= threshold; ++i) {
		if (results[i] == trillion) {
			std::cout << "Fail\n";
		}
		result += results[i];
	}
	return result;
}

int main()
{
	sw.start();

	primes = getPrimes(100 * million);

	std::vector<int64_t> calculated{ find(100) };
	std::vector<int64_t> rightResults{ 2012 };
	
	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i] % modulo << " = " << rightResults[i] % modulo << std::endl;
		if (calculated[i] % modulo != rightResults[i] % modulo) {
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

	finalSum = find(100 * million);

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