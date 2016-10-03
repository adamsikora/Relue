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

int main()
{	
	sw.start();
	
	std::vector<std::vector<long long>> input;

	std::fstream file("sets.txt", std::ios::in);
	

	for (long long i = 0; i < 100; ++i) {
		char c[1000];
		file.getline(c, 1000);
		std::string s = c;
		std::vector<long long> numbers;
		long long toput = 0;
		for (auto it : s) {
			if (it == ',') {
				numbers.push_back(toput);
				toput = 0;
			}
			else {
				toput *= 10;
				toput += it - '0';
			}
		}
		numbers.push_back(toput);
		std::sort(numbers.begin(), numbers.end());
		input.push_back(numbers);
	}
	long long count = 0;
	for (auto &it : input) {
		std::cout << ++count;
		if (isSetable(it)) {
			if (isSpecial(it)) {
				std::cout << " yes";
				for (auto &jt : it) {
					finalSum += jt;
				}
			}
		}
		std::cout << std::endl;
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