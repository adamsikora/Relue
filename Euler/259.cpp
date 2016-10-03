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

#include <boost/circular_buffer.hpp>
#include <boost/lexical_cast.hpp>

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

unsigned long long finalSum = 0;
const long long tresh = 9;

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

std::set<long long> bingo;

void count(std::vector<Number> nums)
{
	if (nums.size() == 1) {
		bingo.insert(nums.back().isInteger());
	}
	else {
		const size_t size = nums.size() - 1;
		for (int i = 0; i < size; ++i) {
			std::vector<Number> newnums(size, Number(0));
			for (int j = 0; j < i; ++j) {
				newnums[j] = nums[j];
			}
			for (int j = i; j < size - 1; ++j) {
				newnums[j + 1] = nums[j + 2];
			}
			newnums[i] = nums[i] + nums[i + 1];
			count(newnums);
			newnums[i] = nums[i] - nums[i + 1];
			count(newnums);
			newnums[i] = nums[i] * nums[i + 1];
			count(newnums);
			newnums[i] = nums[i] / nums[i + 1];
			count(newnums);
		}
	}
}

long long proc = 0;

void getNext(long long curr, std::vector<Number> nums)
{
	if (curr <= tresh) {
		std::vector<Number> next = nums;
		next.push_back(curr);
		getNext(curr + 1, std::move(next));
		nums.back() = nums.back() * Number(10) + Number(curr);
		getNext(curr + 1, nums);
	}
	else {
		std::cout << ++proc << std::endl;
		count(nums);
	}
}

StopWatch sw;

int main()
{	
	sw.start();
	
	getNext(2, std::vector < Number > {1});

	for (auto &it : bingo) {
		finalSum += it;
	}

	sw.stop();
	std::cout << "it took: " << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::string ans = answer.str();
	std::cout << "Answer is: " << ans << std::endl;
	ClipboardIt(ans);
	std::cin.ignore();
	return EXIT_SUCCESS;
}