#include "Main.h"
#include <vector>
#include <math.h>
#include <io.h>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>

/*
UVa Problem 108 - Maximum Sum
Problem Specs:
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=44

*/


int sumArray(std::vector<std::vector<int>> arr)
{
	// this function just sums the elements in the array.
	int sum = 0;
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[i].size(); ++j)
		{
			sum += arr[i][j];
		}
	}
	return sum;
}

void maxSum(std::vector<std::vector<int>> arr)
{
	std::vector<std::vector<int>> temp = arr;
	std::vector<int> sumX; // sum of a colum
	std::vector<int> sumY; // sum of a row
	sumX.resize(arr.size());
	sumY.resize(arr.size());
	// first, calculate the sum of each row and column
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[i].size(); ++j)
		{
			sumX[i] += arr[i][j];
			sumY[j] += arr[i][j];
		}
	}
	// second, subtract that sumX and sumY back from the array, here I'll use a temp array since we want to preserve the original values of the array for later.
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[i].size(); ++j)
		{
			temp[i][j] -= sumX[i] + sumY[j];
		}
	}
	// third, take the endsums again like in step1, this time for the temp array.
	for (int i = 0; i < temp.size(); ++i)
	{
		for (int j = 0; j < temp[i].size(); ++j)
		{
			sumX[i] += temp[i][j];
			sumY[j] += temp[i][j];
		}
	}
	// fourth, any endsum that is greater than -1 denotes a row or column to be removed. This must be done from the outside, inward.
	//from the top
	int k = 0;
	while (sumX[k] >= 0)
	{
		arr.erase(arr.begin());
		++k;
	}
	//from the bottom
	k = sumX.size() - 1;
	while (sumX[k] >= 0)
	{
		arr.erase(arr.end() - 1);
		--k;
	}
	//from the left
	k = 0;
	while (sumY[k] >= 0)
	{
		for (int i = 0; i < arr.size(); ++i)
		{
			arr[i].erase(arr[i].begin());
		}
		++k;
	}
	// from the right
	k = sumY.size() - 1;
	while (sumY[k] >= 0)
	{
		for (int i = 0; i < arr.size(); ++i)
		{
			arr[i].erase(arr[i].end() - 1);
		}
		--k;
	}

	std::cout << "\n" << sumArray(arr);
}

void readInput(std::string file)
{
	// Read from input file.
	std::vector<std::vector<int>> arrA;
	int size = 0;
	std::fstream filestream(file);
	while (!filestream.eof())
	{
		filestream >> size;
		arrA.resize(size);
		for (int i = 0; i < size; ++i)
		{
			arrA[i].resize(size);
			for (int j = 0; j < size; ++j)
			{
				filestream >> arrA[i][j];
			}
		}
		// solve completed array
		maxSum(arrA);
		// then loop to next array
	}
	filestream.close();
}

void readInput()
{
	// Read from console inpput.
	std::vector<std::vector<int>> arrA;
	int size = 0;
	while (std::cin.peek() != 10)
	{
		std::cin >> size;
		arrA.resize(size);
		for (int i = 0; i < size; ++i)
		{
			arrA[i].resize(size);
			for (int j = 0; j < size; ++j)
			{
				std::cin >> arrA[i][j];
			}
		}
		maxSum(arrA);
		//std::cin.ignore();
	}
}

int main()
{
	// file input
	
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<int>> arr;
	
	for (int i = 0; i < 100; ++i)
	{
		readInput("inputs.txt");
		std::cout << "\n";
	}

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
	
	 /*// console-in

	readInput();
	std::cin.ignore();

	*/
}