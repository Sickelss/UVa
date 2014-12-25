#include "Main.h"
#include <io.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

/*
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=41
*/

void printSkyline(std::vector<int> skyline)
{
	int currHeight = 0; // the height of a filthy degenerate.
	int heightChange = 0;
	for (int i = 0; i < skyline.size(); ++i)
	{
		if (skyline[i] != currHeight)
		{
			currHeight = skyline[i];
			std::cout << i + 1 << " " << skyline[i] << " ";
		}
	}
	std::cout << "\n";
}

std::vector<int> updateSkyline(std::vector<int> skyline, int l, int h, int r)
{
	if (skyline.size() < r)
	{
		skyline.resize(r+1);
	}
	for (int i = l-1; i < r-1; ++i)
	{
		if (h > skyline[i])
		{
			skyline[i] = h;
		}
	}
	return skyline;
}

void findSkyline()
{
	std::vector<int> skyline;
	int left = 0;
	int height = 0;
	int right = 0;
	std::fstream myfile("input.txt");

	while (!myfile.eof())
	{
		myfile >> left;
		myfile >> height;
		myfile >> right;
		skyline = updateSkyline(skyline, left, height, right);
	}
	printSkyline(skyline);
}

int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	findSkyline();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
}