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

	int treshold = 2000;

	std::vector<long long> random(treshold*treshold+1, 0);
	
	long long i = 0;
	while (i <= treshold*treshold) {
		while (i < 56) {
			random[i] = (100003 - 200003 * i + 300007 * i*i*i) % 1000000 - 500000;
			i++;
		}
		random[i] = (random[i - 24] + random[i - 55] + 1000000) % 1000000 - 500000;
		i++;
	}

	std::vector<std::vector<long long>> arr(treshold, std::vector<long long>(treshold, 0));

	for (long long i = 0; i < treshold; i++) {
		for (long long j = 0; j < treshold; j++) {
			arr[i][j] = random[i*treshold + j + 1];
		}
	}

	long long maxSum = 0;

	for (long long i = 0; i < treshold; i++) {
		long long currSum = 0;
		for (long long j = 0; j < treshold; j++) {
			currSum += arr[i][j];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	for (long long i = 0; i < treshold; i++) {
		long long currSum = 0;
		for (long long j = 0; j < treshold; j++) {
			currSum += arr[j][i];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	for (long long i = 0; i < treshold; i++) {
		long long currSum = 0;
		for (long long j = 0; j < treshold - i; j++) {
			currSum += arr[i + j][j];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	for (long long j = 1; j < treshold; j++) {
		long long currSum = 0;
		for (long long i = 0; i < treshold - j; i++) {
			currSum += arr[i][j + i];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	for (long long i = 0; i < treshold; i++) {
		long long currSum = 0;
		for (long long j = 0; j < i + 1; j++) {
			currSum += arr[i - j][j];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	for (long long j = 1; j < treshold; j++) {
		long long currSum = 0;
		for (long long i = 0; i < j + 1; i++) {
			currSum += arr[i][j - i];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}


	finalSum = maxSum;

	/*std::vector<std::vector<int>> arr(treshold, std::vector<int>(treshold, 0));

	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<> dist(-1000, 1000);

	for (int i = 0; i < treshold; i++) {
		for (int j = 0; j < treshold; j++) {
			arr[i][j] = dist(gen);
		}
	}

	int maxSum = 0;

	for (int i = 0; i < treshold; i++) {
		int currSum = 0;
		for (int j = 0; j < treshold; j++) {
			currSum += arr[j][i];
			if (currSum < 0) {
				currSum = 0;
			}
			else if (currSum > maxSum) {
				maxSum = currSum;
			}
		}
	}
	finalSum = maxSum;*/

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}