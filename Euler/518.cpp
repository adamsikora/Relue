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
#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

#undef min;
#undef max;

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

//const uint64_t modulo = trillion;
uint64_t threshold = 100*million;

StopWatch sw;

std::vector<int64_t> primes;
std::unordered_set<int64_t> primesP1;

int64_t recurse(int64_t aP1, int64_t divider, int64_t index, const std::vector<std::pair<int64_t, int64_t>>& doubleFactors, uint64_t usedFactors) {
	int64_t result = 0;
	if (index < doubleFactors.size()) {
		for (int64_t i = 0, dividerModifier = 1; i <= doubleFactors[index].second; ++i, dividerModifier *= doubleFactors[index].first) {
			result += recurse(aP1, divider*dividerModifier, index + 1, doubleFactors, usedFactors + (i == 0 ? 0ui64 : 1ui64 << index));
		}
	} else {
		int64_t max = int64_t(sqrt(double(threshold) / aP1) * divider);
		for (int64_t i = divider + 1; i <= max; ++i) {
			bool skip = false;
			for (int64_t j = 0; j < doubleFactors.size(); ++j) {
				if (usedFactors & 1ui64 << j) {
					if (i % doubleFactors[j].first == 0) {
						skip = true;
						break;
					}
				}
			}
			if (skip) {
				continue;
			}
			int64_t bP1 = (i*aP1) / divider;
			if (primesP1.count(bP1) > 0) {
				int64_t cP1 = (i*bP1) / divider;
				if (primesP1.count(cP1) > 0) {
					result += aP1 + bP1 + cP1 - 3;
				}
			}
		}
	}
	return result;
}

int64_t find(int64_t threshold)
{
	int64_t result = 0;
	int64_t step = million;
	int64_t next = step;
	for (int64_t i = 0; i < primes.size() && primes[i] <= threshold; ++i) {
		if (primes[i] > next) {
			std::cout << next << std::endl;
			next += step;
		}
		int64_t aP1 = primes[i]+1;
		std::vector<std::pair<int64_t, int64_t>> doubleFactors;
		for (int64_t j = 0; primes[j] * primes[j] <= aP1; ++j) {
			int64_t doubleFactor = primes[j] * primes[j];
			int64_t power = 0;
			int64_t aP1c = aP1;
			while (aP1c % doubleFactor == 0) {
				aP1c /= doubleFactor;
				++power;
			}
			if (power > 0) {
				doubleFactors.push_back({ primes[j], power });
			}
		}
		result += recurse(aP1, 1i64, 0, doubleFactors, 0);
	}

	return result;
}

int main()
{
	sw.start();

	threshold = 100;
	primes = getPrimes(threshold);
	for (int64_t p : primes) {
		primesP1.insert(p + 1);
	}

	std::vector<int64_t> calculated{ find(100) };
	std::vector<int64_t> rightResults{ 1035 };
	
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

	threshold = 100*million;
	primes = getPrimes(threshold);
	for (int64_t p : primes) {
		primesP1.insert(p + 1);
	}

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