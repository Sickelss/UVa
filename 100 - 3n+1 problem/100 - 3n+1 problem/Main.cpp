#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36
void cycleCount(int i, int j)
{
	int n = 0;		//current number in sequence
	int currentCycleLength = 0;		//current cycle length
	int maxCycleLength = 1;		//initialized at 1 since the loop is set up to not count the initial number as a process.

	for (int a = i; a<=j; ++a)
	{
		n=a;
		//cout << n << "\n";
		while (n != 1)
		{
			((n%2==0) ? n=n/2 : n=3*n+1);
			//cout << n << "\n";
			++currentCycleLength;
		}
		if (maxCycleLength < currentCycleLength) {maxCycleLength = currentCycleLength;}
		currentCycleLength = 1;		//reset our current cycle count, remember it's initial val is 1.
	}
	std::cout << i << " " << j << " " << maxCycleLength << '\n';
}

void main()
{
	clock_t t = clock();	//for timing the execution time.
	int i = 0;	//input integers
	int j = 1;	//input integer, must be > i
	std::string a;	// read from file input i as string
	std::string b;	// read from file input j as string

	std::ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())	//This is bad, but I'm sleepy. Hopefully I'll return to write a better filereader.
		{
			myfile >> a;
			myfile >> b;
			i = atoi(a.c_str());	//convert string to int
			j = atoi(b.c_str());
			cycleCount(i,j);
		}
	}
	
	myfile.close();		// if you don't close files, bad stuff happens.
	t = clock() - t;
	std::cout << "\n" << "run time: " << ((float)t) / CLOCKS_PER_SEC;
	std::cin.ignore();	//lazy way to "hit any key to exit"
}