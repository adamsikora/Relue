#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>
#include <cstddef>

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

double finalSum = 0.0;

const long long max = 4;
const long long modul = 16;

namespace arr {
	class Array {
	public:
		Array(std::vector<long long> v) {
			for (int i = 0; i < max; ++i) {
				a[i] = v[i];
			}
		}
		long long a[max];

		long long sum() const {
			long long result = 0;
			for (long long i = 0; i < max; ++i) {
				result += a[i];
			}
			return result;
		}

		long long multip() const {
			long long result = 0;
			for (long long i = 0; i < max; ++i) {
				result *= modul;
				result += a[i];
			}
			return result;
		}
	};

	bool operator==(Array const& a, Array const& b)
	{
		return a.multip() == b.multip();
	}

	std::size_t hash_value(Array const& b)
	{
		boost::hash<long long> hasher;
		return hasher(b.multip());
	}
}

StopWatch sw;

int main()
{	
	sw.start();
	
	long long batchesLeft = (1 << max) - 1;

	std::unordered_map<arr::Array, double, boost::hash<arr::Array>> states;
	states[arr::Array(std::vector<long long>(max, 1))] = 1.0;

	for (int i = batchesLeft; i > 1; --i) {
		std::unordered_map<arr::Array, double, boost::hash<arr::Array>> newstates;
		for (auto &it : states) {
			if (it.first.sum() == 1) {
				finalSum += it.second;
			}
			double currSum = it.first.sum();
			for (int j = 0; j < max; ++j) {
				if (it.first.a[j] > 0) {
					arr::Array newarr = it.first;
					--newarr.a[j];
					for (int k = j + 1; k < max; ++k) {
						++newarr.a[k];
					}
					if (newstates.count(newarr)) {
						newstates[newarr] += it.first.a[j] / currSum * it.second;
					}
					else {
						newstates[newarr] = it.first.a[j] / currSum * it.second;
					}
				}
			}
		}
		states = std::move(newstates);
	}

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