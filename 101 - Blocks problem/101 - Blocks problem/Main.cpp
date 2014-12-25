#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37
// I've fixed this solution, no more scouring across the array each time stack is called.
// Maybe next time don't put it all in one big file, these problems are getting too big for that.

class Block
{
public:
	int id;		// block ID as int
	int blockAbove;		//stores the id of the block above, -1 if none
	int blockBelow;		//stores the id of the block below, -1 if none
	bool originalPos;	//original position flag for printing
};

std::vector<Block> unstack(std::vector<Block> bArr,int pos)	
{
	int test;
	test = bArr[pos].blockBelow;
	if (test != -1)
	{
		bArr[test].blockAbove = -1;
	}
	bArr[pos].originalPos = true;
	return bArr;
}

std::vector<Block> stackA(std::vector<Block> bArr, int start, int end)
{
	int test;
	if (bArr[start].originalPos == false)	// this will unhook the block below the starting block
	{
		test = bArr[start].blockBelow;
		if (test >= 0 && test <= bArr.size())
		{
			bArr[test].blockAbove = -1;
		}
		bArr[test].blockAbove = -1;
	}
	while (bArr[end].blockAbove != -1)		//this looks for the block stacked on top of the end block given
	{
		end = bArr[end].blockAbove;
	}
	bArr[end].blockAbove = bArr[start].id;
	bArr[start].blockBelow = bArr[end].id;
	bArr[start].originalPos = false;
	return bArr;
}

// returns true in the event: the start and end blocks are in the same pile already.
bool checkStack(std::vector<Block> bArr, int start, int end)
{
	int check = start;
	while (bArr[check].blockAbove != -1)
	{
		if (bArr[check].blockAbove == bArr[end].id)
		{
			return true;
		}
		else
		{
			check = bArr[check].blockAbove;
		}
	}
	return false;
}

std::vector<Block> blockMove(std::vector<Block> bArr, std::string com, int start, int end)
{
	bool check = checkStack(bArr, start, end);		//first we check the for invalid moves
	if (check)
	{
		com = "";		//overwrite the command if the move is invalid
	}

	if (com == "moveonto")		// since we're using strings, we can't use the switch statements in C++, instead I'll go with if... tedious yea
	{
		bArr = unstack(bArr, start);
		bArr = unstack(bArr, end);
		bArr = stackA(bArr, start, end);
	}
	else if (com == "moveover")
	{
		bArr = unstack(bArr, start);
		bArr = stackA(bArr, start, end);
	}
	else if (com == "pileonto")
	{
		bArr = unstack(bArr, end);
		bArr = stackA(bArr, start, end);
	}
	else if (com == "pileover")
	{
		bArr = stackA(bArr, start, end);
	}
	return bArr;
}

void print2(std::vector<Block> bArr, int i)
{
	if (bArr[i].blockAbove != -1)
	{
		std::cout << " " << bArr[i].blockAbove;
		print2(bArr, bArr[i].blockAbove);
	}
}

void printBlocks(std::vector<Block> bArr)
{
	for (int i=0; i<bArr.size(); ++i)
	{
		std::cout << i << ":";
		if (bArr[i].originalPos == true)
		{
			std::cout << " " << bArr[i].id;
			print2(bArr, i);
		}
		std::cout << "\n";
	}
}


int main()
{
	clock_t t = clock();
	int size = 1;
	std::string commandA;
	std::string commandB;
	std::string commandC;
	std::string commandD;
	int blockToMove = 0;
	int positionToMove = 0;
	std::vector<Block> bArr;	//like an array, but re-sizable

	std::ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		bool quit = false;
		myfile >> size;
		bArr.resize(size);	//this resizes the vector so now we can hold the correct number of stacks.
		for (int i=0; i<size; i++)	// populate stacks with block numbers.
		{
			bArr[i].id = i;
			bArr[i].blockAbove = -1;
			bArr[i].blockBelow = -1;
			bArr[i].originalPos = true;
		}

		//printBlocks(bArr);

		while (!myfile.eof() && !quit)	//read instructions
		{
			myfile >> commandA;
			if (commandA != "quit")
			{
				myfile >> commandB;
				myfile >> commandC;
				myfile >> commandD;
				commandA += commandC;
				blockToMove = atoi(commandB.c_str());
				positionToMove = atoi(commandD.c_str());
				//cout << commandA << " " << blockToMove << " " << positionToMove << '\n';		// this will print each step's command sequence
				bArr = blockMove(bArr, commandA, blockToMove, positionToMove);
				//printBlocks(bArr);		//this prints each step's output
			}
			else {quit = true;}
		}
	}
	myfile.close();
	
	printBlocks(bArr);
	t = clock() - t;
	std::cout << "\n" << "run time: " << ((float)t) / CLOCKS_PER_SEC;
	std::cin.ignore();
}
