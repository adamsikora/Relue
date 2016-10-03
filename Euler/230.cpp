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

std::string finalSum;

unsigned long long pwr(unsigned long long n, unsigned long long exp)
{
	unsigned long long res = 1;
	for (unsigned long long i = 0; i < exp; ++i) {
		res *= n;
	}
	return res;
}

StopWatch sw;

int main()
{	
	sw.start();

	std::vector<std::pair<unsigned long long, unsigned long long>> line;
	line.emplace_back(0, 1);
	line.emplace_back(1, 1);
	for (long long i = 0; i < 88; ++i) {
		unsigned long long first = (line.end() - 1)->first + (line.end() - 1)->second;
		unsigned long long second = (line.end() - 1)->second + (line.end() - 2)->second;
		line.emplace_back(first, second);
	}

	std::string a = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679", b = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";
	//std::string a = "1415926535", b = "8979323846";
	unsigned long long length = 100;
	for (long long i = 17; i >= 0; --i) {
		unsigned long long numb = (127 + 19 * i)*pwr(7, i);
		unsigned long long position = (numb - 1) / length;
		unsigned long long it = 0;
		while (line[++it].second <= position);
		unsigned long long totalposition = line[it].first + position;
		while (true) {
			totalposition -= line[it].second;
			if (totalposition < 2) {
				if (totalposition == 1) {
					std::cout << b[(numb - 1) % length];
					finalSum += b[(numb - 1) % length];
				}
				if (totalposition == 0) {
					std::cout << a[(numb - 1) % length];
					finalSum += a[(numb - 1) % length];
				}
				break;
			}
			else {
				while (line[--it].first > totalposition);
			}
		}
	}
	std::cout << std::endl;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}