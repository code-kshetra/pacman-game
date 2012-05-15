#include "headers.h"
#include "Screen.h"
#include<iostream>
using namespace std;

int main()
{
	LOG(__func__);
	Screen gamescreen;
	gamescreen.displayMainWindow();
/*	while(1)
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
