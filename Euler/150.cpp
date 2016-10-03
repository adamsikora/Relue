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

long long finalSum = 0;

const long long threshold = thousand;

StopWatch sw;

long long t = 0;

long long generateNext()
{
	t = (615949 * t + 797807) % (1i64 << 20);
	return t - (1i64 << 19);
}

int main()
{	
	sw.start();

	std::vector<std::vector<long long>> triangle;
	long long count = 0;
	for (long long i = 0; i < threshold; ++i) {
		triangle.push_back(std::vector<long long>());
		for (long long j = 0; j <= i; ++j) {
			triangle.back().push_back(generateNext());
			++count;
		}
	}

	long long minimum = 0;

	for (long long column = 0; column < threshold; ++column) {
		std::vector<long long> sums;
		for (long long row = column; row < threshold; ++row) {
			sums.push_back(0);
			long long sum = 0;
			for (long long index = 0; index <= row - column; ++index) {
				sum += triangle[row][column + index];
				sums[sums.size() - 1 - index] += sum;
				if (sums[sums.size() - 1 - index] < minimum) {
					minimum = sums[sums.size() - 1 - index];
				}
			}
		}
	}
	finalSum = minimum;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}