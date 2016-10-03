#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <set>
#include <map>
#include <vector>

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

double finalSum = 0;

class Counts
{
public:
	Counts() : state(0), count(0) {};
	Counts(long long state, long long count) : state(state), count(count) {};

	long long state;
	long long count;
};

std::vector<std::map<long long, long long>> configs(1, std::map<long long, long long>{std::pair<long long, long long>(1, 1), std::pair<long long, long long>(2, 1), std::pair<long long, long long>(3, 1), });

bool compatible(long long state1, long long state2)
{
	while (state1 > 0) {
		if (state2 == 0) {
			std::cout << "chyba";
		}
		if (state1 % 4 == state2 % 4) {
			return false;
		}
		else {
			state1 /= 4;
			state2 /= 4;
		}
	}
	if (state2 > 0) {
		std::cout << "chyba";
	}
	return true;
}

void tiler(int row, int currTile, int lastTile, long long upState, long long downState)
{
	if (currTile == 2 * row) {
		long long count = 0;
		for (auto it : configs[row - 2]) {
			if (compatible(upState, it.first)) {
				count += it.second;
			}
		}
		auto iter = configs[row - 1].find(downState);
		if (iter != configs[row - 1].end()) {
			iter->second += count;
		}
		else {
			configs[row - 1].insert(std::pair<long long, long long>(downState, count));
		}
	}
	else {
		for (int i = 1; i < 4; i++) {
			if (lastTile != i) {
				tiler(row, currTile + 1, i, ((currTile % 2 == 0) ? 4 * upState + i : upState), ((currTile % 2 == 1) ? 4 * downState + i : downState));
			}
		}
	}
}

int main()
{
	StopWatch sw;
	sw.start();

	for (int row = 2; row < 9; row++) {
		std::cout << row << std::endl;
		configs.push_back(std::map<long long, long long>());
		tiler(row, 1, 0, 0, 0);
	}

	for (std::pair<long long, long long> it : configs.back()) {
		finalSum += it.second;
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