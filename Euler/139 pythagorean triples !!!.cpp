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

StopWatch sw;

const long long treshold = 100*million;

const std::vector<std::vector<std::vector<long long>>> matrices = 
{
	{
		{ 1, -2, 2 },
		{ 2, -1, 2 },
		{ 2, -2, 3 },
	},
	{
		{ 1, 2, 2 },
		{ 2, 1, 2 },
		{ 2, 2, 3 },
	},
	{
		{ -1, 2, 2 },
		{ -2, 1, 2 },
		{ -2, 2, 3 },
	}
};

void tryNextTriplet(std::vector<long long> parent)
{
	long long perimeter = parent[0] + parent[1] + parent[2];
	if (perimeter < treshold) {
		if (parent[2] % (parent[0] - parent[1]) == 0) {
			finalSum += (treshold - 1) / perimeter;
		}
		for (auto &it : matrices) {
			tryNextTriplet(std::vector < long long > {
				it[0][0] * parent[0] + it[0][1] * parent[1] + it[0][2] * parent[2],
				it[1][0] * parent[0] + it[1][1] * parent[1] + it[1][2] * parent[2],
				it[2][0] * parent[0] + it[2][1] * parent[1] + it[2][2] * parent[2],
			});
		}
	}
}

int main()
{	
	sw.start();

	std::vector<long long> baseTriplet = { 3, 4, 5 };

	tryNextTriplet(baseTriplet);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}