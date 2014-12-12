// Monty Hall Problem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int correct_door; //the correct door
	int guess1;  //the door guessed by our contestant initially
	int guess2;	//the door guessed after eliminating one of the doors
	const int doors_fir[3] = {1, 2, 3};	//I'm actually going to simulate these doors as array indexes.
	int doors_sec[2] = {};	// this will be for our second pick when we elimante an incorrect door.
	int tot_correct_kept = 0;	// to tally up the correct guesses for not switching
	int tot_correct_switched = 0;	// tally for switching the choice.
	int switched = 0;	//number of times the contestant switched guess
	int kept = 0;	//number of times the contestant kept their initial door
	int tot_guess = 100;	//this will be the number of times we run this sim.

	cout << "Run how many times? ";
	cin >> tot_guess;
	cin.ignore(); // simple fix for the newline character left in the input stream of the previous cin

	for (int i=0; i < tot_guess; i++)
	{
		cout << "Win -- Guess" << endl;
		// pick the first door;
		correct_door = rand() % 3;
		guess1 = rand() % 3;
		cout << doors_fir[correct_door] << "   " << doors_fir[guess1] << endl;
		int temp = 1;

		if (doors_fir[correct_door] != doors_fir[guess1])	// if these doors aren't the same door, then we just have these two left.
		{
			doors_sec[0] = doors_fir[correct_door];	//for simplicity, we'll denote the correct door as the first door in the second set of doors. It doesn't matter since our contestant doesn't know and chooses randomly again later.
			doors_sec[1] = doors_fir[guess1];
		}
		else	//otherwise, we have to pick another random door to include.
		{
			doors_sec[0] = doors_fir[correct_door];
			while (temp == correct_door)
			{
				temp = rand() % 3;
			}
			doors_sec[1] = doors_fir[temp];
		}

		guess2 = rand() % 2; // select a door from the now 2 choices.
		cout << doors_sec[0] << "   " << doors_sec[guess2] << endl;	//print out the winning door and the selected door.

		if (doors_fir[guess1] == doors_sec[guess2] && doors_sec[0] == doors_sec[guess2])	//kept door choice and won
		{
			kept++;
			tot_correct_kept++;
			cout << "kept, won" << endl;
		}
		if (doors_fir[guess1] == doors_sec[guess2] && doors_sec[0] != doors_sec[guess2])	//kept door choice and lost
		{
			kept++;
			cout << "kept, lost" << endl;
		}
		if (doors_fir[guess1] != doors_sec[guess2] && doors_sec[0] == doors_sec[guess2])	//switched doors and won
		{
			switched++;
			tot_correct_switched++;
			cout << "switched, won" << endl;
		}
		if (doors_fir[guess1] != doors_sec[guess2] && doors_sec[0] != doors_sec[guess2])	//switched doors and lost
		{
			switched++;
			cout << "switched, lost" << endl;
		}
		cout << endl;
	}

	cout << "--Without Switching your guess--" << endl;
	cout << "Number wins: " << tot_correct_kept << "  out of: " << kept << endl;
	cout << "That's: " << ((double)tot_correct_kept / (double)kept * 100) << "% correct" << endl << endl;
	cout << "--With Switching your guess--" << endl;
	cout << "Number wins: " << tot_correct_switched << "  out of: " << switched << endl;
	cout << "That's: " << ((double)tot_correct_switched / (double)switched * 100) << "% correct" << endl;

	cout << "Hit enter to quit." << endl;
	cin.ignore(); // we want the user to hit enter to end, but we don't want to do anything with that input
	return 0;
}

