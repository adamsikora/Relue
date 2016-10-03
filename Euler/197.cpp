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

std::vector<double> us = { -1 };

double f(double x)
{
	return int(pow(2, 30.403243784 - x*x)) * 1e-9;
}

double u(int n)
{
	double toret;
	if (n > us.size() - 1) {
		toret = f(u(n - 1));
		us.push_back(toret);
	}
	else
		toret = us[n];
	return toret;
}

int main()
{
	StopWatch sw;
	sw.start();

	int i = 0;
	while (abs(u(i + 2) - u(i)) > 1e-10) {
		i += 100;
	}

	finalSum = u(i) + u(i + 1);

   sw.stop();
   std::cout << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << std::fixed << std::setprecision(9) << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}