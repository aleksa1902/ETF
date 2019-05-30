#ifndef PERFORMANCE_CALCULATOR_H__
#define PERFORMANCE_CALCULATOR_H__
#include "windows.h"
class PerformanceCalculator {
	LARGE_INTEGER startCounter;
	LARGE_INTEGER stopCounter;
	LARGE_INTEGER frequency;
public:
	PerformanceCalculator() {
		startCounter.QuadPart = stopCounter.QuadPart = 0;
		QueryPerformanceFrequency(&frequency);
	}
	void start() {
		QueryPerformanceCounter(&startCounter);
	}
	void stop() {
		QueryPerformanceCounter(&stopCounter);
	}
	double elapsedMillis() const {
		return (stopCounter.QuadPart - startCounter.QuadPart)*1000. / frequency.QuadPart;
	}
};
#endif