#pragma once
#include <vector>
#include <algorithm>

class Box
{
public:
	Box();
	~Box();
	void setNum(int, int);
	void dimenSort();
	void updateVol();
	int num;
	std::vector<int> dimenArr;
	long boxVol;
	
};

bool operator < (const Box &b1, const Box &b2);	//overloaded operator for comparing boxes, it will compare them by volume.