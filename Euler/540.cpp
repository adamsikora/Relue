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

const uint64_t modulo = billion;
uint64_t threshold = 3141592653589793;

StopWatch sw;

void adjust(int64_t index, int64_t count, int64_t multiplied, int64_t ceiling, const std::vector<int64_t>& factors, int64_t& result)
{
	if (index < factors.size()) {
		adjust(index + 1, count, multiplied, ceiling, factors, result);
		int64_t newMultiplied = multiplied * factors[index];
		if (newMultiplied <= ceiling) {
			if (count % 2 == 0) {
				result -= ceiling / newMultiplied;
			} else {
				result += ceiling / newMultiplied;
			}
			adjust(index + 1, count + 1, newMultiplied, ceiling, factors, result);
		}
	}
}

int64_t find(int64_t max)
{
	int64_t result = 0;
	// for generating primitive triples use c = m^2 + n^2, m > n, gcd(m,n) = 1
	int64_t maxM = int64_t(sqrt(max));
	if (maxM*maxM > max || (maxM + 1)*(maxM + 1) <= max) {
		std::cout << "bad\n";
	}
	auto factors = getJustFactors(maxM);
	std::cout << "got them\n";
	for (int64_t m = 2; m <= maxM; ++m) {
		int64_t m2 = m*m;
		int64_t maxN = int64_t(sqrt(max - m2));
		if (maxN*maxN > max - m2 || (maxN + 1)*(maxN + 1) <= max - m2) {
			std::cout << "bad\n";
		int64_t maxN = std::min(int64_t(sqrt(max - m2)), m - 1);
		}
		maxN = std::min(maxN, m - 1);
		if (m % 2 == 1) {
			maxN /= 2;
		}
		int64_t interResult = maxN;

		adjust(0, 0, 1, maxN, factors[m], interResult);

		result += interResult;
	}
	return result;
}

const double pi = 3.14159265358979323846;

int main()
{
	sw.start();

	std::vector<int64_t> calculated{ find(50), find(million) };
	std::vector<int64_t> rightResults{ countPrimitiveTriplesUpToC(50), countPrimitiveTriplesUpToC(million) };

	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i]/* % modulo*/ << " = " << rightResults[i]/* % modulo*/ << std::endl;
		if (calculated[i]/* % modulo*/ != rightResults[i]/* % modulo*/) {
			right = false;
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	if (right) {
		std::cout << "Tests passed successfully" << std::endl;
	} else {
		std::cout << "Tests failed" << std::endl;
	}
	sw.start();
	
	//for (int64_t i = 10; i <= 1000*billion; i *= 10) {
	//	std::cout << int64_t(pi*i) << " " << find(int64_t(pi*i)) << std::endl;
	//}
	//std::cout << "done\n";

	finalSum = find(threshold);

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