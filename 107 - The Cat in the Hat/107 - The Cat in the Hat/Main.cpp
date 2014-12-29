#include "Main.h"
#include <io.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include "Cats.h"

/*
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=43
*/

std::vector<Cats> readInput(std::string file)
{
	/*
	Input from test file.
	*/
	std::vector<Cats> inputs;
	std::fstream mystream(file);
	long a = 1;
	long b = 1;
	do
	{
		mystream >> a;
		mystream >> b;
		mystream.ignore(); //dump the newline characters or else .peek will return them
		inputs.push_back({ a, b });
	} while (mystream.peek() != 48);	// check for 48, ASCII for 0 
	mystream.close();
	return inputs;
}

std::vector<Cats> readInput()
{
	/*
	Input from stdin.
	*/
	std::vector<Cats> inputs;
	long a = 1;
	long b = 1;
	while (std::cin.peek() != 48)
	{
		std::cin >> a;
		std::cin >> b;
		inputs.push_back({ a, b });
		std::cin.ignore();
	}
	return inputs;
}

void printResults(std::vector<Cats> catArr)
{
	for (int i = 0; i < catArr.size(); ++i)
	{
		catArr[i].findN();
		std::cout << catArr[i].findNumSlackers() << " " << catArr[i].findHeightCatStack() << "\n";
	}
}

int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	/* Remove these comments for a more normalized time test.
	for (int i = 0; i < 100; ++i)
	{
		printResults(readInput());
	}
	*/
	printResults(readInput("input.txt"));

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();

}