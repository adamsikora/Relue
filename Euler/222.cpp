#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <memory>
#include <assert.h>

#include <set>
#include <map>
#include <vector>
#include <list>

#include <math.h>

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

long long finalSum = trillion;

long long nBalls = 21;

double minRadius = 30.0;
double maxRadius = 50.0;

//void getMin(std::vector<double> balls, long long left, double height, std::vector<double> order) {
//	if (left == 0) {
//		if (height*1000 < finalSum) {
//			for (auto &it : order) {
//				std::cout << it << ", ";
//			}
//			std::cout << height << std::endl;
//			finalSum = height*1000;
//			//std::cin.ignore();
//			//return height;
//		}
//	}
//	else {
//		for (auto &it : balls) {
//			double newHeight;
//			if (left == nBalls) {
//				newHeight = it;
//			}
//			else {
//				double joined = it + order.back();
//				double step = sqrt(joined*joined - (2 * maxRadius - joined)*(2 * maxRadius - joined));
//				if (left == 1) {
//					newHeight = height + it + step;
//				}
//				else {
//					newHeight = height + step;
//				}
//			}
//			std::vector<double> newBalls;
//			for (auto &sit : balls) {
//				if (sit != it) {
//					newBalls.push_back(sit);
//				}
//			}
//			std::vector<double> newOrder = order;
//			newOrder.push_back(it);
//
//			getMin(newBalls, left - 1, newHeight, newOrder);
//		}
//	}
//
//}

StopWatch sw;

int main()
{	
	sw.start();

	std::vector<double> subBalls;
	for (double i = minRadius; i <= maxRadius; i += (maxRadius - minRadius) / (nBalls - 1)) {
		subBalls.push_back(i);
	}

	std::vector<double> balls;
	for (auto it = ++(subBalls.rbegin()); it != subBalls.rend(); ++it, ++it) {
		std::cout << *it << ", ";
		balls.push_back(*it);
	}
	for (auto it = subBalls.begin(); it != ++(subBalls.end()); ++it, ++it) {
		std::cout << *it << ", ";
		balls.push_back(*it);
	}
	std::cout << std::endl;

	double height = balls.front() + balls.back();
	for (auto fit = balls.begin(), sit = ++(balls.begin()); sit != balls.end(); ++fit, ++sit) {
		double joined = *fit + *sit;
		height += sqrt(joined*joined - (2 * maxRadius - joined)*(2 * maxRadius - joined));
	}

	finalSum = long long(height * 1000);
	//getMin(balls, nBalls, 0.0, std::vector<double>());

	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	std::stringstream answer;
	answer << long long(finalSum);
	std::cout << "Answer is: " << answer.str() << std::endl;
	ClipboardIt(answer.str());
	std::cin.ignore();
	return EXIT_SUCCESS;
}