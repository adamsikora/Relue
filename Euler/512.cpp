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

std::vector<int64_t> getTotient(int64_t max)
{
	std::vector<int64_t> primes = getPrimes(max);
	std::vector<int64_t> result(max + 1, 1);

	for (int64_t p : primes) {
		int64_t number = p;
		while (number <= max) {
			int64_t interNumber = number / p;
			result[number] *= p - 1;
			while (interNumber % p == 0) {
				result[number] *= p;
				interNumber /= p;
			}
			number += 2*p;
		}
	}

	return result;
}

int64_t naiveFind(int64_t max)
{
	int64_t result = 0;
	std::vector<int64_t> totients = getTotient(max);

	for (int64_t i = 1; i <= max; ++i) {
		int64_t totient = totients[i];
		//int64_t interResult = ((i % 2 == 0) ? 0 : totient) + i/2;
		int64_t interResult = totient;
		std::cout << i << ": ";
		for (int64_t j = 2; j <= i; ++j) {
			totient *= i;
			totient %= i + 1;
			std::cout << totient << " ";
			interResult += totient;
		}
		std::cout << std::endl;
		result += interResult % (i + 1);
	}

	return result;
}

int64_t find(int64_t max)
{
	int64_t result = 0;

	std::vector<int64_t> totients = getTotient(max);

	for (int64_t i = 1; i <= max; ++i) {
		int64_t totient = totients[i];
		int64_t interResult = (i % 2 == 0) ? 0 : totient;
		result += interResult % (i + 1);
	}

	return result;
}

int main()
{
	sw.start();

	std::vector<int64_t> calculated{ find(100) };
	std::vector<int64_t> rightResults{ 2007 };

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

	finalSum = find(500 * million);

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