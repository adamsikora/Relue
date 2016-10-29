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
#include "ModuloPrimeCombinations.h"

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
const uint64_t billion = thousand * million; // 10^9
const uint64_t trillion = million * million; // 10^12
const uint64_t quadrillion = million * billion; // 10^15
const uint64_t quintillion = billion * billion; // 10^18

int64_t finalSum = 0;

const uint64_t modulo = 100000007ui64;
const uint64_t threshold = billion;

StopWatch sw;

int64_t find(int64_t max)
{
	std::vector<std::set<int64_t>> points(max, std::set<int64_t>());
	std::map<int64_t, int64_t> paths;

	int64_t pow2 = 1 % max, pow3 = 1 % max;
	for (int64_t i = 0; i <= 2 * max; ++i) {
		points[pow3].insert(pow2);
		pow2 = (2 * pow2) % max;
		pow3 = (3 * pow3) % max;
	}
	//points[0] = std::set<int64_t>();
	//for (auto set : points) {
	//	if (set.count(0) > 0) {
	//		set.erase(0);
	//	}
	//}

	for (auto set : points) {
		for (int64_t i : set) {
			if (paths.empty()) {
				paths.insert({ i, 1 });
			} else {
				auto lb = paths.lower_bound(i);
				if (lb == paths.end()) {
					paths.insert(lb, { i, (--lb)->second + 1 });
					++lb;
				} else if (lb->first == i) {
					++(lb->second);
				} else if (lb == paths.begin()) {
					paths.insert({ i, 1 });
					lb = paths.begin();
				} else {
					paths.insert(lb, { i, (--lb)->second + 1 });
					++lb;
				}
				auto deleter = lb;
				while (++deleter != paths.end() && deleter->second <= lb->second) {}
				paths.erase(++lb, deleter);
				//for (auto it = paths.begin(), jt = ++(paths.begin()); jt != paths.end(); ++it, ++jt) {
				//	if (it->second >= jt->second) {
				//		std::cout << "bad\n";
				//	}
				//}
			}
		}
	}

	return paths.rbegin() == paths.rend() ? 0 : paths.rbegin()->second;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;
	std::cout << find(10000) << std::endl;

	for (int64_t i = 1; i <= 30; ++i) {
		std::cout << i << " ";
		int64_t result = find(intExponent(i, 5, quadrillion));
		std::cout << result << std::endl;
		finalSum += result;
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