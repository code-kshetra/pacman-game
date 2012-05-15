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
