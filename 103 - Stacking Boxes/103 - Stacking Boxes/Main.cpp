#include "Main.h"
#include <io.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <array>
#include <chrono>
#include "Box.h"

/*
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=39
*/

void printArr(std::vector<Box> arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		std::cout << "Box " << arr[i].num << ": ";
		for (int j = 0; j < arr[i].dimenArr.size(); ++j)
		{
			std::cout << arr[i].dimenArr[j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

std::vector<Box> sortBoxes(std::vector<Box> arr)
{
	/* Because in order for a box b1 to nest in b2, all dimensions n of b1 must be less than a paired dimension of b2
	by sorting the dimensions, we can do a 1 to 1 comparison instead of iterating all permuatations to find a nesting orientation.
	Due to this property, we can also infer that the box b1, will always have n-dimensional volume less than that of b2 in order to nest.
	By sorting the boxes by n-dimensional volume, we can quickly cut down on iteration time later.
	*/
	for (int i = 0; i < arr.size(); ++i)
	{
		arr[i].dimenSort();
		arr[i].updateVol();
	}
	std::sort(arr.begin(), arr.end());
	return arr;
}

bool doesNest(Box b1, Box b2)
{
	for (int i = 0; i < b1.dimenArr.size(); ++i)
	{
		if (b1.dimenArr[i] > b2.dimenArr[i])
			return false;
	}
	return true;
}

void nestBoxes(std::vector<Box> arr)
{
	int maxNestLength = 1;
	std::vector<int> finalNestOrder;
	finalNestOrder.resize(arr.size());
	int i = 0;
	bool stop = false;

	while (i < arr.size() && !stop)
	{	//imagine this as a 2d array and we going along each row, seeing if boxes nest in the next box. This while loop changes the row
		std::vector<int> nestOrder;
		int currentNestLength = 1;
		nestOrder.push_back(arr[i].num);
		for (int j = i; j < arr.size() - 1; ++j)
		{	//this for loop will change the column in our 2d array.
			if (doesNest(arr[j], arr[j + 1]))
			{
				if (nestOrder[currentNestLength - 1] != arr[j].num)
				{	// this is the case for if we had some boxes that didn't nest, then suddenly things started nesting again.
					nestOrder.push_back(arr[j].num);
					currentNestLength++;
				}
				nestOrder.push_back(arr[j+1].num);
				currentNestLength++;
			}
		}
		if (currentNestLength > maxNestLength)
		{
			maxNestLength = currentNestLength;
			finalNestOrder = nestOrder;
		}
		if (maxNestLength > arr.size() - i) // we can stop testing at this point because we know that what's left cannot possibly have a nest length greater.
		{
			stop = true;
		}
		++i;
	}
	// output maxNestLength and nestOrder
	std::cout << maxNestLength << "\n";
	for (int i = 0; i < maxNestLength; ++i)
	{
		std::cout << finalNestOrder[i] << " ";
	}
	std::cout << "\n";
}

void stackBoxes()
{
	std::vector<Box> boxArr;
	int numBoxes = 0;
	int numDims = 0;
	while (std::cin.peek() != 10)
	{
		std::cin >> numBoxes;
		std::cin >> numDims;
		boxArr.resize(numBoxes);
		for (int i = 0; i < numBoxes; ++i)
		{
			boxArr[i].setNum(i, numDims);
			for (int j = 0; j < numDims; ++j)
			{
				std::cin >> boxArr[i].dimenArr[j];
			}
		}

		// I'll leave some extra ouptuts here to show the arrays, but if I need an accurate execution time, remove these.
		std::cout << "\n";
		boxArr = sortBoxes(boxArr);
		//printArr(boxArr);  //
		nestBoxes(boxArr);
		std::cin.ignore();
	}
}

void stackBoxes(std::string file)
{
	std::vector<Box> boxArr;
	int numBoxes = 0;
	int numDims = 0;
	std::fstream myStream(file);
	while (!myStream.eof())
	{
		myStream >> numBoxes;
		myStream >> numDims;
		boxArr.resize(numBoxes);
		for (int i = 0; i < numBoxes; ++i)
		{
			boxArr[i].setNum(i, numDims);
			for (int j = 0; j < numDims; ++j)
			{
				myStream >> boxArr[i].dimenArr[j];
			}
		}

		// I'll leave some extra ouptuts here to show the arrays, but if I need an accurate execution time, remove these.
		std::cout << "\n";
		printArr(boxArr);	//
		boxArr = sortBoxes(boxArr);
		std::cout << "After sorting: \n";
		printArr(boxArr);  //
		nestBoxes(boxArr);
	}
	myStream.close();
}

int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	stackBoxes("input.txt");

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
}