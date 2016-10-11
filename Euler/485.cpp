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
//#include <boost/bimap.hpp>
//#include <boost/bimap/set_of.hpp>
//#include <boost/bimap/multiset_of.hpp>
//#include <boost\multiprecision\cpp_int.hpp>

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

int64_t finalSum = 0;

const uint64_t modulo = billion;
uint64_t threshold = million*billion;

StopWatch sw;

std::vector<int64_t> getNDivisors(int64_t max)
{
	std::vector<int64_t> primes = getPrimes(max);
	std::vector<int64_t> result(max + 1, 1);

	for (int64_t p : primes) {
		int64_t number = p;
		while (number <= max) {
			int64_t interNumber = number / p;
			int64_t exponent = 1;
			while (interNumber % p == 0) {
				++exponent;
				interNumber /= p;
			}
			result[number] *= exponent + 1;
			number += p;
		}
	}

	return result;
}

int64_t naiveFind(int64_t u, int64_t k)
{
	int64_t result = 0;
	std::vector<int64_t> nDivisors = getNDivisors(u);

	for (int64_t i = 1; i <= u - k + 1; ++i) {
		int64_t max = 0;
		for (int64_t j = i; j <= i + k - 1; ++j) {
			if (nDivisors[j] > max) {
				max = nDivisors[j];
			}
		}
		result += max;
	}

	return result;
}

int64_t find(int64_t u, int64_t k)
{
	int64_t result = 0;

	std::vector<int64_t> nDivisors = getNDivisors(u);
	std::vector<int64_t> nextBigger(u + 1, std::numeric_limits<int64_t>::max());
	std::map<int64_t, int64_t> sequence;

	for (int64_t i = u; i > 0; --i) {
		while (true) {
			if (sequence.empty()) {
				sequence[nDivisors[i]] = i;
				break;
			} else {
				auto it = sequence.begin();
				if (it->first > nDivisors[i]) {
					nextBigger[i] = it->second;
					sequence[nDivisors[i]] = i;
					break;
				} else {
					sequence.erase(it->first);
				}
			}
		}
	}

	for (int64_t i = 1; i <= u - k + 1; ++i) {
		int64_t max = nDivisors[i];
		int64_t next = nextBigger[i];
		int64_t length = next - i;
		while (length < k) {
			max = nDivisors[next];
			length += nextBigger[next] - next;
			next = nextBigger[next];
		}
		result += max;
	}

	return result;
}

int main()
{
	sw.start();

	std::vector<int64_t> calculated{ find(1000, 10), find(1000, 100), find(10000, 10), find(10000, 100)/*, find(100 * million, 10)*/ };
	std::vector<int64_t> rightResults{ 17176, naiveFind(1000, 100), naiveFind(10000, 10), naiveFind(10000, 100)/*, naiveFind(100 * million, 10)*/ };

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

	finalSum = find(100 * million, 100 * thousand);

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