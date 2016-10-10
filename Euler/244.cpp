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
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost\multiprecision\cpp_int.hpp>

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

boost::multiprecision::cpp_int finalSum = 0;

const uint64_t modulo = 100000007i64;
//uint64_t threshold = 10*million;

StopWatch sw;

struct Configuration {
	std::array<int64_t, 16> sliders;
	int64_t emptyPosition;

	int64_t encode() {
		int64_t result = 0;
		for (int64_t i = 0; i < sliders.size(); ++i) {
			result += sliders[i] << i;
		}
		result += emptyPosition << 16;
		return result;
	}

	static Configuration decode(int64_t input) {
		Configuration result;
		for (int64_t i = 0; i < result.sliders.size(); ++i) {
			result.sliders[i] = (input & (1 << i)) == 0 ? 0 : 1;
		}
		result.emptyPosition = input / (1 << 16i64);
		return result;
	}
};

int64_t L(int64_t checksum, int64_t number) {
	return (243*checksum + 76 * number) % modulo;
}

int64_t R(int64_t checksum, int64_t number) {
	return (243 * checksum + 82 * number) % modulo;
}

int64_t U(int64_t checksum, int64_t number) {
	return (243 * checksum + 85 * number) % modulo;
}

int64_t D(int64_t checksum, int64_t number) {
	return (243 * checksum + 68 * number) % modulo;
}

int64_t find(Configuration start, Configuration end)
{
	std::vector<std::tuple<int64_t, int64_t, int64_t>> arr(1 << 20i64, { -1, 0, 0 });
	int64_t encodedEnd = end.encode();

	arr[start.encode()] = { 0, 0, 1 };
	int64_t currentPosition = 0;
	std::unordered_set<int64_t> currentPositions{ start.encode() };
	while (true) {
		++currentPosition;
		std::unordered_set<int64_t> newPositions;

		for (auto position : currentPositions) {
			Configuration config = Configuration::decode(position);
			const int64_t emptyPos = config.emptyPosition;
			if (emptyPos % 4 != 0) { //R
				Configuration newConfig = config;
				newConfig.emptyPosition = emptyPos - 1;
				std::swap(newConfig.sliders[emptyPos], newConfig.sliders[newConfig.emptyPosition]);
				int64_t encodedNew = newConfig.encode();
				if (std::get<0>(arr[encodedNew]) == -1 || std::get<0>(arr[encodedNew]) == currentPosition) {
					std::get<0>(arr[encodedNew]) = currentPosition;
					std::get<1>(arr[encodedNew]) += R(std::get<1>(arr[position]), std::get<2>(arr[position]));
					std::get<2>(arr[encodedNew]) += std::get<2>(arr[position]);
					newPositions.insert(encodedNew);
				}
			}
			if (emptyPos % 4 != 3) { //L
				Configuration newConfig = config;
				newConfig.emptyPosition = emptyPos + 1;
				std::swap(newConfig.sliders[emptyPos], newConfig.sliders[newConfig.emptyPosition]);
				int64_t encodedNew = newConfig.encode();
				if (std::get<0>(arr[encodedNew]) == -1 || std::get<0>(arr[encodedNew]) == currentPosition) {
					std::get<0>(arr[encodedNew]) = currentPosition;
					std::get<1>(arr[encodedNew]) += L(std::get<1>(arr[position]), std::get<2>(arr[position]));
					std::get<2>(arr[encodedNew]) += std::get<2>(arr[position]);
					newPositions.insert(encodedNew);
				}
			}
			if (emptyPos / 4 != 0) { //D
				Configuration newConfig = config;
				newConfig.emptyPosition = emptyPos - 4;
				std::swap(newConfig.sliders[emptyPos], newConfig.sliders[newConfig.emptyPosition]);
				int64_t encodedNew = newConfig.encode();
				if (std::get<0>(arr[encodedNew]) == -1 || std::get<0>(arr[encodedNew]) == currentPosition) {
					std::get<0>(arr[encodedNew]) = currentPosition;
					std::get<1>(arr[encodedNew]) += D(std::get<1>(arr[position]), std::get<2>(arr[position]));
					std::get<2>(arr[encodedNew]) += std::get<2>(arr[position]);
					newPositions.insert(encodedNew);
				}
			}
			if (emptyPos / 4 != 3) { //U
				Configuration newConfig = config;
				newConfig.emptyPosition = emptyPos + 4;
				std::swap(newConfig.sliders[emptyPos], newConfig.sliders[newConfig.emptyPosition]);
				int64_t encodedNew = newConfig.encode();
				if (std::get<0>(arr[encodedNew]) == -1 || std::get<0>(arr[encodedNew]) == currentPosition) {
					std::get<0>(arr[encodedNew]) = currentPosition;
					std::get<1>(arr[encodedNew]) += U(std::get<1>(arr[position]), std::get<2>(arr[position]));
					std::get<2>(arr[encodedNew]) += std::get<2>(arr[position]);
					newPositions.insert(encodedNew);
				}
			}
		}
		if (std::get<0>(arr[encodedEnd]) != -1) {
			return std::get<1>(arr[encodedEnd]);
		}

		currentPositions = newPositions;
	}

	return -1;
}

int main()
{
	sw.start();

	Configuration start{ { 0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1 }, 0 };
	Configuration endPreTest1{ { 0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1 }, 1 };
	Configuration endPreTest2{ { 0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1 }, 4 };
	Configuration endPreTest3{ { 0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1 }, 5 };
	Configuration endTest{ { 0,0,1,1, 0,1,1,1, 0,0,0,1, 0,0,1,1 }, 9 };
	Configuration endRun{ { 0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0 }, 0 };

	std::vector<int64_t> calculated{
		Configuration::decode(start.encode()).encode(),
		Configuration::decode(endTest.encode()).encode(),
		Configuration::decode(endRun.encode()).encode(),
		R(U(L(U(L(0, 1), 1), 1), 1), 1),
		find(start, endPreTest1),
		find(start, endPreTest2),
		find(start, endPreTest3),
		find(start, endTest)
	};
	std::vector<int64_t> rightResults{
		start.encode(),
		endTest.encode(),
		endRun.encode(),
		19761398,
		L(0, 1),
		U(0, 1),
		(U(L(0, 1), 1) + L(U(0, 1), 1)) % modulo,
		(R(U(L(U(L(0, 1), 1), 1), 1), 1) + R(U(L(L(U(0, 1), 1), 1), 1), 1)) % modulo
	};
	
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

	finalSum = find(start, endRun);

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