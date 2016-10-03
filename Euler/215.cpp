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

std::vector<long long> rows;

void recursor(long long currWidth, long long currSetup, long long maxWidth)
{
	if ((currWidth + 2 == maxWidth) || (currWidth + 3 == maxWidth)) {
		rows.push_back(currSetup);
	}
	else if (currWidth < maxWidth) {
		recursor(currWidth + 2, currSetup + (1i64 << (currWidth + 2)), maxWidth);
		recursor(currWidth + 3, currSetup + (1i64 << (currWidth + 3)), maxWidth);
	}
}

int main()
{
	StopWatch sw;
	sw.start();

	long long width = 32;
	long long height = 10;

	recursor(0, 0, width);

	std::vector<std::vector<bool>> compatibility(rows.size(), std::vector<bool>(rows.size(), false));

	for (int i = 0; i < rows.size(); i++) {
		for (int j = 0; j < rows.size(); j++) {
			if ((rows[i] & rows[j]) == 0) {
				compatibility[i][j] = true;
			}
		}
	}

	std::vector<long long> lastCounts(rows.size(), 0);
	std::vector<long long> currCounts(rows.size(), 0);

	for (int i = 0; i < rows.size(); i++) {
		for (int j = 0; j < rows.size(); j++) {
			if (compatibility[i][j]) {
				lastCounts[i]++;
			}
		}
	}

	for (int h = 2; h < height; h++) {
		currCounts = std::vector<long long>(rows.size(), 0);
		for (int i = 0; i < rows.size(); i++) {
			for (int j = 0; j < rows.size(); j++) {
				if (compatibility[i][j]) {
					currCounts[i] += lastCounts[j];
				}
			}
		}
		lastCounts = currCounts;
	}

	for (int i = 0; i < rows.size(); i++) {
		finalSum += currCounts[i];
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