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

long long finalSum;

long long threshold = 20*thousand;

StopWatch sw;

int main()
{	
	sw.start();

	long long first = 1;
	long long second = 1;
	long long plus = 6;

	std::vector<long long> cuboids(threshold, 0);

	for (long long x = 1; x <= threshold / 4; ++x) {
		for (long long y = 1; y <= x; ++y) {
			for (long long z = 1; z <= y; ++z) {
				long long area = x*y;
				long long length = x;
				long long cuboid = 0;
				while (true) {
					cuboid = 2 * (area + length * z + y * z);
					if (cuboid <= threshold) {
						++cuboids[cuboid];
					}
					else {
						break;
					}
					area += 2 * (length + y);
					length += 2;
				}
			}
		}
	}
	for (long long i = 0; i < threshold; ++i) {
		if (cuboids[i] == 1000) {
			finalSum = i;
			break;
		}
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