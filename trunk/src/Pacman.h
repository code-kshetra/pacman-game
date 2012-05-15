#ifndef _PACMAN_H
#define _PACMAN_H

#include "globals.h"
#include "Square.h"

class Pacman
{
private:
	int row, col;
	int direction;

public:
	Pacman(){}
	Pacman(int row, int col, int dir);

	int getDirection();

	//Algorithms to be implemented
	void changeDirection(int dir);	 //----------- To be filled
	int move(Square squares[NUM_ROWS][NUM_COLS]);					//----------- To be filled

	void toString();
};

Pacman::Pacman(int x, int y, int dir)
{
	this->row = x;
	this->col = y;
	this->direction = dir;
}

void Pacman::toString()
{
	cout << "\tPacman\n";
	cout << "Coordinates: (" << row << "," << col << ")" << endl;
	cout << "Direction: " << direction << endl;
}

//Returns an error flag if it cannot move
int Pacman::move(Square squares[NUM_ROWS][NUM_COLS])
{
	//Pacman can only move in 'direction' if there is no Wall.
	//So, check if there's a wall.

	switch(direction)
	{
		case DIR_LEFT:
			LOG("Left");
			if(squares[row][col-1].getType1() == TYPE1_WALL)
				return BLOCKED_BY_WALL_FLAG;
			else
			{
				squares[row][col].setType2(TYPE_BLANK);
				col = col-1;
			}
			break;

		case DIR_RIGHT:
			LOG("Right");
			if(squares[row][col+1].getType1() == TYPE1_WALL)
				return BLOCKED_BY_WALL_FLAG;
			else
			{
				squares[row][col].setType2(TYPE_BLANK);
				col = col+1;
			}
			break;

		case DIR_UP:
			LOG("Up");
			if(squares[row-1][col].getType1() == TYPE1_WALL)
				return BLOCKED_BY_WALL_FLAG;
			else
			{
				squares[row][col].setType2(TYPE_BLANK);
				row = row-1;
			}
			break;

		case DIR_DOWN:
			LOG("Down");
			if(squares[row+1][col].getType1() == TYPE1_WALL)
				return BLOCKED_BY_WALL_FLAG;
			else
			{				
				squares[row][col].setType2(TYPE_BLANK);
				row = row+1;
			}
			break;

	}
	
	squares[row][col].setType2(TYPE2_PACMAN);
	return SUCCESS_FLAG;
}

int Pacman::getDirection()
{
	return direction;
}

void Pacman::changeDirection(int dir)
{
	direction = dir;
}

#endif
