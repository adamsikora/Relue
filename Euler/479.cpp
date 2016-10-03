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

const int64_t mod = 1000000007;
const int64_t top = million;

StopWatch sw;

int main()
{
	sw.start();

	for (int64_t k = 1; k <= top; ++k) {
		if (k % 1000 == 0) {
			std::cout << k << std::endl;
		}
		int64_t mk2 = (k*k - 1) % mod;
		int64_t pow = (mk2*mk2 - mk2 + mod) % mod;
		int64_t mul = (mk2*mk2) % mod;
		finalSum += pow;
		for (int64_t p = 1; p <= top / 2 - 1; ++p) {
			pow *= mul;
			pow %= mod;
			finalSum += pow;
			finalSum %= mod;
		}
	}

	sw.stop();
	std::cout << "it took: " << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::string ans = answer.str();
	std::cout << "Answer is: " << ans << std::endl;
	ClipboardIt(ans);
	std::cin.ignore();
	return EXIT_SUCCESS;
}