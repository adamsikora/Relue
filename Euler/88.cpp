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

const int64_t treshold = 12*thousand;
int64_t left = treshold - 1;

std::vector<int64_t> psnInit()
{
	std::vector<int64_t> res(treshold + 1, 0);
	res[0] = res[1] = 1;
	return std::move(res);
}
std::vector<int64_t> psn(psnInit());

StopWatch sw;

std::vector<int64_t> primes = getPrimes(treshold + 1);

std::vector<std::pair<int64_t, int64_t>> factor(int64_t toFactor)
{
	std::vector<std::pair<int64_t, int64_t>> result;
	int64_t left = toFactor;
	for (auto &prime : primes) {
		if (left % prime == 0) {
			int64_t mul = 0;
			while (left % prime == 0) {
				++mul;
				left /= prime;
			}
			result.emplace_back(prime, mul);
			if (left == 1) {
				break;
			}
		}
	}
	return std::move(result);
}

void psnIt(std::vector<std::pair<int64_t, int64_t>> factors, int64_t number, int64_t sumDiv, int64_t nDiv, int64_t nextDiv)
{
	if (left > 0) {
		if (nextDiv > 1) {
			psnIt(factors, number, sumDiv + nextDiv, nDiv + 1, 1);
		}
		if (!factors.empty()) {
			for (auto i = 0; i < factors.size(); ++i) {
				assert(factors[i].second > 0);
				if (factors[i].second > 1) {
					--(factors[i].second);
					psnIt(factors, number, sumDiv, nDiv, nextDiv * factors[i].first);
					++(factors[i].second);
				}
				else {
					std::vector<std::pair<int64_t, int64_t>> newF = factors;
					newF.erase(newF.begin() + i);
					psnIt(newF, number, sumDiv, nDiv, nextDiv * factors[i].first);
				}
			}
		}
		else if (nextDiv == 1) {
			int64_t index = nDiv + number - sumDiv;
			if (index <= treshold && psn[index] == 0) {
				psn[index] = number;
				--left;
				if (left % 12 == 0 || left < 100) {
					std::cout << left << " " << number << std::endl;
				}
			}
		}
	}
}

int main()
{
	sw.start();

	int64_t curr = 1;
	while (left > 0) {
		psnIt(factor(curr), curr, 0, 0, 1);
		++curr;
	}
	std::set<int64_t> uni;
	for (int i = 2; i <= treshold; ++i) {
		uni.insert(psn[i]);
	}
	assert(!uni.count(0));
	for (auto &n : uni) {
		finalSum += n;
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}