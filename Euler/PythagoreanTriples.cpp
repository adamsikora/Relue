#include "PythagoreanTriples.h"

#include <array>

void countEmUpToC(int64_t a, int64_t b, int64_t c, int64_t max, int64_t& result)
{
	if (c <= max) {
		++result;
		for (auto &it : pythagoreanTripleGeneratingMatrices) {
			countEmUpToC(
				it[0][0] * a + it[0][1] * b + it[0][2] * c,
				it[1][0] * a + it[1][1] * b + it[1][2] * c,
				it[2][0] * a + it[2][1] * b + it[2][2] * c,
				max, result
			);
		}
	}
}

int64_t countPrimitiveTriplesUpToC(int64_t max)
{
	int64_t result = 0;
	countEmUpToC(3, 4, 5, max, result);
	return result;
}

void countEmUpToSum(int64_t a, int64_t b, int64_t c, int64_t max, int64_t& result)
{
	if (a+b+c <= max) {
		++result;
		for (auto &it : pythagoreanTripleGeneratingMatrices) {
			countEmUpToSum(
				it[0][0] * a + it[0][1] * b + it[0][2] * c,
				it[1][0] * a + it[1][1] * b + it[1][2] * c,
				it[2][0] * a + it[2][1] * b + it[2][2] * c,
				max, result
			);
		}
	}
}

int64_t countPrimitiveTriplesUpToSum(int64_t max)
{
	int64_t result = 0;
	countEmUpToC(3, 4, 5, max, result);
	return result;
}