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

boost::rational<int64_t> finalSum = 0;

const int64_t length = 500;

std::string s = "PPPPNNPPPNPPNPN";

std::vector<bool> isPrime;
std::vector<long long> primes = getPrimes(length, isPrime);

void proceed(long long index, long long position, boost::rational<int64_t> probability)
{
	if (index == s.size()) {
		finalSum += probability;
	}
	else {
		if (position == 1) {
			proceed(index + 1, position + 1, probability * boost::rational<int64_t>((isPrime[position + 1] == (s[index] == 'P')) ? 2 : 1, 3));
		}
		else if (position == length) {
			proceed(index + 1, position - 1, probability * boost::rational<int64_t>((isPrime[position - 1] == (s[index] == 'P')) ? 2 : 1, 3));
		}
		else {
			proceed(index + 1, position + 1, probability * boost::rational<int64_t>((isPrime[position + 1] == (s[index] == 'P')) ? 2 : 1, 6));
			proceed(index + 1, position - 1, probability * boost::rational<int64_t>((isPrime[position - 1] == (s[index] == 'P')) ? 2 : 1, 6));
		}
	}
}

StopWatch sw;

int main()
{
	sw.start();

	for (int i = 1; i <= length; ++i) {
		proceed(1, i, boost::rational<int64_t>(isPrime[i] ? 2 : 1, 3));
	}
	finalSum /= length;

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