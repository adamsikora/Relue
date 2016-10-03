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

long long threshold = 12;

void count(long long firstCount, long long secondCount, bool right, long long threshold, long long& result)
{
	if (firstCount == threshold && secondCount == threshold && right) {
		++result;
	}
	if (firstCount < secondCount) {
		right = true;
	}
	if (firstCount < threshold) {
		count(firstCount + 1, secondCount, right, threshold, result);
	}
	if (secondCount < threshold) {
		count(firstCount, secondCount + 1, right, threshold, result);
	}
}

long long countEm(long long size)
{
	long long toret = 0;
	count(1, 0, false, size, toret);
	return toret;
}

StopWatch sw;

int main()
{	
	sw.start();
	
	for (long long i = 2; i <= threshold / 2; ++i) {
		finalSum += combinations(threshold, 2 * i) * countEm(i);
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