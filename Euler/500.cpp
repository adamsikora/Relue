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
//#include <boost\multiprecision\cpp_int.hpp>

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

/*boost::multiprecision::cpp_int*/ uint64_t finalSum = 0;

uint64_t modulo = 500500507;

StopWatch sw;

std::vector<int64_t> primes;

int64_t find(int64_t power)
{
	int64_t usedPrimes = 0;
	std::map<int64_t, int64_t> minimums;
	minimums[2] = 0;

	int64_t result = 1;
	for (int i = 0; i < power; ++i) {
		auto min = *(minimums.begin());
		minimums.erase(minimums.begin());

		result *= min.first;
		result %= modulo;

		if (min.second == usedPrimes) {
			++usedPrimes;
			minimums[primes[usedPrimes]] = usedPrimes;
		}
		minimums[min.first*min.first] = min.second;
	}
	return result;
}

int main()
{
	sw.start();

	primes = getPrimes(100 * million);

	std::vector<int64_t> calculated{ find(4) };
	std::vector<int64_t> rightResults{ 120 };
	
	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i] % modulo << " = " << rightResults[i] % modulo << std::endl;
		if (calculated[i] % modulo != rightResults[i] % modulo) {
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

	finalSum = find(500500);

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