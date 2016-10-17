#pragma once

#include <algorithm>
#include <vector>

namespace mpc {

	void initialize(int64_t max, int64_t modulo);

	int64_t naiveModuloCombination(int64_t n, int64_t k, int64_t modulo);
	int64_t moduloCombination(int64_t n, int64_t k);
	int64_t moduloPermutation(std::vector<int64_t> ns);
	int64_t moduloFactorial(int64_t n);

}