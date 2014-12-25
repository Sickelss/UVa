#include "Main.h"
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

/* Problem Details found at:
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=40
*/

void printArr(std::vector<std::vector<double>> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr.size(); j++)
		{
			std::cout << arr[i][j] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

float profitCalc(std::vector<std::vector<double>> arr, std::vector<int> path)
{
	float profitMar = 1;
	for (int i = 1; i < path.size() -1 ; ++i)
	{
		profitMar = profitMar * arr[path[i]][path[i + 1]];
	}
	return profitMar;
}

std::vector<int> baseConvert(int dec, int size)
{
	std::vector<int> path;
	std::vector<int> rpath;
	int tmp = dec;
	while (tmp!= 0)
	{
		path.push_back(tmp%size);
		tmp = (tmp - tmp%size) / size;
	}
	for (int i = path.size()-1; i >= 0; --i)
	{
		rpath.push_back(path[i]);
	}
	return rpath;
}

void arbitrage(std::vector <std::vector<double>> arr)
{
	std::vector<int> path;
	int currentDecNum = arr.size()*arr.size() + 1;
	float profitMar = 1;	// the final profit margin of the arbitrage sequence
	while (profitMar <= 1.01 && currentDecNum < pow(arr.size(), arr.size()))
	{
		path = baseConvert(currentDecNum, arr.size());
		if (currentDecNum >= 2 * pow(arr.size(), path.size()-1))
		{
			currentDecNum = pow(arr.size(), path.size());
		}
		else
		{
			path.push_back(path[1]);
			profitMar = profitCalc(arr, path);
		}
		++currentDecNum;
	}

	if (profitMar > 1.01)
	{
		std::cout << "Profit: " << profitMar << " \n";
		for (int i = 1; i < path.size(); ++i)
		{
			std::cout << " " << path[i] + 1;
		}
	}
	else
	{
		std::cout << "no arbitrage sequence exists";
	}
	std::cout << "\n\n";
}


int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	std::vector <std::vector <double>> arr;

	std::fstream myfile("input.txt");	// input file
	while (!myfile.eof())
	{
		int size = 0;
		myfile >> size;
		arr.resize(size);
		for (int k = 0; k < size; k++)
		{
			arr[k].resize(size);
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (j == i)
				{
					arr[i][j] = 1;
				}
				else
				{
					myfile >> arr[i][j];
				}
			}
		}
		// outputs
		printArr(arr);		// print out each table of conversions we load, comment for accurate execution time
		arbitrage(arr);		// find the arbitrage paths
	}

	myfile.close();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Exection time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
}