#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

#include <limits>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>

#include <math.h>

//#include <boost/circular_buffer.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/functional/hash.hpp>
//#include <boost/rational.hpp>
//#include <boost/bimap.hpp>
//#include <boost/bimap/set_of.hpp>
//#include <boost/bimap/multiset_of.hpp>
//#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

#undef min
#undef max

struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

const uint64_t thousand = 1000;
const uint64_t million = thousand * thousand;
const uint64_t billion = thousand * million;
const uint64_t trillion = million * million;
const uint64_t quadrillion = million * billion;

int64_t finalSum = 0;

const uint64_t modulo = 100000007i64;
//uint64_t threshold = 10*million;

StopWatch sw;

enum Movement {
	None = 0,
	Incoming = 1,
	Outgoing = 2
};

void recurse(const std::pair<int64_t, int64_t>& previousRow, int64_t index, int64_t maxIndex, Movement fromLeft, int64_t currentRowEndings, std::unordered_map<int64_t, int64_t>& toSave)
{
	if (index == maxIndex) {
		if (toSave.count(currentRowEndings) > 0) {
			toSave[currentRowEndings] += previousRow.second;
		} else {
			toSave[currentRowEndings] = previousRow.second;
		}
	} else {
		Movement fromTop = Movement((previousRow.first >> (2 * index)) % 4);
		int64_t nIncoming = 0;
		if (fromLeft == Incoming) {
			++nIncoming;
		}
		if (fromTop == Incoming) {
			++nIncoming;
		}
		int64_t nOutgoing = 0;
		if (fromLeft == Outgoing) {
			++nOutgoing;
		}
		if (fromTop == Outgoing) {
			++nOutgoing;
		}

		if (nIncoming == 2 || nOutgoing == 2) {
			return; //invalid movement
		} else if (nIncoming == 1 && nOutgoing == 1) {
			recurse(previousRow, index + 1, maxIndex, None, currentRowEndings, toSave);
		} else if (nIncoming == 0 && nOutgoing == 0) {
			if (index + 1 < maxIndex) {
				recurse(previousRow, index + 1, maxIndex, Outgoing, currentRowEndings + (int64_t(Incoming) << (2 * index)), toSave);
				recurse(previousRow, index + 1, maxIndex, Incoming, currentRowEndings + (int64_t(Outgoing) << (2 * index)), toSave);
			} else {
				return;
			}
		} else if (nIncoming == 1 && nOutgoing == 0) {
			recurse(previousRow, index + 1, maxIndex, None, currentRowEndings + (int64_t(Incoming) << (2 * index)), toSave);
			if (index + 1 < maxIndex) {
				recurse(previousRow, index + 1, maxIndex, Incoming, currentRowEndings + (int64_t(None) << (2 * index)), toSave);
			} else {
				return;
			}
		} else if (nIncoming == 0 && nOutgoing == 1) {
			recurse(previousRow, index + 1, maxIndex, None, currentRowEndings + (int64_t(Outgoing) << (2 * index)), toSave);
			if (index + 1 < maxIndex) {
				recurse(previousRow, index + 1, maxIndex, Outgoing, currentRowEndings + (int64_t(None) << (2 * index)), toSave);
			} else {
				return;
			}
		} else {
			std::cout << "Impossible\n";
		}
	}
}

int64_t find(int64_t n)
{
	int64_t result = 0;

	std::unordered_map<int64_t, int64_t> rowEndings{ { 0, 1 } };
	for (int64_t i = 0; i < n; ++i) {
		std::unordered_map<int64_t, int64_t> nextRowEndings;
		for (auto &rowEnding : rowEndings) {
			recurse(rowEnding, 0, n, None, 0, nextRowEndings);
		}
		rowEndings = nextRowEndings;
	}

	return rowEndings[0];
}

int main()
{
	sw.start();

	std::vector<int64_t> calculated{ find(2), find(4) };
	std::vector<int64_t> rightResults{ 2, 88 };

	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i]/* % modulo*/ << " = " << rightResults[i]/* % modulo*/ << std::endl;
		if (calculated[i]/* % modulo*/ != rightResults[i]/* % modulo*/) {
			right = false;
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	if (right) {
		std::cout << "Tests passed successfully" << std::endl;
	} else {
		std::cout << "Tests failed" << std::endl;
	}

	sw.start();

	finalSum = find(10);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::ofstream file;
	file.open("Euler.txt");
	file << answer.str();
	file.close();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}