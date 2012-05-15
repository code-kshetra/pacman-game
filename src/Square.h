#ifndef _SQUARE_H
#define _SQUARE_H

#include "globals.h"
#include <string>
#include <iostream>

using namespace std;

class Square
{
private:

	int type1;			//Should be one of the TYPE1_xxx constants
	int type2;			//Should be one of the TYPE2_xxx constants

	bool changed;		//Needed for double buffering to record only those squares that have been modified and need to be redrawn.

	void displayType(int type);

public:
	
	Square(){}
	Square(int t1);
	
	int getType1();
	void setType1(int t1);
	void displayType1();

	int getType2();
	void setType2(int t2);
	void displayType2();

	bool isChanged();
	void resetChanged();

	void toString();
	
};

Square::Square(int t1)
{
	this->changed = false;

	type1 = t1;
	type2 = TYPE_BLANK;
}

int Square::getType1()
{
	return type1;
}

void Square::setType1(int t1)
{	
	changed = true;
	type1 = t1;
}

void Square::displayType1()
{
	displayType(type1);
}

int Square::getType2()
{
	return type2;
}

void Square::setType2(int t2)
{
	changed = true;
	type2 = t2;
}

void Square::displayType2()
{
	displayType(type2);
}

bool Square::isChanged()
{
	return changed;
}

void Square::resetChanged()
{
	changed = false;
}

void Square::toString()
{
	cout << "TYPES = " << type1 << "\t" << type2 << endl;
	cout << "Changed = " << changed << endl;
}


void Square::displayType(int type)
{
	switch(type)
	{
	case TYPE1_DOT: 
		cout << '.';
		break;
	case TYPE1_WALL:
		cout << 'W';
		break;
	case TYPE1_POWERPOINT:
		cout << '%';
		break;
	case TYPE2_PACMAN:
		cout << 'C';
		break;
	case TYPE2_GHOST:
		cout << '@';
		break;
	case TYPE_BLANK:
		cout << ' ';
		break;
	default:
		cout << '?';
	}
}

#endif
