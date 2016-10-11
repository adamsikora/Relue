#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

#include <algorithm>
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

const uint64_t modulo = billion;
uint64_t threshold = million*billion;

StopWatch sw;

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}

struct Card {
	int number;
	char color;
};

int resolveValue(char c)
{
	switch (c) {
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'T': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
	}
}

struct Hand {
	Hand(std::vector<std::string> input)
	{
		if (input.size() != 5) {
			std::cout << "bad size\n";
		}
		for (int i = 0; i < 5; ++i) {
			cards[i].number = resolveValue(input[i][0]);
			cards[i].color = input[i][1];
		}
		if (cards[0].color == cards[1].color &&
				cards[1].color == cards[2].color &&
				cards[2].color == cards[3].color &&
				cards[3].color == cards[4].color) {
			sameSuit = true;
		}
		std::map<int, int> multipl;
		for (int i = 0; i < 5; ++i) {
			if (multipl.count(cards[i].number) > 0) {
				multipl[cards[i].number] += 1;
			} else {
				multipl[cards[i].number] = 1;
			}
		}
		for (auto it : multipl) {
			sorted.push_back({ it.second, it.first });
		}
		int check = 0;
		std::sort(sorted.begin(), sorted.end());
		for (auto val : sorted) {
			check += val.first;
		}
		if (check != 5) {
			std::cout << "bad count\n";
		}
		if (sorted.size() == 5) {
			if (sorted[0].second + 1 == sorted[1].second &&
					sorted[1].second + 1 == sorted[2].second &&
					sorted[2].second + 1 == sorted[3].second &&
					sorted[3].second + 1 == sorted[4].second) {
				consecutive = true;
			}
		}
		if (consecutive && sameSuit) {
			if (sorted.back().second = 14) {
				result = RoyalFlush;
			} else {
				result = StraightFlush;
			}
		} else if (sorted.back().first == 4) {
			result = FourofaKind;
		} else if (sorted.back().first == 3 && sorted[sorted.size() - 2].first == 2) {
			result = FullHouse;
		} else if (sameSuit) {
			result = Flush;
		} else if (consecutive) {
			result = Straight;
		} else if (sorted.back().first == 3) {
			result = ThreeofaKind;
		} else if (sorted.back().first == 2) {
			if (sorted[sorted.size() - 2].first == 2) {
				result = TwoPairs;
			} else {
				result = OnePair;
			}
		} else {
			result = HighCard;
		}
	}
	Card cards[5];
	bool sameSuit = false;
	bool consecutive = false;
	std::vector<std::pair<int, int>> sorted;
	enum ResultType {
		HighCard,
		OnePair,
		TwoPairs,
		ThreeofaKind,
		Straight,
		Flush,
		FullHouse,
		FourofaKind,
		StraightFlush,
		RoyalFlush
	} result;
};

bool operator>(const Hand& f, const Hand& s)
{
	if (f.result == s.result) {
		for (int i = f.sorted.size() - 1; i >= 0; --i) {
			if (f.sorted[i].second == s.sorted[i].second) {
				continue;
			} else {
				return f.sorted[i].second > s.sorted[i].second;
			}
		}
	} else {
		return f.result > s.result;
	}
	std::cout << "bad\n";
	return false;
}

int main()
{
	sw.start();

	std::ifstream input;
	input.open("poker.txt");

	for (int i = 0; i < 1000; ++i) {
		std::string line;
		std::getline(input, line);
		auto cards = split(line,  ' ');
		std::vector<std::string> firsthand, secondhand;
		for (int i = 0; i < 5; ++i) {
			firsthand.push_back(cards[i]);
			secondhand.push_back(cards[i+5]);
		}
		Hand f(firsthand);
		Hand s(secondhand);
		if (f > s) {
			++finalSum;
		}

	}

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