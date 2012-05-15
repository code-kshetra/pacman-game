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

class Grid
{
private:
	Square squares[NUM_ROWS][NUM_COLS];			//Assume that a grid is 21x40

	Pacman pacman;
	Ghost ghosts[4];


	void initGrid(ifstream &infile);			//Initializes grid from pacman-screen.txt
	
	void clrscr();	
	void setCursor(int x, int y);
	void setCursor(int x, int y, string str);
public:
	Grid(string filename);

	void displayGrid();

	//Find all modified squares and refresh (for double buffering) ----------- To be filled
	void findModifiedSquares();
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
	cout <<	"\033[" << x << ";" << y << "H";
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

#endif
