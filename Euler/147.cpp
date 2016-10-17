#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

#include <algorithm>
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
#include "PythagoreanTriples.h"
#include "IntegerExponent.h"

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

const uint64_t modulo = 1000000009ui64;
const uint64_t threshold = 1i64 << 50i64;

StopWatch sw;

int64_t find(int64_t maxM, int64_t maxN)
{
	int64_t result = 0;
	int64_t m = maxM;
	int64_t n = maxN;

	for (int64_t n = 1; n <= maxN; ++n) {
		for (int64_t m = 1; m <= maxM; ++m) {
			for (int64_t i = 0; i < m; ++i) {
				for (int64_t j = 0; j < n; ++j) {
					result += (m - i)*(n - j);
				}
			}
			int64_t top = std::min(m, n);
			for (int64_t i = 1; i < 2*top; ++i) {
				for (int64_t j = 1; j <= 2 * top - i; ++j) {
					//std::cout << i << " " << j << std::endl;
					int64_t boundingBoxLength = i + j;
					bool iMod2 = i % 2 == 0;
					bool jMod2 = j % 2 == 0;
					if (iMod2 && jMod2) {
						int64_t c = boundingBoxLength / 2 - 1;
						if (c < m && c < n) {
							result += (m - c)*(n - c);
						}
						c = boundingBoxLength / 2;
						if (c < m && c < n) {
							result += (m - c)*(n - c);
						}
					}
					if (!iMod2 && !jMod2) {
						int64_t ic = boundingBoxLength / 2 - 1;
						int64_t jc = boundingBoxLength / 2;
						if (jc < m && ic < n) {
							result += (m - jc)*(n - ic);
						}
						ic = boundingBoxLength / 2;
						jc = boundingBoxLength / 2 - 1;
						if (jc < m && ic < n) {
							result += (m - jc)*(n - ic);
						}
					}
					if (iMod2  ^ jMod2) {
						int64_t c = boundingBoxLength / 2;
						if (c < n && c < m) {
							result += 2*(m - c)*(n - c);
						}
					}
				}
			}
		}
	}

	return result;
}

int main()
{
	sw.start();

	finalSum = find(43,47);
	
	//std::cout << naiveFind() << " = " << finalSum << std::endl;

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