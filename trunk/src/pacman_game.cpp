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
	Grid grid("simple_level0.txt");
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
/*	Screen gamescreen;
	gamescreen.displayMainWindow();
	while(1)
	{
		int opt = gamescreen.displayOptionsWindow();
		switch(opt)
		{
			case 1: gamescreen.displayGameWindow();
				break;
			case 2: gamescreen.displayHighScoresWindow();
				break;
			case 3:exit(0);
			default:
			       cout<<"Invalid Option Selected!"<<endl;
			       cin.get();
		}
	}
*/
}
