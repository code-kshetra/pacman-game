#ifndef _PACMAN_H
#define _PACMAN_H

#include "globals.h"
#include "Square.h"

/*
 * This class is used to keep track of the current status of Pacman,
 * 	and to make it come to life.
 */

class Pacman
{
private:
	int row, col;		//The row and col of the Grid where Pacman is currently located.
	int direction;		//One of the four DIR_xxx constants
	int moveTimer;			//This is to ensure that the speed of the ghost < speed of Pacman

public:
	Pacman(){}
	Pacman(int row, int col, int dir);	//This constructor is called, when the game screen is initialized for the first time.
	
	//Returns a part of the coordinates.
	int getRow();
	int getCol();

	int getDirection();	//Returns the current direction that Pacman is facing.

	//This method is used to change the direction that Pacman is facing.
	void changeDirection(int dir);	 
	
	//This method is needed when a user tries to change the direction of Pacman, when it is invalid
	bool isValidDirection(Square squares[NUM_ROWS][NUM_COLS], int dir);

	/*
	 * This method is used to move Pacman, wherever and whenever possible.
	 * 	Pacman can move in its current direction only if there is no wall in front of it.
	 *		If a wall is present, Pacman doesn't move and this function returns BLOCKED_BY_WALL_FLAG.
	 *		If a wall is not present, Pacman moves and the grid of squares is modified to accomodate this change.	      *		and if dots are present, they are eaten by Pacman (Still have to take care of this feature)
  	 */
	int move(Square squares[NUM_ROWS][NUM_COLS]);		

	void toString();
};

Pacman::Pacman(int x, int y, int dir)
{
	this->row = x;
	this->col = y;
	this->direction = dir;

	moveTimer = PACMAN_INVERSE_RELATIVE_SPEED;
}

int Pacman::getRow()
{
	return row;
}

int Pacman::getCol()
{
	return col;
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
	//First, check if it's the Pacman's turn to move (Note: This is done to reduce Pacman's speed compared to the refresh rate of the signal handler.
	if(moveTimer != 0)
	{
		moveTimer--;
		return GHOST_MOVEMENT_ILLEGAL_FLAG;
	}
	
	//Reset Timer
	moveTimer = PACMAN_INVERSE_RELATIVE_SPEED;



	//Pacman can only move in 'direction' if there is no Wall.
	//So, check if there's a wall.
	/*
	 * If a wall is present, do not move Pacman but return BLOCKED_BY_WALL_FLAG.
	 *	However, if a wall is NOT present, clear the current square occupied by Pacman
	 * 		and change Pacman's location to the adjacent square (depending on its direction)
	 * 		After that, readjust the Grid of Squares to show Pacman at this new location
	 *			and return SUCCESS_FLAG;
 	 */

	switch(direction)
	{
		case DIR_LEFT:
			LOG("Left");
			if(squares[row][col-1].getType1() == TYPE1_WALL)
				return BLOCKED_BY_WALL_FLAG;
			else
			{
				squares[row][col].setType1(TYPE_BLANK);
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
				squares[row][col].setType1(TYPE_BLANK);
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
				squares[row][col].setType1(TYPE_BLANK);
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
				squares[row][col].setType1(TYPE_BLANK);
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

bool Pacman::isValidDirection(Square squares[NUM_ROWS][NUM_COLS], int dir)
{
	switch(dir)
	{
		case DIR_LEFT:
	                if(squares[row][col-1].getType1() == TYPE1_WALL)
				return false;
			break;
		case DIR_RIGHT:
			if(squares[row][col+1].getType1() == TYPE1_WALL)
				return false;
			break;
		case DIR_UP:
			if(squares[row-1][col].getType1() == TYPE1_WALL)
				return false;
			break;
		case DIR_DOWN:
			if(squares[row+1][col].getType1() == TYPE1_WALL)
				return false;
			break;
	}	
	return true;
}

#endif
