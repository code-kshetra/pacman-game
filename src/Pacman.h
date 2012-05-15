#ifndef _PACMAN_H
#define _PACMAN_H

#include "globals.h"
#include "Square.h"

class Pacman
{
private:
	int x, y;
	int direction;

public:
	Pacman(){}
	Pacman(int x, int y, int dir);

	//Algorithms to be implemented
	void changeDirection(int dir);	 //----------- To be filled
	void move();					//----------- To be filled

	void toString();
};

Pacman::Pacman(int x, int y, int dir)
{
	this->x = x;
	this->y = y;
	this->direction = dir;
}

void Pacman::toString()
{
	cout << "\tPacman\n";
	cout << "Coordinates: (" << x << "," << y << ")" << endl;
	cout << "Direction: " << direction << endl;
}

void Pacman::move()
{

}

void Pacman::changeDirection(int dir)
{
}

#endif
