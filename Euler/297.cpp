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

long long treshold = 100 * quadrillion;

std::set<long long> f;
std::map<long long, long long> counted;

long long count(long long numb)
{
	if (numb == 0) {
		return 0;
	}
	auto it = f.lower_bound(numb);
	if (*it != numb) {
		if (it != f.begin()) {
			--it;
		}
		else {
			assert(false);
		}
	}
	long long above = 0;
	if (counted.count(numb - *it)) {
		above = counted.find(numb - *it)->second;
	}
	else {
		above = count(numb - *it);
		counted[numb - *it] = above;
	}
	long long under = 0;
	if (counted.count(*it - 1)) {
		under = counted.find(*it - 1)->second;
	}
	else {
		under = count(*it - 1);
		counted[*it - 1] = under;
	}

	return numb - *it + 1 + above + under;
	//return numb - *it + 1 + count(numb - *it) + count(*it - 1);
}

StopWatch sw;

int main()
{	
	sw.start();

	long long first = 1;
	long long second = 1;
	int i = 0;

	while (second < treshold) {
		f.insert(second);
		std::cout << ++i << ": " << second << ", " << count(second - 1) << std::endl;
		long long next = first + second;
		first = second;
		second = next;
	}

	finalSum = count(treshold - 1);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}