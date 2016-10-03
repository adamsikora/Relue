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

const int64_t treshold = 11;

int64_t mask = 15;

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

std::string printStr(int64_t hit)
{
	std::string result;
	for (int64_t i = treshold - 1; i >= 0; --i) {
		result += 'A' + (hit >> (4i64 * i)) % (1i64 << 4i64);
	}
	return result;
}

std::vector<std::set<int64_t>> rotations(2 * treshold, std::set<int64_t>());

int64_t countRotations(int64_t encoded)
{
	std::vector<int64_t> decoded(treshold, 0);
	int64_t result = 0;
	for (int64_t i = treshold - 1; i >= 0; --i) {
		decoded[treshold - 1 - i] = (encoded >> (4i64 * i)) % (1i64 << 4i64);
	}
	for (int64_t i = 0; i < treshold; ++i) {
		if (decoded[i] == i) {
			continue;
		}
		else if (decoded.back() == i) {
			for (int64_t j = i; j < i + (treshold - i) / 2; ++j) {
				std::swap(decoded[j], decoded[treshold - 1 - j + i]);
			}
			++result;
		}
		else {
			int64_t j = i;
			while (decoded[j] != i) { ++j; }
			for (int64_t k = j; k < j + (treshold - j) / 2; ++k) {
				std::swap(decoded[k], decoded[treshold - 1 - k + j]);
			}
			for (int64_t k = i; k < i + (treshold - i) / 2; ++k) {
				std::swap(decoded[k], decoded[treshold - 1 - k + i]);
			}
			result += 2;
		}
	}
	return result;
}

void getEm(int64_t encoded, int64_t used, int64_t index)
{
	if (index == treshold) {
		//std::cout << std::hex << (encoded) << std::endl;
		//std::cout << printStr(encoded) << std::endl;
		//++finalSum;
		rotations[countRotations(encoded)].insert(encoded);
	}
	else {
		for (int64_t i = 0; i < treshold; ++i) {
			if (!(used & (1i64 << i))) {
				getEm(encoded + (index << (4i64 * i)), used + (1i64 << i), index + 1);
			}
		}
	}
}

int main()
{
	sw.start();

	int64_t hit = 18;

	getEm(0, 0, 0);

	int64_t index = 2 * treshold;
	while (rotations[--index].empty());
	int64_t n = 2011;
	//std::cout << index << std::endl;
	for (auto it = rotations[index].begin(); it != rotations[index].end(); ++it) {
		//std::cout << printStr(*it) << std::endl;
		if (--n == 0) {
			finalSum = *it;
			break;
		}
	}

	/*for (auto &p : primes) {
		if (p > treshold) {
			int64_t next = Sam(p) - Max(p);
			assert(next >= 0);
			finalSum += next;
		}
	}*/

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	//answer << printStr(hit);
	answer << printStr(finalSum);
	std::ofstream file;
	file.open("Euler.txt");
	file << answer.str();
	file.close();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}