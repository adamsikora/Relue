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

#include "boost\circular_buffer.hpp"

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

const long long teight = million * 100;
const long long treshold = trillion;

long long finalSum;

const long long boardSize = 40;
const long long diceSides = 4;

const double sixteenth = 1.0 / 16.0;

std::vector<double> rolls(2*diceSides + 1, 0);

double setRolls(long long diceSides)
{
	for (long long i = 0; i < diceSides; ++i) {
		rolls[i + 2] = rolls[2 * diceSides - i] = double(i + 1) / (diceSides*diceSides);
	}
	double twoDoubles = 1.0 / (diceSides*diceSides);
	rolls[0] = twoDoubles / diceSides;
	for (long long i = 2; i <= 2*diceSides; i += 2) {
		rolls[i] -= twoDoubles / (diceSides*diceSides);
	}

	double sum = 0.0;
	for (auto &it : rolls) {
		sum += it;
	}
	return abs(1.0 - sum);
}

const std::set<long long> rail{ 5, 15, 25, 35 };
const std::set<long long> util{ 12, 28 };
const std::set<long long> cc{ 2, 17, 33 };
const std::set<long long> ch{ 7, 22, 36 };
const long long go = 0;
const long long jail = 10;
const long long g2j = 30;

void resolveProbs(double probability, long long index, std::vector<double>& probs)
{
	if (index == g2j) {
		probs[jail] += probability;
	}
	else if (cc.count(index)) {
		probs[go] += probability*sixteenth;
		probs[jail] += probability*sixteenth;
		probs[index] += probability*14*sixteenth;
	}
	else if (ch.count(index)) {
		probs[go] += probability*sixteenth;
		probs[jail] += probability*sixteenth;
		probs[11] += probability*sixteenth;
		probs[24] += probability*sixteenth;
		probs[39] += probability*sixteenth;
		probs[5] += probability*sixteenth;
		auto railiter = rail.upper_bound(index);
		if (railiter == rail.end()) { railiter = rail.begin(); }
		probs[*railiter] += probability * 2 * sixteenth;
		auto utiliter = util.upper_bound(index);
		if (utiliter == util.end()) { utiliter = util.begin(); }
		probs[*utiliter] += probability*sixteenth;
		resolveProbs(probability*sixteenth, index - 3, probs);
		probs[index] += probability * 6 * sixteenth;
	}
	else {
		probs[index] += probability;
	}
}

double upgradeProbs(std::vector<double>& oldProbs)
{
	std::vector<double> newProbs(boardSize, 0.0);

	for (long long i = 0; i < boardSize; ++i) {
		resolveProbs(oldProbs[i] * rolls[0], jail, newProbs);
		for (long long j = 2; j <= 2 * diceSides; ++j) {
			resolveProbs(oldProbs[i] * rolls[j], (i + j) % boardSize, newProbs);
		}
	}
	oldProbs = newProbs;
	double sum = 0.0;
	for (auto &it : newProbs) {
		sum += it;
	}
	return abs(1.0 - sum);
}

StopWatch sw;

int main()
{	
	sw.start();

	std::cout << "roll sum differs from 1 by: " << setRolls(diceSides) << std::endl;

	std::vector<double> probabilities(boardSize, 1.0 / boardSize);

	double sigma = 1.0;
	long long i = 0;
	while (++i < thousand) {
		upgradeProbs(probabilities);
	}
	std::cout << "total probs differ from 1 by: " << upgradeProbs(probabilities) << std::endl;

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}