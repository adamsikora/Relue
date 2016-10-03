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

const int64_t tresh = 2*billion;
std::vector<unsigned char> is(tresh + 1, 0);

StopWatch sw;

int main()
{
	sw.start();

	std::vector<unsigned char> curr(tresh + 1, 0);
	for (uint64_t i = 1; i < tresh; ++i) {
		for (uint64_t j = 1; j <= i; ++j) {
			uint64_t n = i*i + j*j;
			if (n > tresh) {
				break;
			}
			else {
				curr[n] = 1;
			}
		}
	}
	for (uint64_t i = 1; i <= tresh; ++i) {
		if (curr[i] != 0) {
			++is[i];
		}
		curr[i] = 0;
	}
	std::cout << "1";

	for (uint64_t i = 1; i < tresh; ++i) {
		for (uint64_t j = 1; j <= tresh; ++j) {
			uint64_t n = i*i + 2*j*j;
			if (n > tresh) {
				break;
			}
			else {
				curr[n] = 1;
			}
		}
	}
	for (uint64_t i = 1; i <= tresh; ++i) {
		if (curr[i] != 0) {
			++is[i];
		}
		curr[i] = 0;
	}
	std::cout << "2";

	for (uint64_t i = 1; i < tresh; ++i) {
		for (uint64_t j = 1; j <= tresh; ++j) {
			uint64_t n = i*i + 3*j*j;
			if (n > tresh) {
				break;
			}
			else {
				curr[n] = 1;
			}
		}
	}
	for (uint64_t i = 1; i <= tresh; ++i) {
		if (curr[i] != 0) {
			++is[i];
		}
		curr[i] = 0;
	}
	std::cout << "3";

	for (uint64_t i = 1; i < tresh; ++i) {
		for (uint64_t j = 1; j <= tresh; ++j) {
			uint64_t n = i*i + 7*j*j;
			if (n > tresh) {
				break;
			}
			else {
				curr[n] = 1;
			}
		}
	}
	for (uint64_t i = 1; i <= tresh; ++i) {
		if (curr[i] != 0) {
			++is[i];
		}
		curr[i] = 0;
	}
	std::cout << "7";

	for (uint64_t i = 1; i <= tresh; ++i) {
		if (is[i] == 4) {
			++finalSum;
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