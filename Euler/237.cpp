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

const long long teight = million * 100;
const long long treshold = trillion;

long long finalSum = 0;

StopWatch sw;

class Ways {
public:
	Ways() : none(0), up(0), mid(0), down(0), wide(0), allup(0), alldown(0), allwide(0) {}
	long long none, up, mid, down, wide, allup, alldown, allwide;
};

int main()
{	
	sw.start();

	Ways ways;
	ways.wide = 1;
	for (long long i = 0; i < treshold; ++i) {
		Ways neways;
		neways.none = (ways.wide + ways.allwide) % teight;
		neways.up = (ways.wide + ways.allwide) % teight;
		neways.mid = (ways.wide) % teight;
		neways.down = (ways.wide + ways.allwide) % teight;
		neways.allup = (ways.up + ways.allup) % teight;
		neways.alldown = (ways.down + ways.alldown) % teight;
		neways.allwide = (ways.wide + ways.allwide) % teight;
		neways.wide = (ways.up + ways.mid + ways.down + ways.allup + ways.alldown) % teight;
		ways = neways;
		if (i % (10*million) == 0) {
			std::cout << i / million << "M" << std::endl;
		}
	}
	finalSum = ways.none;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}