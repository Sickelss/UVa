#include "Main.h"
#include <fstream>
#include <io.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "Kingdom.h"

/*
Problem 109 - SCUD Busters
Problem details:
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=45
*/

// I usually don't use global variables for reasons, but today I will. These problems are usually simple enough that it's not an issue anyway.
std::vector<Kingdom> kingdoms;
std::vector<std::pair<int, int>> strikes;


void readInputs(std::string file)
{
	int numSites = 0;
	int a = 0;
	int b = 0;
	std::fstream inFile(file);
	while (!inFile.eof())
	{
		while (inFile.peek() != 45)
		{	// -1 denotes the end of kingdom sites and the beginning of missile strike locations. 45 is "-"
			kingdoms.resize(kingdoms.size() + 1);	//add a kingdom
			inFile >> numSites;		// get the number of sites
			kingdoms[kingdoms.size() - 1].sites.resize(numSites);	// resize that kingdom class' sites vector
			for (int i = 0; i < numSites; ++i)
			{	// since I'm using std::pairs for the coordinates, I'll have to read them two at a time and make_pair
				inFile >> a;
				inFile >> b;
				kingdoms[kingdoms.size() - 1].sites[i] = std::make_pair(a,b);
			}
			inFile.ignore();
		}
		// after we're done with the kingdoms, throw out the -1 and read in the missile strike locations.
		inFile.ignore();
		inFile.ignore();
		while (!inFile.eof())
		{	// so it doesn't jump back to reading to kingdoms
			strikes.resize(strikes.size() + 1);
			inFile >> a;
			inFile >> b;
			strikes[strikes.size() - 1] = std::make_pair(a, b);
		}
	}
	inFile.close();
}

void findOutages()
{
	float area = 0;

	readInputs("inputs.txt");

	for (int i = 0; i < kingdoms.size(); ++i)
	{
		kingdoms[i].getArea();
	}
	for (int i = 0; i < kingdoms.size(); ++i)
	{
		if (kingdoms[i].isHit(strikes))
		{
			area += kingdoms[i].area;
		}
	}

	printf("%.2f", area);
}

int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	findOutages();

	std::cout << "\n";
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();

}