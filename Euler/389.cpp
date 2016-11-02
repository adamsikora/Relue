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
#include <boost\multiprecision\cpp_int.hpp>
#include <boost\multiprecision\cpp_dec_float.hpp>

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

typedef boost::multiprecision::cpp_int unlimitedInt;

boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>> finalSum(0);

const int64_t modulo = 100 * million;
const int64_t threshold = trillion;

StopWatch sw;


int main()
{
	sw.start();

	std::vector<int64_t> dices{ 1, 4, 6, 8, 12, 20 };
	std::vector<std::vector<unlimitedInt>> throws(dices.size(), std::vector<unlimitedInt>());

	
	throws[0] = std::vector<unlimitedInt>(1, 1);
	for (int64_t i = 1, size = 1; i < dices.size(); ++i) {
		size *= dices[i];
		throws[i] = std::vector<unlimitedInt>(size, 0);
	}
	for (int64_t i = 0; i < dices.size() - 1; ++i) {
		std::vector<unlimitedInt> temp(throws[i + 1].size(), 0);
		std::vector<unlimitedInt> nextTemp(throws[i + 1].size(), 0);
		for (int64_t l = 0; l < dices[i + 1]; ++l) {
			temp[l] = 1;
		}
		unlimitedInt power = 1;
		for (int64_t p = 1; p < throws[i].size(); ++p) {
			power *= dices[i + 1];
		}
		for (int64_t j = 0; j < throws[i].size(); ++j) {
			if (j % 100 == 0) {
				std::cout << dices[i + 1] << " " << j << std::endl;
			}
			//if (j < 100 && j > 0) {
			//	std::cout << throws[i + 1][j] << std::endl;
			//}
			int64_t k = 0;
			while (temp[k] == 0) {
				++k;
			}
			for (k; k < temp.size() && temp[k] > 0; ++k) {
				throws[i + 1][k] += temp[k] * throws[i][j] * power;
				if (j < throws[i].size() - 1) {
					for (int64_t l = 0; l < dices[i + 1]; ++l) {
						nextTemp[k + l + 1] += temp[k];
					}
				}
			}
			std::swap(nextTemp, temp);
			nextTemp = std::vector<unlimitedInt>(throws[i + 1].size(), 0);
			if (j < throws[i].size() - 1) {
				if (power % dices[i + 1] != 0) {
					std::cout << "bad\n";
				}
				power /= dices[i + 1];
			} else {
				if (power != 1) {
					std::cout << "bad\n";
				}
			}
		}
	}
	//std::cout << throws[dices.size() - 1][throws[dices.size() - 1].size() - 1] << std::endl;
	unlimitedInt num = 0, num2 = 0, denom = 0;
	for (int64_t i = 0; i < throws.back().size(); ++i) {
		num += throws.back()[i] * (i + 1);
		num2 += throws.back()[i] * (i + 1) * (i + 1);
		denom += throws.back()[i];
		//if (i < 100) {
		//	std::cout << i + 1 << " " << throws.back()[i] << std::endl;
		//}
	}
	unlimitedInt totNum = denom * num2 - num * num;
	unlimitedInt totDenom = denom * denom;

	finalSum = totNum.convert_to<boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>>>() / totDenom.convert_to<boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>>>();

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