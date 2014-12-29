#include "Triple.h"
#include <vector>
#include <math.h>

void Triple::setTriple(int a, int b, int c)
{
	aVal = a;
	bVal = b;
	cVal = c;
}

bool Triple::isCoprime()
{
	int temp;
	std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 27, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
	bool coprime = true;
	temp = fmin(aVal, fmin(bVal, cVal));
	for (int i = 0; i < primes.size(); ++i)
	{
		int count = 0;
		if (temp > primes[i])
		{
			if (aVal % primes[i] == 0)
			{
				++count;
			}
			if (bVal % primes[i] == 0)
			{
				++count;
			}
			if (cVal % primes[i] == 0)
			{
				++count;
			}
			if (count >= 2)
			{
				return false;
			}
		}
		else
		{
			coprime = true;
			return true;
		}
	}
}

Triple::Triple()
{
}


Triple::~Triple()
{
}
