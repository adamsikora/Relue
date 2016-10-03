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
//#include <boost\multiprecision\cpp_int.hpp>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const uint64_t thousand = 1000;
const uint64_t million = thousand * thousand;
const uint64_t billion = thousand * million;
const uint64_t trillion = million * million;
const uint64_t quadrillion = million * billion;

/*boost::multiprecision::cpp_int*/ uint64_t finalSum = 0;

uint64_t modulo = 100 * million;

StopWatch sw;

uint64_t P(uint64_t floor, uint64_t room)
{
	bool floorMod = (floor % 2 == 0);
	bool roomMod = (room % 2 == 0);
	uint64_t floorHalf = floor / 2;
	uint64_t roomHalf = room / 2;
	uint64_t roomP1Half = (room + 1) / 2;
	uint64_t roomM1Half = (room - 1) / 2;
	floor %= modulo;
	room %= modulo;
	floorHalf %= modulo;
	roomHalf %= modulo;
	roomP1Half %= modulo;
	roomM1Half %= modulo;
	
	if (floor == 1) {
		return (roomMod ? roomHalf*(room+1) : room*roomP1Half) % modulo;
	} else {
		uint64_t start = ((floor*floor) / 2) % modulo;
		uint64_t constantRise = ((room - 1)*(2*floorHalf)) % modulo;
		uint64_t risingRise = (roomMod ? roomHalf*(room-1) : room*roomM1Half) % modulo;
		uint64_t adjustment = 0;

		if (roomMod) {
			if (floorMod) {
				adjustment = floor;
			} else {
				adjustment = modulo - 2* (floor / 2);
			}
		}

		//std::cout << start << std::endl << constantRise << std::endl << risingRise << std::endl << adjustment << std::endl;
		return (start + constantRise + risingRise + adjustment) % modulo;
	}
}

int main()
{
	sw.start();

	std::vector<uint64_t> calculated{ P(1, 1), P(1, 2), P(1, 3), P(1, 4), P(2, 1), P(6, 1), P(6, 2), P(6, 3), P(6, 4), P(10, 20), P(25, 75), P(99, 100) };
	std::vector<uint64_t> rightResults{ 1, 3, 6, 10, 2, 18, 31, 33, 48, 440, 4863, 19454 };
	
	bool right = true;
	for (uint64_t i = 0; i < calculated.size(); ++i) {
		std::cout << calculated[i] % modulo << " = " << rightResults[i] % modulo << std::endl;
		if (calculated[i] % modulo != rightResults[i] % modulo) {
			right = false;
		}
	}

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	if (right) {
		std::cout << "Tests passed successfully";
	} else {
		std::cout << "Tests failed";
	}

	sw.start();

	uint64_t num = 71328803586048ui64;
	uint64_t pow2 = 1;
	for (int i = 0; i <= 27; ++i) {
		if (i != 0) {
			pow2 *= 2;
		}
		uint64_t pow3 = 1;
		for (int j = 0; j <= 12; ++j) {
			if (j != 0) {
				pow3 *= 3;
			}
			uint64_t floor = pow2*pow3;
			uint64_t room = num / floor;
			finalSum += P(floor, room);
			finalSum %= modulo;
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