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

long long k = 1;

boost::circular_buffer<long long> old;

long long generate()
{
	long long toret = 0;
	if (k <= 55) {
		toret = (100003i64 - 200003i64 * k + 300007i64 * k*k*k) % million;
	}
	else {
		toret = (*(old.end() - 55) + *(old.end() - 24)) % million;
	}
	++k;
	old.push_back(toret);
	return toret;
}

StopWatch sw;

int main()
{	
	sw.start();

	old.resize(100);

	std::vector<long long> positions(million, -1);
	std::vector<std::list<long long>> lists(million / 2, std::list<long long>() );

	long long free = 0;

	long long misdialed = 0;

	while (true) {
		long long first = generate();
		long long second = generate();
		if (first != second) {
			++finalSum;

			if (positions[first] == positions[second]) {
				if (positions[first] == -1) {
					lists[free].push_back(first);
					lists[free].push_back(second);
					positions[first] = positions[second] = free;
					while (lists[++free].size() != 0);
				}
			}
			else {
				if (positions[first] == -1) {
					lists[positions[second]].push_back(first);
					positions[first] = positions[second];
				}
				else if (positions[second] == -1) {
					lists[positions[first]].push_back(second);
					positions[second] = positions[first];
				}
				else {
					if (positions[first] < positions[second]) {
						if (positions[second] < free) {
							free = positions[second];
						}
						const long long oldPosition = positions[second];
						for (auto &it : lists[oldPosition]) {
							positions[it] = positions[first];
						}
						lists[positions[first]].splice(lists[positions[first]].end(), lists[oldPosition]);
					}
					else {
						if (positions[first] < free) {
							free = positions[first];
						}
						const long long oldPosition = positions[first];
						for (auto &it : lists[oldPosition]) {
							positions[it] = positions[second];
						}
						lists[positions[second]].splice(lists[positions[second]].end(), lists[oldPosition]);
					}
				}
			}

			if (positions[524287] != -1 && lists[positions[524287]].size() >= 990 * thousand) {
				goto end;
			}
		}
		else { ++misdialed; }
	}

end:;
	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << finalSum;
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}