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

const long long dicesides = 12;
const long long treshold = 20;
const long long notUsed = 10;
const long long desired = 70;

std::vector<unsigned long long> getFactorial(long long to)
{
	std::vector<unsigned long long> result;
	result.push_back(1);
	for (long long i = 1; i < to; ++i) {
		result.push_back(result.back()*i);
	}
	return result;
}

std::vector<unsigned long long> factorials = getFactorial(treshold + 1);

void proceed(long long all, long long index, long long sum, std::vector<long long> multip)
{
	if (all == treshold) {
		if (sum == desired) {
			unsigned long long multiplicity = factorials[treshold];
			for (long long i = 0; i < dicesides; ++i) {
				assert(multiplicity % factorials[multip[i]] == 0);
				multiplicity /= factorials[multip[i]];
			}
			finalSum += multiplicity;
		}
	}
	else if (all < treshold && index < dicesides) {
		std::vector<long long> newmul = multip;
		++newmul[index];
		 
		proceed(all + 1, index, sum + (all < notUsed ? 0 : index + 1), std::move(newmul));
		proceed(all, index + 1, sum, multip);
	}
}

StopWatch sw;

int main()
{	
	sw.start();
	
	std::vector<long long> vec(dicesides, 0);
	proceed(0, 0, 0, vec);

	//std::cout << megaprime << std::endl;
	//std::cout << root << std::endl;
	//
	//recurse(1, 0);

	sw.stop();
	std::cout << "it took: " << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::string ans = answer.str();
	//answer << finalSum % ttmath::UInt<4>("10 000 000 000 000 000");
	std::cout << "Answer is: " << ans << std::endl;
	ClipboardIt(ans);
	std::cin.ignore();
	return EXIT_SUCCESS;
}