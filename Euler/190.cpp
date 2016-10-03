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

int main()
{
	StopWatch sw;
	sw.start();

	std::vector<int> partitions;

	for (int i = 2; i <= 15; i++) {
		double p = 1;
		for (int j = 1; j <= i; j++) {
			p *= pow(2 * j, j);
		}
		p /= pow(i + 1, i*(i + 1) / 2);
		finalSum += floor(p);
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