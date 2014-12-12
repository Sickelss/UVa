#include "Main.h"
#include <io.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

void binPack(long arr[])
{
	long minSum = 99999999;
	string order;
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
	cout << order << " " << minSum << "\n";
}

int main()
{
	long bArr[9];
	ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			for (int i = 0; i < 9; i++)
			{
				myfile >> bArr[i];
			}
			binPack(bArr);
		}
	}

	cin.ignore();
}