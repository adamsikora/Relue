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
#include <array>

#include <math.h>

//#include <boost/circular_buffer.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/functional/hash.hpp>
//#include <boost/rational.hpp>
//#include <boost/bimap.hpp>
//#include <boost/bimap/set_of.hpp>
//#include <boost/bimap/multiset_of.hpp>
//#include <boost\multiprecision\cpp_int.hpp>
//#include <boost\multiprecision\cpp_dec_float.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"
#include "PythagoreanTriples.h"
#include "IntegerExponent.h"
#include "ModuloPrimeCombinations.h"

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
const uint64_t billion = thousand * million; // 10^9
const uint64_t trillion = million * million; // 10^12
const uint64_t quadrillion = million * billion; // 10^15
const uint64_t quintillion = billion * billion; // 10^18

int64_t finalSum;

const int64_t modulo = 100 * million;
const int64_t threshold = trillion;

StopWatch sw;

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		item.erase(0, 1);
		item.erase(item.size() - 1, 1);
		result.push_back(item);
	}
	return result;
}


int main()
{
	sw.start();

	std::ifstream t("words.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string allWords = buffer.str();
	auto words = split(allWords, ',');

	std::map<std::string, std::vector<std::string>> anagrams;
	for (auto &word : words) {
		std::string sorted = word;
		std::sort(sorted.begin(), sorted.end());
		anagrams[sorted].push_back(word);
	}
	std::map<int64_t, std::vector<std::pair<std::string, std::vector<std::string>>>> monster;
	for (auto& anagram : anagrams) {
		if (anagram.second.size() > 1) {
			monster[anagram.first.size()].push_back(anagram);
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer.precision(4);
	answer << std::fixed << finalSum;
	std::ofstream file;
	file.open("Euler.txt");
	file << answer.str();
	file.close();
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}