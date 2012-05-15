#ifndef _GHOST_H
#define _GHOST_H

#include "globals.h"
#include "Square.h"

class Ghost
{
private:
	int x, y;
	int direction;

public:
	Ghost(){}
	Ghost(int x, int y, int dir);

	//Algorithms to be implemented
	void changeDirection(int dir);		//----------- To be filled
	void move();						//----------- To be filled

	void toString();
};

Ghost::Ghost(int x, int y, int dir)
{
	this->x = x;
	this->y = y;
	this->direction = dir;
}

void Ghost::toString()
{
	cout << "\tGhost\n";
	cout << "Coordinates: (" << x << "," << y << ")" << endl;
	cout << "Direction: " << direction << endl;
}

void Ghost::move()
{

}

void Ghost::changeDirection(int dir)
{
}

#endif
