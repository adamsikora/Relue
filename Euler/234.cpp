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

long long finalSum = 0;

int main()
{
	StopWatch sw;
	sw.start();

	const long long treshold = 999966663333i64;

	std::vector<long long> primes = getPrimes(2*int(sqrt(treshold)));
	while (primes[primes.size() - 2] >= sqrt(treshold)) {
		primes.pop_back();
	}
	std::cout << primes[primes.size() - 2] * primes[primes.size() - 2] << std::endl;
	std::cout << primes.back() * primes.back() << std::endl;
	std::cout << treshold - primes.back() * primes.back() << std::endl;
	std::cout << treshold - primes[primes.size() - 2] * primes[primes.size() - 2] << std::endl;

	long long itis = 0;
	long long isnt = 0;
	long long counter = 0;
	long long max = 0;
	for (auto it = primes.begin(); it != primes.end() - 1; it++) {
		const long long first = *it;
		const long long second = *(it + 1);
		long long numb = first * first + first;
		bool is = false;
		while (numb < second * second) {
			if (numb % second != 0 && numb <= treshold) {
				is = true;
				counter++;
				if (numb > max) max = numb;
				//std::cout << first << " " << second << " " << numb << std::endl;
				finalSum += numb;
			}
			numb += first;
		}
		numb = second * second - second;
		while (numb > first * first) {
			if (numb % first != 0 && numb <= treshold) {
				is = true;
				counter++;
				if (numb > max) max = numb;
				//std::cout << first << " " << second << " " << numb << std::endl;
				finalSum += numb;
			}
			numb -= second;
		}
		if (is) {
			itis++;
		}
		else {
			std::cout << "isnt" << first << " " << second << std::endl;
			isnt++;
		}
	}
	std::cout << itis << " " << isnt << std::endl;
	std::cout << counter << std::endl;
	std::cout << max << std::endl;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}