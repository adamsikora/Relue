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

std::vector<long long> newn(16, -1i64);

void recurse(long long nextPos, long long sum)
{
	long long carrySum;

	switch (nextPos) {

	case 3:
		carrySum = newn[0] + newn[1] + newn[2];
		for (int i = 0; i < 10; i++) {
			newn[nextPos] = i;
			recurse(nextPos + 1, carrySum + i);
		}
		break;

	case 7:
		carrySum = sum - (newn[4] + newn[5] + newn[6]);
		if (carrySum > -1 && carrySum < 10) {
			newn[nextPos] = carrySum;
			recurse(nextPos + 1, sum);
		}
		break;

	case 11:
		carrySum = sum - (newn[8] + newn[9] + newn[10]);
		if (carrySum > -1 && carrySum < 10) {
			newn[nextPos] = carrySum;
			recurse(nextPos + 1, sum);
		}
		break;

	case 12:
		if (newn[0] + newn[4] + newn[8] == newn[3] + newn[6] + newn[9]) {
			carrySum = sum - (newn[0] + newn[4] + newn[8]);
			if (carrySum > -1 && carrySum < 10) {
				newn[nextPos] = carrySum;
				recurse(nextPos + 1, sum);
			}
		}
		break;

	case 13:
		carrySum = sum - (newn[1] + newn[5] + newn[9]);
		if (carrySum > -1 && carrySum < 10) {
			newn[nextPos] = carrySum;
			recurse(nextPos + 1, sum);
		}
		break;

	case 14:
		carrySum = sum - (newn[2] + newn[6] + newn[10]);
		if (carrySum > -1 && carrySum < 10) {
			newn[nextPos] = carrySum;
			recurse(nextPos + 1, sum);
		}
		break;

	case 15:
		carrySum = newn[3] + newn[7] + newn[11];
		if (carrySum == newn[0] + newn[5] + newn[10] && carrySum == newn[12] + newn[13] + newn[14]) {
			carrySum = sum - carrySum;
			if (carrySum > -1 && carrySum < 10) {
				finalSum++;
				/*newn[15] = carrySum;
				for (int j = 0; j < 16; j++) {
					std::cout << newn[j] << " ";
					if ((j + 1) % 4 == 0) {
						std::cout << std::endl;
					}
				}
				std::cin.ignore();*/
			}
		}
		break;

	default:
		for (int i = 0; i < 10; i++) {
			newn[nextPos] = i;
			recurse(nextPos + 1, sum);
		}
		break;
	}
}

int main()
{
	StopWatch sw;
	sw.start();

	std::vector<long long> ns(16, -1i64);

	recurse(0, -1);

   sw.stop();
   std::cout << sw.getLastElapsed() << std::endl;

   std::stringstream answer;
   answer << long long(finalSum);
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}