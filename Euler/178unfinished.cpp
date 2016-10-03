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

const long long truePandig = (1 << 10) - 1;

long long maxPos = 40;

void recurse(long long position, long long lastDig, long long pandig, long long maxPos)
{
	if (position == maxPos) {
		if (pandig == truePandig) {
			finalSum++;
		}
	}
	else {
		if (lastDig > 0) {
			recurse(position + 1, lastDig - 1, (pandig & (1 << (lastDig - 1))) ? pandig : (pandig + (1 << (lastDig - 1))), maxPos);
		}
		if (lastDig < 9) {
			recurse(position + 1, lastDig + 1, (pandig & (1 << (lastDig + 1))) ? pandig : (pandig + (1 << (lastDig + 1))), maxPos);
		}
	}
}

int main()
{
	StopWatch sw;
	sw.start();

	for (int digs = 5; digs < maxPos; digs++) {
		std::cout << digs << std::endl;
		for (int i = 1; i < 10; i++) {
			recurse(1, i, 1 << i, digs);
		}
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