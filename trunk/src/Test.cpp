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
#include <iostream>
#include <stdio.h>
#include <string>

#include "globals.h"
#include "Square.h"
#include "Grid.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

int main()
{
	/*Square sq(10, 20);
	sq.toString();*/

	Grid grid("pacman-screen.txt");
	
	while(true)
	{
		cin.get();

		grid.modifyGrid();
		grid.displayGrid();
	}

/*	Pacman pacman(1,2, DIR_LEFT);
	pacman.toString();

	Ghost ghosts[4];

	for(int i=0; i<4; i++)
	{
		ghosts[i] = Ghost(i, i+1, DIR_UP);
		ghosts[i].toString();
	}*/

	cin.get();
}
