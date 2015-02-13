#include "Kingdom.h"
#include <iostream>
#include <algorithm>

bool slopeCompare(const std::pair<int, int>& a, const std::pair<int, int>& b)
{	// this will compare the slopes of these points from the origin. Used on the far side.
	float angleA = float(a.second) / a.first;
	float angleB = float(b.second) / b.first;

	return angleA > angleB;
}

bool slopeCompare2(const std::pair<int, int>& a, const std::pair<int, int>& b)
{	// this will compare the slopes of these points from the origin. Used on the near side.
	float angleA = float(a.second) / a.first;
	float angleB = float(b.second) / b.first;

	return angleA < angleB;
}

void Kingdom::getArea()
{
	area = 0;
	float slope = 0;
	float length = 0;
	std::vector<std::pair<int,int>> near;
	std::vector<std::pair<int,int>> far;

	// first, find the point of greatest angle to the x-axis, we'll start there.
	for (int i = 0; i < sites.size(); ++i)
	{
		if (float(sites[i].second) / sites[i].first > slope)
		{
			slope = float(sites[i].second) / sites[i].first;
			length = sqrt(sites[i].first * sites[i].first + sites[i].second * sites[i].second);
		}
	}

	// divide the remaining parts into two sub-arrays, length < and length >. 
	for (int i = 0; i < sites.size(); ++i)
	{
		if (length <= sqrt(sites[i].first * sites[i].first + sites[i].second * sites[i].second))
		{
			far.push_back(sites[i]);
		}
		if (length > sqrt(sites[i].first * sites[i].first + sites[i].second * sites[i].second))
		{
			near.push_back(sites[i]);
		}
	}

	//next, sort those arrays... we'll just make a custom comparator to use.
	sort(far.begin(), far.end(), slopeCompare);
	sort(near.begin(), near.end(), slopeCompare2);

	//then put those sorted arrays into our coords array.
	for (int i = 0; i < far.size(); ++i)
	{
		coords.push_back(far[i]);
	}
	for (int i = 0; i < near.size(); ++i)
	{
		coords.push_back(near[i]);
	}

	// then, eliminate unnecessary interior points.
	int count = 0;
	while ((coords.size() - 1) >= count + 2)
	{
		bool above = false;
		bool below = false;
		slope = (coords[count].second - coords[count + 1].second) / (coords[count].first - coords[count + 1].first + 0.0001);
		float intercerpt = -1 * slope * coords[count].first + coords[count].second;
		for (int i = count + 2; i < coords.size(); ++i)
		{
			if (coords[i].second > slope * coords[i].first + intercerpt)
			{
				above = true;
			}
			if (coords[i].second < slope * coords[i].first + intercerpt)
			{
				below = true;
			}
		}
		if (above && below)
		{
			coords.erase(coords.begin() + count + 1);
		}
		else
		{
			++count;
		}
	}

	// lastly, using the shoelace formula, sum the area. Since the coords array has been sorted, it will go around the polygon properly.
	for (int i = 0; i < coords.size() - 1; ++i)
	{
		area += (coords[i].first * coords[i + 1].second) - (coords[i + 1].first * coords[i].second);
	}

	area += (coords[coords.size() - 1].first * coords[0].second) - (coords[0].first * coords[coords.size() - 1].second);
	area /= 2;
	area = abs(area);
}

bool Kingdom::isHit(std::vector<std::pair<int, int>> strike)
{
	float perim = 0;
	float dist = 0;

	for (int i = 0; i < coords.size() - 1; ++i)
	{	//sum the perimeter of the kingdom
		perim += sqrt(pow(coords[i].first - coords[i+1].first, 2) + pow(coords[i].second - coords[i+1].second,2));
	}
	perim += sqrt(pow(coords[0].first - coords[coords.size() - 1].first, 2) + pow(coords[0].second - coords[coords.size() - 1].second, 2));

	for (int j = 0; j < strike.size(); ++j)
	{	//sum the distance from the missile strike to the perimeter points.
		dist = 0;
		for (int i = 0; i < coords.size(); ++i)
		{
			dist += sqrt(pow(coords[i].first - strike[j].first, 2) + pow(coords[i].second - strike[j].second, 2));
		}
		if (dist <= perim)
		{
			return true;
		}
	}

	return false;
}

Kingdom::Kingdom()
{
}


Kingdom::~Kingdom()
{
}
