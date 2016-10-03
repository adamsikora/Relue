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

const uint64_t treshold = 25*10000;
uint64_t finalSum = 0;

std::vector<long long> primes = getPrimes(190);

const long long maxIndex = primes.size();

boost::multiprecision::uint128_t root("2323218950681478446587180516177954549");

boost::multiprecision::uint128_t max = 0;

long long count = 0;

void proceed(long long index, boost::multiprecision::uint128_t curr)
{
	if (index == 10) {
		std::cout << ++count << std::endl;
	}
	if (curr < root) {
		if (curr > max) {
			max = curr;
		}
		if (index < maxIndex) {
			proceed(index + 1, curr);
			proceed(index + 1, curr*primes[index]);
		}
	}
}

StopWatch sw;

int main()
{
	sw.start();

	proceed(0, 1);

	sw.stop();
	std::cout << "it took: " << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << max % (quadrillion*10);
	std::string ans = answer.str();
	std::cout << "Answer is: " << ans << std::endl;
	ClipboardIt(ans);
	std::cin.ignore();
	return EXIT_SUCCESS;
}