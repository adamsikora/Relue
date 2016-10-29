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

int64_t finalSum = 0;

const int64_t modulo = 982451653i64;
const int64_t threshold = 100 * trillion;

StopWatch sw;

enum PointType {
	invalid, up, left, right, mid, down, under
};

struct Point {
	PointType type;
	int64_t row, column;
};

struct pointHash {
public:
	std::size_t operator()(const Point &x) const
	{
		return std::hash<int64_t>()(int64_t(x.type)) ^ std::hash<int64_t>()(x.row) ^ std::hash<int64_t>()(x.column);
	}
};

struct pointEq {
public:
	std::size_t operator()(const Point &f, const Point &s) const
	{
		return f.type == s.type && f.row == s.row && f.column == s.column;
	}
};

const Point invalidPoint{ PointType::invalid, 0, 0 };

typedef std::array<Point, 6> Descendants;

int64_t find(int64_t size)
{
	int64_t result = 0;

	std::unordered_map<Point, Descendants, pointHash, pointEq> allPoints;

	for (int64_t row = 0; row < size; ++row) {
		for (int64_t column = 0; column <= row; ++column) {
			Point  up{ PointType::up, row, column };
			Point  left{ PointType::left, row, column };
			Point  right{ PointType::right, row, column };
			Point  mid{ PointType::mid, row, column };
			Point  down{ PointType::down, row, column };
			Point  under = (row + 1) < size ? Point{ PointType::under, row, column } : invalidPoint;

			Point  downLeft{ PointType::up, row + 1, column };
			Point  downRight{ PointType::up, row + 1, column + 1 };
			Point  underLeft = (row + 1) < size ? Point{ PointType::right, row + 1, column } : invalidPoint;
			Point  underRight = (row + 1) < size ? Point{ PointType::left, row + 1, column + 1 } : invalidPoint;
			Point  underMid = (row + 1) < size ? Point{ PointType::up, row + 2, column + 1 } : invalidPoint;

			Descendants desc{};
			if (allPoints.count(up) > 0) {
				std::cout << "bad\n";
			}
			if (column > 0) {
				desc[0] = Point{ PointType::down, row - 1, column - 1 };
				desc[1] = Point{ PointType::under, row - 1, column - 1 };
			}
			if (column < row) {
				//desc[6] = Point{ PointType::down, row - 1, column };
				desc[5] = Point{ PointType::under, row - 1, column };
			}
			desc[2] = left;
			desc[3] = mid;
			desc[4] = right;

			allPoints[up] = desc;


			desc = Descendants{};
			if (allPoints.count(left) > 0) {
				std::cout << "bad\n";
			}
			desc[2] = downLeft;
			desc[5] = mid;

			allPoints[left] = desc;


			desc = Descendants{};
			if (allPoints.count(mid) > 0) {
				std::cout << "bad\n";
			}
			desc[1] = downLeft;
			desc[3] = down;
			desc[5] = downRight;

			allPoints[mid] = desc;


			desc = Descendants{};
			if (allPoints.count(right) > 0) {
				std::cout << "bad\n";
			}
			desc[1] = mid;
			desc[4] = downRight;

			allPoints[right] = desc;


			desc = Descendants{};
			if (allPoints.count(down) > 0) {
				std::cout << "bad\n";
			}
			desc[0] = downLeft;
			desc[3] = under;
			//desc[6] = downRight;

			allPoints[down] = desc;


			if (!pointEq()(invalidPoint, under)) {
				desc = Descendants{};
				if (allPoints.count(under) > 0) {
					std::cout << "bad\n";
				}
				desc[1] = underLeft;
				desc[3] = underMid;
				desc[5] = underRight;

				allPoints[under] = desc;
			}

		}
	}

	for (int64_t column = 0; column <= size; ++column) {
		Point curr{ PointType::up, size, column };
		if (allPoints.count(curr) > 0) {
			std::cout << "badlast\n";
		}
		Descendants desc{};
		if (column > 0) {
			desc[0] = Point{ PointType::down, size - 1, column - 1 };
		}
		allPoints[curr] = desc;
	}

	for (const auto &it : allPoints) {
		for (int64_t i = 0; i < 6; ++i) {
			if (it.second[i].type != PointType::invalid) {
				if (allPoints.count(it.second[i]) <= 0) {
					std::cout << "bad links\n";
				}
			}
		}
	}
	for (const auto &it : allPoints) {
		for (int64_t i = 0; i < 5; ++i) {
			if (it.second[i].type == PointType::invalid) {
				continue;
			}
			for (int64_t j = i + 1; j < 6; ++j) {
				if (it.second[j].type == PointType::invalid) {
					continue;
				}
				std::unordered_set<Point, pointHash, pointEq> is, js;
				Point next = it.second[i];
				while (next.type != PointType::invalid) {
					is.insert(next);
					next = allPoints[next][i];
				}
				next = it.second[j];
				while (next.type != PointType::invalid) {
					js.insert(next);
					next = allPoints[next][j];
				}

				int64_t interResult = 0, iResult = 0, jResult = 0;

				for (const auto& inIs : is) {
					for (int64_t k = i + 1; k < 6; ++k) {
						Point next = allPoints[inIs][k];
						while (next.type != PointType::invalid) {
							if (js.count(next) > 0) {
								++iResult;
								break;
							}
							next = allPoints[next][k];
						}
					}
				}

				for (const auto& inJs : js) {
					for (int64_t k = 0; k < j; ++k) {
						Point next = allPoints[inJs][k];
						while (next.type != PointType::invalid) {
							if (is.count(next) > 0) {
								++jResult;
								break;
							}
							next = allPoints[next][k];
						}
					}
				}

				interResult = iResult + jResult;
				result += interResult;
			}
		}
	}

	return result;
}

int main()
{
	sw.start();

	//initializePrimes(threshold);
	//std::cout << "primes initialized" << std::endl;

	//for (int i = 4; i < 10; ++i) {
	//	std::cout << find(i) << std::endl;
	//}

	finalSum = find(36);

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer.precision(8);
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