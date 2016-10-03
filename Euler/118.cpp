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

long long finalSum = 0;

std::vector<long long> correct(10, 0);

const long long allDigs = (1 << 10) - 2;

void getSets(long long numb, long long length, long long elements, const std::set<long long>& isPrime) {
	if (length > numb) {
		if (isPrime.count(numb)) {
			correct[elements] += 1;
		}
	}
	else {
		if (isPrime.count(numb % length)) {
			getSets(numb / length, 10, elements + 1, isPrime);
		}
		getSets(numb, length * 10, elements, isPrime);
	}
}

void process(long long numb, long long digits, const std::set<long long>& isPrime) {
	if (digits == allDigs) {
		getSets(numb, 10, 1, isPrime);
	}
	else {
		for (long long i = 1; i < 10; ++i) {
			if (!(digits & 1 << i)) {
				process(numb * 10 + i, digits + (1 << i), isPrime);
			}
		}
	}
}

StopWatch sw;

int main()
{	
	sw.start();

	std::vector<long long> primes = getPrimes(billion * 10);

	std::set<long long> isPrime;

	for (auto &it : primes) {
		isPrime.insert(it);
	}

	process(0, 0, isPrime);

	std::vector<long long> factorial(10, 1);
	for (int i = 1; i < 10; ++i) {
		factorial[i] = i*factorial[i - 1];
	}

	for (int i = 1; i < 10; ++i) {
		std::cout << correct[i] << " " << factorial[i] << std::endl;
		finalSum += correct[i] / factorial[i];
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