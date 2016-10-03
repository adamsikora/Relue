#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

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

long long finalSum = 0;

const long long treshold = 10*thousand;
std::list<const unsigned long long> numbers;

StopWatch sw;

void test(const unsigned long long curr, const unsigned long long toAdd)
{
	if (toAdd > 0) {
		test(curr * 10 + 0, toAdd - 1);
		test(curr * 10 + 1, toAdd - 1);
		test(curr * 10 + 2, toAdd - 1);
	}
	else {
		for (auto it = numbers.begin(); it != numbers.end();) {
			if (curr < *it) {
				break;
			}
			if (curr % *it == 0) {
				finalSum += curr / *it;
				it = numbers.erase(it);
				if (numbers.size() % 100 == 0 || numbers.size() < 100) {
					std::cout << numbers.size() << ": " << curr << std::endl;
				}
				if (numbers.empty()) {
					sw.stop();
					std::cout << sw.getLastElapsed() << std::endl;

					std::stringstream answer;
					answer << long long(finalSum);
					std::cout << "Answer is: " << answer.str() << std::endl;
					ClipboardIt(answer.str());
					std::cin.ignore();
				}
			}
			else {
				++it;
			}
		}
	}
}

int main()
{	
	sw.start();

	for (int i = 1; i <= treshold; ++i) {
		numbers.push_back(i);
	}

	for (int i = 0;; ++i) {
		test(1, i);
		test(2, i);
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