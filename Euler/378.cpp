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
#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

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

const uint64_t modulo = billion*billion;
const uint64_t threshold = 60 * million;

StopWatch sw;

std::vector<std::vector<std::pair<int64_t, int64_t>>> factors;
void recalculateFactors(std::vector<std::vector<std::pair<int64_t, int64_t>>>& factors) {
	for (int64_t i = 1; i <= threshold; ++i) {
		std::vector<std::pair<int64_t, int64_t>> newFactors;
		std::map<int64_t, int64_t> newFact;
		for (auto j : factors[i]) {
			newFact[j.first] = j.second;
		}
		for (auto j : factors[i+1]) {
			if (newFact.count(j.first) > 0) {
				newFact[j.first] += j.second;
			} else {
				newFact[j.first] = j.second;
			}
		}
		for (auto j : newFact) {
			newFactors.push_back(j);
		}
		--(newFactors.front().second);
		factors[i] = newFactors;
	}
}

boost::multiprecision::cpp_int find(int64_t threshold)
{
	std::map<int64_t, int64_t> counts, reverseCounts;
	std::vector<int64_t> dT(threshold + 1, 0);

	for (int64_t i = 1; i <= threshold; ++i) {
		int64_t nFactors = 1;
		for (auto &factor : factors[i]) {
			nFactors *= factor.second + 1;
		}
		counts[nFactors] = 0;
		if (reverseCounts.count(nFactors) > 0) {
			++reverseCounts[nFactors];
		} else {
			reverseCounts[nFactors] = 1;
		}
		dT[i] = nFactors;
	}

	boost::multiprecision::cpp_int result = 0;

	for (int64_t i = 1; i < dT.size(); ++i) {
		int64_t countLower = 0;
		for (auto it = counts.rbegin(); it != counts.rend() && it->first > dT[i]; ++it) {
			countLower += it->second;
		}
		++counts[dT[i]];
		int64_t countUpper = 0;
		--reverseCounts[dT[i]];
		for (auto it = reverseCounts.begin(); it != reverseCounts.end() && it->first < dT[i]; ++it) {
			countUpper += it->second;
		}

		result += countLower * countUpper;
		result %= modulo;
	}
	for (auto it = reverseCounts.begin(); it != reverseCounts.end(); ++it) {
		if (it->second != 0) {
			std::cout << it->first << " - " << it->second << std::endl;
		}
	}

	return result;
}

int main()
{
	sw.start();

	factors = getFactors(threshold+1);
	recalculateFactors(factors);
	std::cout << "Factors calculated\n";

	std::vector<boost::multiprecision::cpp_int> calculated{ find(20), find(100), find(1000)};
	std::vector<int64_t> rightResults{ 14, 5772, 11174776 };
	
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