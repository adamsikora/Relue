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

uint64_t treshold = 5000;

uint64_t last = 290797;
int64_t count = 0;

uint64_t generateNext()
{
	++count;
	last = (last*last) % 50515093;
	return last % 500;
}

class Segment {
public:
	Segment(uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy)
		: startx(startx), starty(starty), endx(endx), endy(endy), isVertical(startx == endx)
	{
		assert(startx != endx || starty != endy);
		if (startx == endx) {
			yinter = 0;
			slope = 0;
		}
		else {
			slope = boost::rational<int64_t>(endy - starty, endx - startx);
			assert(abs(slope.numerator()) < billion);
			assert(abs(slope.denominator()) < billion);
			yinter = starty - startx * slope;
			assert(abs(yinter.numerator()) < billion);
			assert(abs(yinter.denominator()) < billion);
		}
	}

	uint64_t startx, starty, endx, endy;
	bool isVertical;
	boost::rational<int64_t> yinter, slope;
	bool zeroSlope() const { return (starty == endy); }
};

std::set<std::pair<boost::rational<int64_t>, boost::rational<int64_t>>> intersects;

bool isSequence(uint64_t start, boost::rational<int64_t> mid, uint64_t end)
{
	return (start > mid && mid > end) || (start < mid && mid < end);
}

void hasCommonIntersection(const Segment& first, const Segment& second)
{
	if ((first.isVertical && second.isVertical) || (first.slope == second.slope)) {
		;
	}
	else {
		boost::rational<int64_t> midx = first.isVertical ? first.startx : (second.isVertical ? second.startx : (second.yinter - first.yinter) / (first.slope - second.slope));
		boost::rational<int64_t> midy = first.isVertical ? second.slope * midx + second.yinter : first.slope * midx + first.yinter;
		if (first.zeroSlope()) { assert(midy == first.starty); }
		if (second.zeroSlope()) { assert(midy == second.starty); }
		if (first.isVertical) { assert(midx == first.startx); }
		if (second.isVertical) { assert(midx == second.startx); }
		//assert(first.slope * midx + first.yinter == second.slope * midx + second.yinter);
		if ((isSequence(first.startx, midx, first.endx) || first.isVertical) && (isSequence(first.starty, midy, first.endy) || first.zeroSlope()) &&
			(isSequence(second.startx, midx, second.endx) || second.isVertical) && (isSequence(second.starty, midy, second.endy) || second.zeroSlope()))
		{
			assert(midx > 0 && midx < 499 && midy > 0 && midy < 499);
			intersects.insert(std::pair<boost::rational<int64_t>, boost::rational<int64_t>>(midx, midy));
		}
	}
}

StopWatch sw;

int main()
{
	sw.start();

	std::vector<Segment> segments;

	//segments.emplace_back(0, 0, 12, 12);
	//segments.emplace_back(12, 0, 12, 12);

	for (int i = 0; i < treshold; ++i) {
		segments.emplace_back(generateNext(), generateNext(), generateNext(), generateNext());
	}
	std::cout << count << std::endl;

	for (int i = 0; i < segments.size(); ++i) {
		if (segments[i].zeroSlope() && segments[i].isVertical) { std::cout << segments[i].slope << std::endl; }
		for (int j = i + 1; j < segments.size(); ++j) {
			hasCommonIntersection(segments[j], segments[i]);
		}
	}

	finalSum = intersects.size();

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