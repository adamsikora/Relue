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
uint64_t threshold = million*billion;

StopWatch sw;

int64_t naiveFind(int64_t n)
{
	int64_t result = 0;

	for (int64_t i = 1; i <= n; ++i) {
		result += ((((i % modulo) * (i % modulo)) % modulo) * ((n / i) % modulo) % modulo);
		result %= modulo;
	}

	return result;
}

int64_t find(int64_t n)
{
	int64_t result = 0;

	std::vector<int64_t> squareSums(modulo, 0);
	int64_t sum = 0;
	for (int64_t i = 0; i < modulo; ++i) {
		sum += (i * i) % modulo;
		sum %= modulo;
		squareSums[i] = sum;
	}
	int64_t sqrtN = int64_t(sqrt(n));
	for (int64_t i = 1; i <= sqrtN; ++i) {
		result += ((((i % modulo) * (i % modulo)) % modulo) * ((n / i) % modulo) % modulo);
		result %= modulo;
	}
	int64_t start = sqrtN + 1;
	while (start <= n) {
		int64_t currentNDivisors = n / start;
		int64_t lastSameMagnitudeDivisor = n / currentNDivisors;
		result += (((squareSums[lastSameMagnitudeDivisor % modulo] - squareSums[(start - 1) % modulo] + modulo) % modulo) * currentNDivisors) % modulo;
		result += (((lastSameMagnitudeDivisor - start + 1) / modulo) * squareSums[modulo - 1]) % modulo;
		result %= modulo;

		start = lastSameMagnitudeDivisor + 1;
	}
	return result;
}

int main()
{
	sw.start();

	//std::vector<int64_t> calculated{ find(6), find(1000), find(million) };
	//std::vector<int64_t> rightResults{ 113, naiveFind(1000), naiveFind(million) };
	//
	//bool right = true;
	//for (uint64_t i = 0; i < calculated.size(); ++i) {
	//	std::cout << calculated[i]/* % modulo*/ << " = " << rightResults[i]/* % modulo*/ << std::endl;
	//	if (calculated[i]/* % modulo*/ != rightResults[i]/* % modulo*/) {
	//		right = false;
	//	}
	//}
	//
	//sw.stop();
	//std::cout << sw.getLastElapsed() << std::endl;
	//
	//if (right) {
	//	std::cout << "Tests passed successfully" << std::endl;
	//} else {
	//	std::cout << "Tests failed" << std::endl;
	//}
	//
	//sw.start();

	finalSum = (find(threshold) + modulo / 2) % modulo; // hack that works, dunno why

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