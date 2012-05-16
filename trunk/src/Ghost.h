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
#ifndef _GHOST_H
#define _GHOST_H

#include "globals.h"
#include "Square.h"
#include "Pacman.h"

/*
 * This class is used to keep track of the current status of a Ghost,
 * 	and to make it come to life.
 */

class Ghost
{
private:
	int row, col;
	int direction;
	int moveTimer;			//This is to ensure that the speed of the ghost < speed of Pacman

public:
	Ghost(){}
	Ghost(int row, int col, int dir); //This constructor is called, when the game screen is initialized for the first time.

	int getDirection();	//Returns the current direction that the Ghost is facing.
	void changeDirection(int dir);	 //This method is used to change the direction that Pacman is facing

	/*
	 * This method is used to move a ghost, wherever and whenever possible.
	 * 	Pacman can move in its current direction only if there is no wall in front of it.
	 *		If a wall is present, Pacman doesn't move and this function returns BLOCKED_BY_WALL_FLAG.
	 * 		If a wall is not present, Pacman moves and the grid of squares is modified to accomodate this change.
  	 */

	int move(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman);						//----------- To be filled

	void toString();

	int getBestDirection(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman);	//Finds a valid direction for the ghost, that brings it closer to Pacman.

	/*
	 * First preference is given to Vertical movement...Then, when that fails, this function is used.
	 */
	int getHorizontalDirection(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman, int lastResortDirection);

};

Ghost::Ghost(int x, int y, int dir)
{
	this->row = x;
	this->col = y;
	this->direction = dir;

	moveTimer = GHOST_INVERSE_RELATIVE_SPEED;
}

void Ghost::toString()
{
	cout << "\tGhost\n";
	cout << "Coordinates: (" << row << "," << col << ")" << endl;
	cout << "Direction: " << direction << endl;
}

//Returns an error flag if it cannot move
int Ghost::move(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman)
{
	//First, check if a ghost and pacman are on the same square...If so, Game is over!!!
	if(row == pacman.getRow() && col == pacman.getCol())
		return GAME_OVER_FLAG;
	

	//Second, check if it's the Ghost's turn to move (Note: A ghost moves 1 step for every 2 steps of Pacman.
	if(moveTimer != 0)
	{
		moveTimer--;
		return GHOST_MOVEMENT_ILLEGAL_FLAG;
	}
	
	//Reset Timer
	moveTimer = GHOST_INVERSE_RELATIVE_SPEED;

	//A Ghost can only move in 'direction' if there is no Wall.
	//So, check if there's a wall.
	/*
	 * If a wall is present, search for a valid location to move to.
	 *	However, if a wall is NOT present, clear the current square occupied by the Ghost
	 * 		and change ghost's location to the adjacent square (depending on its direction)
	 * 		After that, readjust the Grid of Squares to show the ghost at this new location
	 *			and return SUCCESS_FLAG;
 	 */

	
	
	changeDirection(getBestDirection(squares, pacman));


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
	
	squares[row][col].setType2(TYPE2_GHOST);
	
	//Ensure that the Ghost and Pacman aren't in the same square. If they are, the game is over!!
	if(row == pacman.getRow() && col == pacman.getCol())
		return GAME_OVER_FLAG;


	return SUCCESS_FLAG;
}

int Ghost::getBestDirection(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman)
{
	if(pacman.getRow() == row)
	{
		//Pacman is on the same row as the Ghost
		if(squares[row+1][col].getType1() != TYPE1_WALL)			//Choosing the correct last resort
			return getHorizontalDirection(squares, pacman, DIR_DOWN);		
		else
			return getHorizontalDirection(squares, pacman, DIR_UP);
	}

	if(pacman.getRow() > row)
	{
		//Pacman is below the Ghost

		//First, try to move the Ghost down, if possible
		if(squares[row+1][col].getType1() != TYPE1_WALL && squares[row+1][col].getType2() != TYPE2_GHOST)
		{
			//Valid Move
			return DIR_DOWN;
		}
		else
		{
			return getHorizontalDirection(squares, pacman, DIR_UP);	
		}		
	}
	else
	{
		//Pacman is above the Ghost
		if(squares[row-1][col].getType1() != TYPE1_WALL && squares[row-1][col].getType2() != TYPE2_GHOST)
		{
			//Valid Move
			return DIR_UP;
		}
		else
			return getHorizontalDirection(squares, pacman, DIR_DOWN);
	}

	return 1;
}


int Ghost::getHorizontalDirection(Square squares[NUM_ROWS][NUM_COLS], Pacman pacman, int lastResortDirection)
{
	//Now, we have to move left or right, depending on the location of Pacman
	if(pacman.getCol() < col)
	{
		//Pacman is to the Left of the Ghost. Try to move if possible
		if(squares[row][col-1].getType1() != TYPE1_WALL && squares[row][col-1].getType2() != TYPE2_GHOST)
			return DIR_LEFT;

		//Now, try to move right
		if(squares[row][col+1].getType1() != TYPE1_WALL && squares[row][col+1].getType2() != TYPE2_GHOST)
			return DIR_RIGHT;
		else				//Last option
			return lastResortDirection;
	}
	else
	{
		//Pacman is to the Right of the Ghost. Try to move if possible
		if(squares[row][col+1].getType1() != TYPE1_WALL && squares[row][col+1].getType2() != TYPE2_GHOST)
			return DIR_RIGHT;

		//Now, try to move left
		if(squares[row][col-1].getType1() != TYPE1_WALL && squares[row][col-1].getType2() != TYPE2_GHOST)
			return DIR_LEFT;
		else				//Last option
			return lastResortDirection;
	}

}

int Ghost::getDirection()
{
	return direction;
}


void Ghost::changeDirection(int dir)
{
	direction = dir;
}

#endif
