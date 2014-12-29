#include "Cats.h"
#include <math.h>

void Cats::findN()
{
	for (float i = 2; i < sqrt((float)workerCats); ++i)
	{
		float j = log((float)workerCats) / log(i);
		if (j == floor(j))
		{
			N = i;
			break;	//we can just break once we find the first value for N. trust me, don't keep going.
		}
	}
}

long Cats::findNumSlackers()
{
	long currentHeight = initialHeight;
	int count = 0;
	int lazycats = 0;
	while (currentHeight != 1)
	{
		currentHeight /= (N + 1);
		lazycats += pow((float)N, (int)count);
		++count;
	}
	return lazycats;
}

long Cats::findHeightCatStack()
{
	long catStack = 0;
	long currentHeight = initialHeight;
	int count = 0;
	do
	{
		catStack += pow((float)N, count) * currentHeight;
		currentHeight /= (N + 1);
		count++;
	} while (currentHeight >= 1);
	return catStack;
}

Cats::Cats(long height, long cats)
{
	initialHeight = height;
	workerCats = cats;
}


Cats::~Cats()
{
	//
}
