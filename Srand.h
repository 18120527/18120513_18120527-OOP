#ifndef _SRAND_
#define _SRAND_

#include <cstdlib>

class Srand
{
public:
	static int GetRandom(int maxValueUpper)
	{
		return std::rand() % maxValueUpper;
	}


	static int GetRandom(int minValue, int maxValueUpper)
	{
		return minValue + std::rand() % (maxValueUpper - minValue);
	}
};


#endif
