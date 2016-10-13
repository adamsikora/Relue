#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <time.h>

class StopWatch
{
public:
	StopWatch() : startClock(0), stopClock(0), lastElapsed(0), totalElapsed(0) {}
	void start() { startClock = clock(); }
	void stop()  { stopClock = clock(); totalElapsed += lastElapsed = (stopClock - startClock) / static_cast<double> (CLOCKS_PER_SEC); }

	std::string getLastElapsed()  { return convertToTime(lastElapsed);  }
	std::string getTotalElapsed() { return convertToTime(totalElapsed); }
	std::string getElapsedFromStart() { return convertToTime((clock() - startClock) / static_cast<double> (CLOCKS_PER_SEC)); }

private:
	clock_t startClock, stopClock;
	double lastElapsed, totalElapsed;

	std::string convertToTime(double t)
	{
		double seconds = t;

		int hours = static_cast<int> (seconds / 3600);
		seconds -= hours * 3600;
		int minutes = static_cast<int> (seconds / 60);
		seconds -= minutes * 60;

		std::stringstream ss;
		ss << std::fixed << std::setfill('0')
			<< std::setw(2) << hours << ":"
			<< std::setw(2) << minutes << ":"
			<< std::setw(5) << std::setprecision(2) << seconds;

		return ss.str();
	}

};