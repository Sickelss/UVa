#include "Main.h"
#include <io.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include "Triple.h"

/*Problem description found below:
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=42
*/

std::vector<long> readInput(std::string file)
{
	/*
	Read Input from file. Great for debugging
	*/
	std::vector<long> nArr;
	std::fstream myfile(file);
	while (!myfile.eof())
	{
		long n = 0;
		myfile >> n;
		nArr.push_back(n);
	}
	myfile.close();
	return nArr;
}

std::vector<long> readInput()
{
	/*
	Read input from stdin.
	*/
	std::vector<long> nArr;
	while (std::cin.peek() != 10)	// check for lone newline character.
	{
		long n = 0;
		std::cin >> n;
		nArr.push_back(n);
		std::cin.ignore();
	}
	return nArr;
}

void findOutputs(std::vector<Triple> triples, int n)
{
	int outA = 0;
	int outB = 0;
	std::vector<bool> notComponents;
	notComponents.resize(n);
	for (int i = 0; i < triples.size(); ++i)
	{
		if (triples[i].isCoprime())
		{
			++outA;
		}
	}
	for (int i = 0; i < triples.size(); ++i)
	{
		notComponents[triples[i].aVal -1] = true;
		notComponents[triples[i].bVal -1] = true;
		notComponents[triples[i].cVal -1] = true;
	}
	for (int i = 0; i < notComponents.size(); ++i)
	{
		if (!notComponents[i])
		{
			++outB;
		}
	}
	std::cout << outA << " " << outB << "\n";
}

void findTriples(std::vector<long> nArr)
{
	std::vector<Triple> triples;
	for (int n = 0; n < nArr.size(); ++n)
	{
		triples.clear();
		for (int c = nArr[n]; c > 0; --c)
		{
			for (int b = c - 1; b > c/2; --b)
			{
				double a = sqrt(c*c - b*b);
				if (a == floor(a) && a < b)
				{
					triples.resize(triples.size()+1);
					triples[triples.size()-1].setTriple(a, b, c);
				}
			}
		}
		findOutputs(triples, nArr[n]);
	}
}

int main()
{
	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	findTriples(readInput("input.txt"));

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Execution time (microseconds): " << duration.count() << "\n";
	std::cin.ignore();
}
