#include "Main.h"
#include <io.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <time.h>
#include <chrono>

// The problem is found here:
// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

void binPack(long arr[])
{
	long minSum = 99999999;
	std::string order;
	// BGC in arr[], 036 147 258
	int currentSum = arr[3]+arr[6] + arr[2]+arr[8] + arr[1]+arr[4];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "BCG";
	}
	currentSum = arr[3]+arr[6] + arr[1]+arr[7] + arr[2]+arr[5];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "BGC";
	}
	currentSum = arr[5] + arr[8] + arr[0] + arr[6] + arr[1] + arr[4];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "CBG";
	}
	currentSum = arr[5] + arr[8] + arr[1] + arr[7] + arr[0] + arr[3];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "CGB";
	}
	currentSum = arr[4] + arr[7] + arr[0] + arr[6] + arr[2] + arr[5];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "GBC";
	}
	currentSum = arr[4] + arr[7] + arr[2] + arr[8] + arr[0] + arr[3];
	if (currentSum < minSum)
	{
		minSum = currentSum;
		order = "GCB";
	}
	// I hate this, but it works...
	std::cout << order << " " << minSum << "\n";
}

int main()
{
	//clock_t t = clock();	// since Chrono is portable and generally better, I'll switch to that.
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	long bArr[9];
	std::ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			for (int i = 0; i < 9; ++i)
			{
				myfile >> bArr[i];
			}
			binPack(bArr);
		}
	}

	//t = clock() - t;
	//std::cout << "\n" << "run time: " << ((float)t) / CLOCKS_PER_SEC;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
}