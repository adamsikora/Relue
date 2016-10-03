#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>

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


StopWatch sw;

int main()
{	
	sw.start();

	long long count = 0;

	std::vector<long long> cubes;
	for (long long i = 1; i < million; ++i) {
		cubes.push_back(i*i*i);
	}

	for (long long digits = 1;; ++digits) {
		long long half = 1;
		long long end = 10;
		for (long long numb = 1; numb < (digits + 1) / 2; ++numb) {
			half *= 10;
			end *= 10;
		}
		while (half < end) {
			long long pandigit = half;
			long long drain = half;
			if (digits % 2 == 1) {
				drain /= 10;
			}
			while (drain) {
				pandigit *= 10;
				pandigit += drain % 10;
				drain /= 10;
			}

			long long ways = 0;
			for (auto &it : cubes) {
				if (it >= pandigit) {
					break;
				}
				long long potsquare = pandigit - it;
				long long pot = long long(sqrt(potsquare));
				if (potsquare == pot*pot) {
					++ways;
				}
			}
			if (ways == 4) {
				++count;
				std::cout << count << ": " << pandigit << std::endl;
				finalSum += pandigit;
				if (count == 5) {
					goto fin;
				}
			}

			++half;
			//std::cout << pandigit;
			//std::cin.ignore();
		}
	}
fin:;
	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}