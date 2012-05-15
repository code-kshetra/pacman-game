#ifndef _GRID_H
#define _GRID_H

#include <iostream>
#include <fstream>
#include <string>

#include "globals.h"
#include "Square.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

/*
 * The gaming screen is made up of a MxN Grid of squares.
 * The Grid class maintains the status of each location in the gaming screen.
 * It also keeps track of Pacman and the Ghosts using their respective objects.
 */

class Grid
{
private:
	Square squares[NUM_ROWS][NUM_COLS];			//Assume that a grid is 21x40

	//These 2 variables are used to keep track of the game's characters
	Pacman pacman;
	Ghost ghosts[4];


	void initGrid(ifstream &infile);			//Initializes grid from pacman-screen.txt
	
	/*This set of 3 functions, uses VT100 escape sequences to modify the display of the terminal */
	void clrscr();	
	void setCursor(int x, int y);
	void setCursor(int x, int y, string str);
public:
	//This constructor reads a level map from filename, and calls initGrid() to initialize the squares array. 
	Grid(string filename);

	//This function repositions the cursor at the top left of the screen, and redraws the grid in the terminal.
	void displayGrid();

	//Find all modified squares and refresh (for double buffering) ----------- To be filled
	void findModifiedSquares();

	/*This method will be called when a timer goes off, and calls the move() methods of Pacman and all 4 Ghosts
		to update their locations (wherever possible). This function will be used by the signal handlers of Screen.h */
	void modifyGrid();
};

Grid::Grid(string filename)
{
	clrscr();

	ifstream infile(filename.c_str());

	initGrid(infile);
	displayGrid();
}

void Grid::initGrid(ifstream &infile)
{
	int numGhost = 0;
	int pacRow = 0;
	int pacCol = 0;

	int row = 0;	
	while(true)
	{
		string line;
		getline(infile, line);

		if(line == "")
			break;
		
		
		int col = 0;
		for(int i=0; i<line.length(); i++)
		{
			switch(line[i])
			{
			case 'W':
				squares[row][col] = Square(TYPE1_WALL);
				break;

			case '.':
				squares[row][col] = Square(TYPE1_DOT);
				break;

			case '%':
				squares[row][col] = Square(TYPE1_POWERPOINT);
				break;

			case 'C':
				pacRow = row;
				pacCol = col;
				squares[row][col] = Square(TYPE_BLANK);
				squares[row][col].setType2(TYPE2_PACMAN);
				break;

			case '@':
				ghosts[numGhost++] = Ghost(row, col, DIR_RIGHT);
				squares[row][col] = Square(TYPE_BLANK);
				squares[row][col].setType2(TYPE2_GHOST);
				break;

			default:
				squares[row][col] = Square(TYPE_BLANK);
			}
			
			col++;
			pacman = Pacman(pacRow, pacCol, DIR_LEFT);
		}
		row++;
	}
}

void Grid::displayGrid()
{
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			setCursor(i, j);
			if(squares[i][j].getType2() != TYPE_BLANK)
			{
				squares[i][j].displayType2();
			}
			else
			{
				squares[i][j].displayType1();
			}
		}
		cout << endl;
	}
	
	pacman.toString();

	for(int i=0; i<4; i++)
	{
		ghosts[i].toString();
	}
}

void Grid::findModifiedSquares()
{
}

void Grid::setCursor(int x, int y)
{
	cout <<	"\033[" << x+1 << ";" << y+1 << "H";
}


void Grid::setCursor(int x, int y, string str)
{
	setCursor(x, y);
        cout << str;
}

void Grid::clrscr()
{
	cout <<	"\033[2J";
}

void Grid::modifyGrid()
{
	//Right now, if Pacman is blocked by a wall, it tries out a different direction to move. 
	if(pacman.move(squares) == BLOCKED_BY_WALL_FLAG)
		pacman.changeDirection((pacman.getDirection() + 1) % 4);
		
	pacman.toString();
}

#endif
