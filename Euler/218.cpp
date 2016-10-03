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

StopWatch sw;

const long long treshold = 100 * million;

const std::vector<std::vector<std::vector<long long>>> matrices =
{
	{
		{ 1, -2, 2 },
		{ 2, -1, 2 },
		{ 2, -2, 3 },
	},
	{
		{ 1, 2, 2 },
		{ 2, 1, 2 },
		{ 2, 2, 3 },
	},
	{
		{ -1, 2, 2 },
		{ -2, 1, 2 },
		{ -2, 2, 3 },
	}
};

void tryTriplet(const std::vector<long long>& triplet)
{
	if (gcd(triplet[1], triplet[2]) == 1 && (triplet[1] - triplet[2]) % 2 != 0) {
		int64_t a, b, c;
		if (triplet[1] > triplet[2]) {
			a = triplet[1] * triplet[1] - triplet[2] * triplet[2];
		}
		else {
			a = triplet[2] * triplet[2] - triplet[1] * triplet[1];
		}
		b = 2 * triplet[1] * triplet[2];
		c = triplet[2] * triplet[2] + triplet[1] * triplet[1];
		assert(gcd(a, b) == 1 && gcd(b, c) == 1);
		if (gcd(a, gcd(b, 6 * 28)) != 1) {
			++finalSum;
		}
	}
}

void tryNextTriplet(const std::vector<long long>& parent)
{
	if (parent[2] <= treshold) {
		tryTriplet(parent);
		for (auto &it : matrices) {
			tryNextTriplet(std::vector < long long > {
				it[0][0] * parent[0] + it[0][1] * parent[1] + it[0][2] * parent[2],
					it[1][0] * parent[0] + it[1][1] * parent[1] + it[1][2] * parent[2],
					it[2][0] * parent[0] + it[2][1] * parent[1] + it[2][2] * parent[2],
			});
		}
	}
}

int main()
{
	sw.start();

	std::vector<long long> baseTriplet = { 3, 4, 5 };

	tryNextTriplet(baseTriplet);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}