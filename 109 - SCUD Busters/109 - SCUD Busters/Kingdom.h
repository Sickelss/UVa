#pragma once
#include <vector>

class Kingdom
{
public:
	std::vector<std::pair<int,int>> sites;	// Coordinate pairs of buildings in the kingdom
	float area;		// total area in the kingdom

	void Kingdom::getArea();	// sets public area val
	bool Kingdom::isHit(std::vector<std::pair<int, int>>);	// returns true if any input coordinate is within kingdom borders

	Kingdom();
	~Kingdom();

private:
	std::vector<std::pair<int, int>> coords; // Sorted vector of coordinate pair sites.
};

