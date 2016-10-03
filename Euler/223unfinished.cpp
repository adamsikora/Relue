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
uint64_t finalSum = treshold;

StopWatch sw;

int main()
{
	sw.start();

	/*for (int i = 2; i < treshold; ++i) {
		long long c2 = 0;
		long long j = i;
		while ((c2 = i*i + j*j - 1) <= treshold*treshold) {
			long long root = static_cast<long long>(sqrt(c2));
			if (root*root == c2) {
				++finalSum;
				//std::cout << i << " " << j << " " << root << std::endl;
			}
			++j;
		}
	}*/

	for (long long c = 2; c <= treshold; ++c) {
		if (c % 1000 == 0) {
			std::cout << c << std::endl;
		}
		const long long right = c*c + 1;
		long long a = 2;
		long long b = c - 1;
		long long left = a*a + b*b;
		while (a <= b) {
			if (left == right) {
				++finalSum;
				left += 2 * a++ + 1;
				left -= 2 * b-- - 1;
			}
			else {
				(left < right) ? (left += 2 * a++ + 1) : (left -= 2 * b-- - 1);
			}
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