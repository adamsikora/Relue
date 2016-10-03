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

boost::multiprecision::cpp_int finalSum = 0;

uint64_t threshold = million;

StopWatch sw;

void addMultipl(int64_t multipl, int64_t antimultipl) {
	int zm = multipl % 4;
	int m1 = 0, m2 = 0, am1 = 0, am2 = 0;
	for (int i = 0; i < 10; ++i) {
		if (multipl % 4 == 1) ++m1;
		if (multipl % 4 == 2) ++m2;
		multipl /= 4;
		if (antimultipl % 4 == 1) ++am1;
		if (antimultipl % 4 == 2) ++am2;
		antimultipl /= 4;
	}
	assert(antimultipl == 0 && multipl == 0);
	assert(m1 + 2 * m2 == 10);
	assert(am1 + 2 * am2 == 10);

	boost::multiprecision::cpp_int first = factorial(m1 + 2 * m2) / (1 << m2);
	if (zm == 2) first -= factorial(m1 + 2 * m2 - 1) / (1 << (m2 - 1));
	if (zm == 1) first -= factorial(m1 + 2 * m2 - 1) / (1 << m2);
	boost::multiprecision::cpp_int second = factorial(am1 + 2 * am2) / (1 << am2);

	finalSum += first*second;
}

void recurse(int64_t multipl, int64_t antimultipl, int64_t load1, int64_t load2, int64_t pos, int64_t multisum) {
	if (pos == 10) {
		if ((90 - 2 * multisum) % 11 == 0 && load1 == load2) {
			addMultipl(multipl, antimultipl);
		}
		return;
	}
	recurse(multipl + (2i64 << (2i64 * pos)), antimultipl + (0i64 << (2i64 * pos)), load1 + 2, load2 + 0, pos + 1i64, multisum + pos * 2i64);
	recurse(multipl + (1i64 << (2i64 * pos)), antimultipl + (1i64 << (2i64 * pos)), load1 + 1, load2 + 1, pos + 1i64, multisum + pos * 1i64);
	recurse(multipl + (0i64 << (2i64 * pos)), antimultipl + (2i64 << (2i64 * pos)), load1 + 0, load2 + 2, pos + 1i64, multisum + pos * 0i64);
}

int main()
{
	sw.start();

	recurse(0, 0, 0, 0, 0, 0);

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