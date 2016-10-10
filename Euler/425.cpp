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
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost\multiprecision\cpp_int.hpp>

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

boost::multiprecision::cpp_int finalSum = 0;

//const uint64_t modulo = trillion;
uint64_t threshold = 10*million;

StopWatch sw;

typedef boost::bimap<boost::bimaps::set_of<int64_t>, boost::bimaps::multiset_of<int64_t>> biMap;

int64_t find(int64_t threshold)
{
	int64_t result = 0;

	std::vector<int64_t> primes = getPrimes(threshold);
	std::unordered_map<int64_t, int64_t> primesBelong;
	for (int64_t i : primes) {
		if (i > threshold) {
			break;
		}
		primesBelong[i] = quadrillion;
	}

	biMap toCheck;
	toCheck.insert(biMap::value_type(2, 2));
	primesBelong[2] = 2;
	while (!toCheck.empty()) {
		auto minIt = toCheck.right.begin();

		const int64_t number = minIt->second;
		const int64_t max = minIt->first;
		toCheck.left.erase(minIt->second);
		//change digit
		int64_t tenPlace = 1;
		while (tenPlace < number) {
			int64_t nBase = (10*tenPlace)*(number / (10*tenPlace)) + number % tenPlace;
			for (int i = 0; i <= 9; ++i) {
				int64_t n = i*tenPlace + nBase;
				int64_t maxN = std::max(max, n);
				if (primesBelong.count(n) > 0 && primesBelong[n] > maxN) {
					primesBelong[n] = maxN;
					toCheck.left.erase(n);
					toCheck.insert(biMap::value_type(n, maxN));
				}
			}
			tenPlace *= 10;
		}
		//add to left
		for (int i = 1; i <= 9; ++i) {
			int64_t n = i*tenPlace + number;
			int64_t maxN = std::max(max, n);
			if (primesBelong.count(n) > 0 && primesBelong[n] > maxN) {
				primesBelong[n] = maxN;
				toCheck.left.erase(n);
				toCheck.insert(biMap::value_type(n, maxN));
			}
		}
	}

	for (auto i : primesBelong) {
		if (i.second > i.first) {
			result += i.first;
		}
	}

	return result;
}

int main()
{
	sw.start();

	std::vector<int64_t> calculated{ find(thousand), find(10*thousand) };
	std::vector<int64_t> rightResults{ 431, 78728 };
	
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