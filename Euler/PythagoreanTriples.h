#pragma once
/*
Adam Sikora
12.10.2016

*/

#include <algorithm>
#include <vector>

const std::vector<std::vector<std::vector<int64_t>>> pythagoreanTripleGeneratingMatrices =
{
	{
		{ 1, -2, 2 },
		{ 2, -1, 2 },
		{ 2, -2, 3 },
	},
	{
		{ 1, 2, 2 },
		{ 2, 1, 2 },
		{ 2, 2, 3 },
	},
	{
		{ -1, 2, 2 },
		{ -2, 1, 2 },
		{ -2, 2, 3 },
	}
};

int64_t countPrimitiveTriplesUpToC(int64_t max); // inclusive
int64_t countPrimitiveTriplesUpToSum(int64_t max); // inclusive