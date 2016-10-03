#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>

#include <set>
#include <unordered_set>
#include <map>
#include <vector>
#include <list>

#include <math.h>

#include "boost\circular_buffer.hpp"
#include <boost/lexical_cast.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const long long thousand = 1000;
const long long million = thousand * thousand;
const long long billion = thousand * million;
const long long trillion = million * million;
const long long quadrillion = million * billion;

long long finalSum;

long long threshold = million;

StopWatch sw;

void tryConfiguration(long long sum1, long long sum2, std::vector<long long>::iterator begin, std::vector<long long>::iterator end, bool& spec)
{
	if (spec) {
		if (begin == end) {
			if (sum1 != 0 && sum2 != 0) {
				if (sum1 == sum2) {
					spec = false;
				}
			}
		}
		else {
			tryConfiguration(sum1, sum2, begin + 1, end, spec);
			tryConfiguration(sum1 + *begin, sum2, begin + 1, end, spec);
			tryConfiguration(sum1, sum2 + *begin, begin + 1, end, spec);
		}
	}
}

bool isSpecial(std::vector<long long> vect)
{
	bool spec = true;
	tryConfiguration(0, 0, vect.begin(), vect.end(), spec);
	return spec;
}

bool isSetable(std::vector<long long> vect)
{
	bool toret = true;
	for (long long i = 2; i <= vect.size() / 2 + 1; ++i) {
		long long sum1 = 0, sum2 = 0;
		for (long long j = 0; j < i; ++j) {
			sum1 += vect[j];
		}
		long long bounds = (i == vect.size() / 2 + 1 && vect.size() % 2 == 0) ? i - 2 : i - 1;
		for (long long j = 0; j < bounds; ++j) {
			sum2 += vect[vect.size() - 1 - j];
		}
		if (sum1 <= sum2) {
			toret = false;
			break;
		}
	}
	return toret;
}

long long minimum = million;
const long long span = 20;
const long long start = 10;
const long long targetIndex = 7;
std::stringstream result;

void tryVector(long long index, long long number, long long sum, std::vector<long long> potent)
{
	if (index < targetIndex) {
		if (index == 0) {
			std::cout << number << std::endl;
		}
		for (long long i = number + 1; i < number + 1 + span; ++i) {
			std::vector<long long> newpot = potent;
			newpot.push_back(i);
			tryVector(index + 1, i, sum + i, std::move(newpot));
		}
	}
	else {
		if (sum < minimum && isSetable(potent) && isSpecial(potent)) {
			minimum = sum;
			result.str(std::string());
			for (auto &it : potent) {
				result << it;
			}
			std::cout << minimum << " : " << result.str() << std::endl;
		}
	}
}

int main()
{	
	sw.start();
	
	tryVector(0, start, 0, std::vector<long long>());

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << result.str();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}