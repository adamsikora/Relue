#include <iostream>
#include <iomanip>
#include <assert.h>

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

double finalSum = 0.0;

const long long max = 30;
const long long steps = 50;

std::vector<std::vector<double>> grid(max, std::vector<double>(30, 0.0));

void nextStep(std::vector<std::vector<double>>& state)
{
	std::vector<std::vector<double>> nextGrid = grid;
	for (long long y = 0; y < max; ++y) {
		for (long long x = 0; x < max; ++x) {
			assert(state[y][x] >= 0.0);
			if (state[y][x] != 0.0) {
				if (y == 0) {
					if (x == 0) {
						nextGrid[y + 1][x] += state[y][x] / 2.0;
						nextGrid[y][x + 1] += state[y][x] / 2.0;
					}
					else if (x == max - 1) {
						nextGrid[y + 1][x] += state[y][x] / 2.0;
						nextGrid[y][x - 1] += state[y][x] / 2.0;
					}
					else {
						nextGrid[y + 1][x] += state[y][x] / 3.0;
						nextGrid[y][x + 1] += state[y][x] / 3.0;
						nextGrid[y][x - 1] += state[y][x] / 3.0;
					}
				}
				else if (y == max - 1) {
					if (x == 0) {
						nextGrid[y - 1][x] += state[y][x] / 2.0;
						nextGrid[y][x + 1] += state[y][x] / 2.0;
					}
					else if (x == max - 1) {
						nextGrid[y - 1][x] += state[y][x] / 2.0;
						nextGrid[y][x - 1] += state[y][x] / 2.0;
					}
					else {
						nextGrid[y - 1][x] += state[y][x] / 3.0;
						nextGrid[y][x + 1] += state[y][x] / 3.0;
						nextGrid[y][x - 1] += state[y][x] / 3.0;
					}
				}
				else if (x == 0) {
					nextGrid[y + 1][x] += state[y][x] / 3.0;
					nextGrid[y - 1][x] += state[y][x] / 3.0;
					nextGrid[y][x + 1] += state[y][x] / 3.0;
				}
				else if (x == max - 1) {
					nextGrid[y + 1][x] += state[y][x] / 3.0;
					nextGrid[y - 1][x] += state[y][x] / 3.0;
					nextGrid[y][x - 1] += state[y][x] / 3.0;
				}
				else {
					nextGrid[y + 1][x] += state[y][x] / 4.0;
					nextGrid[y - 1][x] += state[y][x] / 4.0;
					nextGrid[y][x + 1] += state[y][x] / 4.0;
					nextGrid[y][x - 1] += state[y][x] / 4.0;
				}
			}
		}
	}
	state = std::move(nextGrid);
}

int main()
{
	StopWatch sw;
	sw.start();

	std::vector<std::vector<std::vector<double>>> grids;

	for (long long y = 0; y < max; ++y) {
		for (long long x = 0; x < max; ++x) {
			std::vector<std::vector<double>> currGrid = grid;
			currGrid[y][x] = 1.0;
			for (long long r = 0; r < steps; ++r) {
				nextStep(currGrid);
			}
			grids.push_back(std::move(currGrid));
		}
	}

	for (long long y = 0; y < max; ++y) {
		for (long long x = 0; x < max; ++x) {
			double prob = 1.0;
			for (long long g = 0; g < max * max; ++g) {
				prob *= 1.0 - grids[g][y][x];
			}
			finalSum += prob;
		}
	}

   sw.stop();
   std::cout << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
	answer.precision(9);
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}