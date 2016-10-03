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

#include <boost/circular_buffer.hpp>
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

unsigned long long finalSum = 0;

const unsigned long long modulo = billion;
const unsigned long long threshold = 10*billion;



StopWatch sw;

int main()
{	
	sw.start();
	
	std::vector<std::pair<long long, long long>> init{ { -1, 0 }, { 1, 0 }, { -7, 2 }, { 7, 2 }, { -2, -3 }, { 2, -3 }, { -5, -4 }, { 5, -4 }, { 14, 5 } };
	std::set<long long> gold;

	for (auto &it : init) {
		std::pair<long long, long long> old = it;
		while (old.second < quadrillion) {
			long long x = - 9 * old.first + 20 * old.second + 28;
			long long y = 4 * old.first - 9 * old.second - 14;
			if (y > 0) {
				gold.insert(y);
			}
			old = { x, y };
		}
	}
	auto it = gold.begin();
	for (long long i = 0; i < 30; ++i, ++it) {
		finalSum += *it;
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