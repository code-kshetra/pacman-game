/*
<Running Scared. A Terminal implementation of the Classic Pac man game using UNIX Signal, File and Process APIs>
    Copyright (C) <2012>  <Samir Sheriff, Satvik N & Vaishakh B N >
		<Code Kshetra>	

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include "Grid.h"

using namespace std;

int main()
{
	//Grid grid("simple_level0.txt");

	cout << "Select level (Enter number): " << endl;
	int n;
	cin >> n;

	string level = "";
	switch(n)
	{
		case 1: level = "simple_level0.txt";
			break;
		case 2: level = "simple_level1.txt";
			break;
		case 3: level = "new_level.txt";
			break;
		default: level = "new_level.txt";
	}
	

	Grid grid(level);
	grid.StartTheGame();
}

