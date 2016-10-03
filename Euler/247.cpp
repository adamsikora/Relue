#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>

#include <set>
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

long long finalSum = 0;

double calculateWidth(std::pair<double, double> position) {
	double b = position.second - position.first;
	return (-b + sqrt(b*b + 4)) / 2 - position.first;
}

struct Square {
	Square(std::pair<double, double> position, std::pair<long long, long long> stacked)
		: width(calculateWidth(position)), position(position), stacked(stacked) {}

	const double width;
	const std::pair<double, double> position;
	const std::pair<long long, long long> stacked;
};

std::pair<long long, long long> targetStacked(3, 3);
const long long target = 20;

StopWatch sw;

int main()
{	
	sw.start();

	std::map<double, Square> candidates;

	Square init(std::pair < double, double > {1.0, 0.0}, std::pair < long long, long long > {0, 0});
	
	candidates.emplace(init.width, init);

	long long got = 0;
	long long index = 1;

	while (true) {
		auto it = --(candidates.end());
		if (it->second.stacked == targetStacked) {
			std::cout << ++got << std::endl;
			if (got == target) {
				finalSum = index;
				break;
			}
		}
		Square up(
			std::pair < double, double > {it->second.position.first, it->second.position.second + it->first},
			std::pair < long long, long long > {it->second.stacked.first, it->second.stacked.second + 1}
		);
		Square left(
			std::pair < double, double > {it->second.position.first + it->first, it->second.position.second},
			std::pair < long long, long long > {it->second.stacked.first + 1, it->second.stacked.second}
		);

		candidates.erase(it);
		candidates.emplace(up.width, up);
		candidates.emplace(left.width, left);

		++index;
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}