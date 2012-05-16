#include "headers.h"
#include "Screen.h"
#include "globals.h"
#include "Square.h"
#include "Grid.h"
#include "Pacman.h"
#include "Ghost.h"
#include<iostream>
using namespace std;

int main()
{
	LOG(__func__);
//	Grid grid("simple_level0.txt");
//	grid.StartTheGame();
	Screen terminalscreen;
	terminalscreen.displayMainWindow();
/*	while(true)
	{
		cin.get();

		grid.modifyGrid();
		grid.displayGrid();
	}
	cin.get();
*/
}
