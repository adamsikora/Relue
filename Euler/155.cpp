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

#include <boost/circular_buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include <boost/rational.hpp>

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

unsigned long long finalSum = 0.0;

uint64_t treshold = 18;

StopWatch sw;

int main()
{	
	sw.start();

	std::vector<const std::set<boost::rational<uint64_t>>> D;
	std::set<boost::rational<uint64_t>> start;
	start.insert(boost::rational<uint64_t>(60));
	D.push_back(start);

	for (int i = 1; i < treshold; ++i) {
		std::set<boost::rational<uint64_t>> next;
		for (int j = 0; j < (i + 1) / 2; ++j) {
			int k = i - 1 - j;
			std::cout << i << " " << j << " " << k << std::endl;
			for (auto &it : D[j]) {
				for (auto &jt : D[k]) {
					next.insert(it + jt);
					next.insert((it * jt) / (it + jt));
				}
			}
		}
		D.push_back(next);
	}
	std::set<boost::rational<uint64_t>> all;
	for (int i = 0; i < treshold; ++i) {
		all.insert(D[i].begin(), D[i].end());
	}
	finalSum = all.size();

	sw.stop();
	std::cout << "it took: " << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::string ans = answer.str();
	std::cout << "Answer is: " << ans << std::endl;
	ClipboardIt(ans);
	std::cin.ignore();
	return EXIT_SUCCESS;
}