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
const long long trillion = million * million;

long long finalSum = 0;

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> & l, const std::pair<T, U> & r) {
	return{ l.first + r.first, l.second + r.second };
}

const long long maxSteps = trillion;
const long long maxDepth = 50;

std::pair<long long, long long> position = { 0, 0 };
long long direction = 0;
long long currSteps = 0;

std::pair<long long, long long> move[4] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

void a(long long depth);
void b(long long depth);

void addStep()
{
	if (++currSteps == maxSteps) {
		std::cout << currSteps << ": " << position.first << "," << position.second << std::endl;
	}
	if (currSteps % billion == 0) {
		std::cout << currSteps / billion << "B: " << position.first << "," << position.second << std::endl;
	}
}

void a(long long depth)
{
	//aRbFR
	if (depth < maxDepth) { a(depth + 1); }

	direction = (direction + 1) % 4;

	if (depth < maxDepth) { b(depth + 1); }

	position = position + move[direction];
	addStep();

	direction = (direction + 1) % 4;
}

void b(long long depth)
{
	//LFaLb
	direction = (direction + 3) % 4;

	position = position + move[direction];
	addStep();

	if (depth < maxDepth) { a(depth + 1); }

	direction = (direction + 3) % 4;

	if (depth < maxDepth) { b(depth + 1); }
}

int main()
{
	StopWatch sw;
	sw.start();

	position = position + move[direction];
	addStep();

	a(1);
	
	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}