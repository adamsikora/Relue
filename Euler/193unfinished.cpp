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

double finalSum = 0;

long long treshold = 1i64 << 50;
long long sqrttreshold = static_cast<long long>(sqrt(treshold));

std::vector<long long> primes = getPrimes(sqrttreshold);

void squareIt(long long maxMultiples, long long currMultiples, long long index, long long value)
{
	if (currMultiples == maxMultiples) {
		if (maxMultiples % 2 == 1) {
			//std::cout << value << " " << (treshold - 1) / (value*value) << std::endl;
			finalSum -= (treshold-1) / (value*value);
		}
		else {
			//std::cout << value << " " << (treshold - 1) / (value*value) << std::endl;
			finalSum += (treshold-1) / (value*value);
		}
	}
	else {
		for (long long i = index + 1; i < primes.size(); i++) {
			if (value * primes[i] >= sqrttreshold) {
				break;
			}
			else {
				squareIt(maxMultiples, currMultiples + 1, i, value*primes[i]);
			}
		}
	}
}

int main()
{
	StopWatch sw;
	sw.start();

	long long multiple = 1;
	long long nMultiples = 0;
	while (multiple < sqrttreshold) {
		multiple *= primes[nMultiples];
		nMultiples++;
	}
	nMultiples--;

	finalSum = treshold;

	for (int i = 1; i <= nMultiples; i++) {
		std::cout << i << std::endl;
		squareIt(i, 0, -1, 1);
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