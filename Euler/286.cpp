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

/*int64_t*/double finalSum = 0;

const int64_t treshold = 10*million;

StopWatch sw;

/*std::vector<int64_t> primes = getPrimes(2 * treshold);

std::vector<std::vector<int64_t>> digits =
{
	{ 1, 0, 1, 1, 1, 1, 1 },//0
	{ 0, 0, 0, 0, 1, 0, 1 },//1
	{ 1, 1, 1, 0, 1, 1, 0 },//2
	{ 1, 1, 1, 0, 1, 0, 1 },//3
	{ 0, 1, 0, 1, 1, 0, 1 },//4
	{ 1, 1, 1, 1, 0, 0, 1 },//5
	{ 1, 1, 1, 1, 0, 1, 1 },//6
	{ 1, 0, 0, 1, 1, 0, 1 },//7
	{ 1, 1, 1, 1, 1, 1, 1 },//8
	{ 1, 1, 1, 1, 1, 0, 1 } //9
};

std::vector<int64_t> countDigits()
{
	std::vector<int64_t> result;
	for (auto &numb : digits) {
		int64_t dig = 0;
		for (auto &i : numb) {
			if (i) { ++dig; }
		}
		result.push_back(dig);
	}
	return std::move(result);
}
std::vector<int64_t> count = countDigits();

std::vector<std::vector<int64_t>> countIntersec()
{
	std::vector<std::vector<int64_t>> result;
	for (auto &numb1 : digits) {
		std::vector<int64_t> nextRow;
		for (auto &numb2 : digits) {
			int64_t dig = 0;
			for (int64_t i = 0; i < 7; ++i) {
				if (numb1[i] && numb2[i]) {
					++dig;
				}
			}
			nextRow.push_back(dig);
		}
		result.push_back(nextRow);
	}
	return std::move(result);
}

std::vector<std::vector<int64_t>> intersec = countIntersec();

int64_t countNextSam(int64_t i, std::vector<int64_t>& result)
{
	if (i < 10) {
		return 2*count[i];
	}
	else {
		int64_t digsum = 0;
		int64_t digcount = 0;
		while (i) {
			digsum += i % 10;
			digcount += count[i % 10];
			i /= 10;
		}
		return 2*digcount + countNextSam(digsum, result);
	}
}

std::vector<int64_t> countSamBase()
{
	std::vector<int64_t> result;
	for (int64_t i = 0; i < 10; ++i) {
		result.push_back(count[i]);
	}
	for (int64_t i = 10; i < 200; ++i) {
		result.push_back(countNextSam(i, result));
	}
	return result;
}

std::vector<int64_t> samBase = countSamBase();

int64_t Sam(int64_t i)
{
	int64_t digsum = 0;
	int64_t digcount = 0;
	while (i) {
		digsum += i % 10;
		digcount += count[i % 10];
		i /= 10;
	}
	return 2*digcount + samBase[digsum];
}

int64_t countNextMax(int64_t i, std::vector<int64_t>& result)
{
	if (i < 10) {
		return 2 * count[i];
	}
	else {
		int64_t digsum = 0;
		int64_t digcount = 0;
		int64_t icopy = i;
		while (i) {
			digsum += i % 10;
			digcount += count[i % 10];
			i /= 10;
		}
		int64_t digsumcopy = digsum;
		int64_t subtract = 0;
		while (icopy && digsum) {
			subtract += intersec[icopy % 10][digsumcopy % 10];
			icopy /= 10;
			digsumcopy /= 10;
		}
		return 2 * digcount - 2 * subtract + countNextMax(digsum, result);
	}
}

std::vector<int64_t> countMaxBase()
{
	std::vector<int64_t> result;
	for (int64_t i = 0; i < 10; ++i) {
		result.push_back(count[i]);
	}
	for (int64_t i = 10; i < 200; ++i) {
		result.push_back(countNextMax(i, result));
	}
	return result;
}

std::vector<int64_t> maxBase = countMaxBase();

int64_t Max(int64_t i)
{
	int64_t digsum = 0;
	int64_t digcount = 0;
	int64_t icopy = i;
	while (i) {
		digsum += i % 10;
		digcount += count[i % 10];
		i /= 10;
	}
	int64_t digsumcopy = digsum;
	int64_t subtract = 0;
	while (icopy && digsumcopy) {
		subtract += intersec[icopy % 10][digsumcopy % 10];
		icopy /= 10;
		digsumcopy /= 10;
	}
	return 2 * digcount - subtract + maxBase[digsum];
}*/

int main()
{
	sw.start();

	/*for (auto &p : primes) {
		if (p > treshold) {
			int64_t next = Sam(p) - Max(p);
			assert(next >= 0);
			finalSum += next;
		}
	}*/
	double q = 52.64945719530;
	std::vector<double> prob(51, 0.0);
	prob[0] = 1.0;
	for (int i = 1; i <= 50; ++i) {
		std::vector<double> newprob(51, 0.0);
		for (int j = 0; j < i; ++j) {
			newprob[j] += prob[j] * i / q;
			newprob[j + 1] += prob[j] * (1.0 - i / q);
		}
		prob = newprob;
	}
	std::cout << std::setprecision(20) << std::fixed << prob[20] << std::endl;
	finalSum = q;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << std::setprecision(10) << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}