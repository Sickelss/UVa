#pragma once
class Cats
{
public:
	Cats(long, long);
	~Cats();
	long initialHeight;
	long workerCats;
	int N;
	void findN();
	long findNumSlackers();
	long findHeightCatStack();
};

