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

long long finalSum = 0;
long long wins = 0;
long long loses = 0;

long long threshold = 15;

void count(long long curr, long long blue, long long red, long long carry)
{
	if (curr == threshold) {
		if (blue > red) {
			wins += carry;
		}
		else {
			loses += carry;
		}
	}
	else {
		count(curr + 1, blue + 1, red, carry);
		count(curr + 1, blue, red + 1, carry*(curr+1));
	}
}

StopWatch sw;

int main()
{	
	sw.start();
	
	count(0, 0, 0, 1);

	finalSum = factorial(threshold+1) / wins;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}