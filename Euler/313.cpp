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

#include <boost/circular_buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include <boost/rational.hpp>
#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const uint64_t thousand = 1000;
const uint64_t million = thousand * thousand;
const uint64_t billion = thousand * million;
const uint64_t trillion = million * million;
const uint64_t quadrillion = million * billion;

int64_t finalSum = 0;

uint64_t threshold = million;

StopWatch sw;

std::vector<int64_t> primes = getPrimes(threshold - 1);
std::unordered_set<int64_t> p2;

int main()
{
	sw.start();

	/*for (auto prime : primes) {
		p2.insert(prime*prime);
	}

	for (int64_t m = 2; m < threshold*threshold; ++m) {
		if (p2.count(8 * m - 11)) ++finalSum;
		for (int64_t n = m + 1; n < threshold*threshold; ++n) {
			if (p2.count(2 * m + 6 * n - 13)) finalSum += 2;
		}
	}*/

	for (auto prime : primes) {
		if ((prime*prime + 11) % 8 == 0) ++finalSum;
		if ((prime*prime + 13) % 2 == 0) {
			int64_t tmp = (prime*prime + 13) / 2;
			int64_t mmin = tmp % 3;
			if (mmin == 2) finalSum += 2;
			int64_t k = (tmp / 3 - mmin) / 2;
			finalSum += k;
		}
	}

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