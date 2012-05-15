#ifndef _GRID_H
#define _GRID_H

#include <iostream>
#include <fstream>
#include <string>

#include "globals.h"
#include "Square.h"

using namespace std;

class Grid
{
private:
	Square squares[NUM_ROWS][NUM_COLS];			//Assume that a grid is 21x40

	void initGrid(ifstream &infile);			//Initializes grid from pacman-screen.txt

public:
	Grid(string filename);

	void displayGrid();

	//Find all modified squares and refresh (for double buffering) ----------- To be filled
	void findModifiedSquares();
};

Grid::Grid(string filename)
{

	ifstream infile(filename.c_str());

	initGrid(infile);
	displayGrid();
}

void Grid::initGrid(ifstream &infile)
{
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

			default:
				squares[row][col] = Square(TYPE_BLANK);
			}
			
			col++;
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
			squares[i][j].displayType1();;
		}
		cout << endl;
	}
}

void Grid::findModifiedSquares()
{
}

#endif