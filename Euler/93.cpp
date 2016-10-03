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

class Number {
public:
	Number(long long num) : numerator(num), denominator(1) {}

	Number operator +(const Number& r) {
		return Number(numerator*r.denominator + r.numerator*denominator, r.denominator*denominator);
	}
	Number operator -(const Number& r) {
		return Number(numerator*r.denominator - r.numerator*denominator, r.denominator*denominator);
	}
	Number operator *(const Number& r) {
		return Number(numerator*r.numerator, r.denominator*denominator);
	}
	Number operator /(const Number& r) {
		return Number(numerator*r.denominator, r.numerator*denominator);
	}
	long long isInteger() { return ((denominator != 0 && numerator % denominator == 0 && numerator * denominator > 0) ? numerator / denominator : 0); };

private:
	Number(long long num, long long den) : numerator(num), denominator(den) {}
	long long numerator, denominator;
};

std::set<long long> candidates;

void calculate(std::vector<Number> numbers)
{
	if (numbers.size() == 1) {
		candidates.insert(numbers.front().isInteger());
	}
	for (long long position = 1; position < numbers.size(); ++position) {
		std::vector<Number> newN = numbers;
		newN[position - 1] = newN[position - 1] + newN[position];
		newN.erase(newN.begin() + position);
		calculate(newN);
		
		newN = numbers;
		newN[position - 1] = newN[position - 1] - newN[position];
		newN.erase(newN.begin() + position);
		calculate(newN);
		
		newN = numbers;
		newN[position - 1] = newN[position - 1] * newN[position];
		newN.erase(newN.begin() + position);
		calculate(newN);
		
		newN = numbers;
		newN[position - 1] = newN[position - 1] / newN[position];
		newN.erase(newN.begin() + position);
		calculate(newN);
	}
}

long long consecutives(std::vector<long long> numbers)
{
	candidates.clear();
	for (auto &it1 : numbers) {
		for (auto &it2 : numbers) {
			if (it2 != it1) {
				for (auto &it3 : numbers) {
					if (it3 != it1 && it3 != it2) {
						for (auto &it4 : numbers) {
							if (it4 != it1 && it4 != it2 && it4 != it3) {
								calculate(std::vector<Number> {it1, it2, it3, it4});
							}
						}
					}
				}
			}
		}
	}
	long long last = -1;
	for (auto &it : candidates) {
		if (last + 1 != it) {
			return last;
		}
		last = it;
	}
	assert(false);
	return -1;
}

StopWatch sw;

int main()
{	
	sw.start();

	long long treshold = 20;
	long long maxres = 0;
	std::string maxresstr;
	for (long long i1 = 4; i1 <= treshold; ++i1) {
		for (long long i2 = 3; i2 < i1; ++i2) {
			for (long long i3 = 2; i3 < i2; ++i3) {
				for (long long i4 = 1; i4 < i3; ++i4) {
					long long res = consecutives(std::vector < long long > {i4, i3, i2, i1});
					std::cout << i4 << " " << i3 << " " << i2 << " " << i1 << " : " << res << std::endl;
					if (res > maxres) {
						maxres = res;
						std::stringstream ss;
						ss << i4 << i3 << i2 << i1;
						maxresstr = ss.str();
					}
				}
			}
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << maxresstr;// long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}