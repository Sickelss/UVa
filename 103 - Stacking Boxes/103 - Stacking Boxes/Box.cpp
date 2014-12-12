#include "Box.h"

void Box::setNum(int boxNum, int boxDims)
{
	num = boxNum;
	dimenArr.resize(boxDims);
}

void Box::dimenSort()
{
	std::sort(dimenArr.begin(), dimenArr.end());
}

void Box::updateVol()
{
	boxVol = 1;
	for (int i = 0; i < dimenArr.size(); i++)
	{
		boxVol *= dimenArr[i];
	}
}

bool operator < (const Box &b1, const Box &b2)
{
	if (b1.boxVol < b2.boxVol)
		return true;
	else
		return false;
}

Box::Box()
{

}

Box::~Box()
{

}