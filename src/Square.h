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
#ifndef _SQUARE_H
#define _SQUARE_H

#include "globals.h"
#include <string>
#include <iostream>

using namespace std;

/*
 * The Game consists of a grid, which is an MxN matrix of squares, which are defined below.
 */

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

	void setCountOfBlanks(int);
	int getCountOfBlanks(void);
	
};

Square::Square(int t1)
{
	//LOG(__func__);
	this->changed = false;
	type1 = t1;
	type2 = TYPE_BLANK;

}

int Square::getType1()
{
	//LOG(__func__);
	return type1;
}

void Square::setType1(int t1)
{	
	//LOG(__func__);
	changed = true;
	type1 = t1;
}

void Square::displayType1()
{
	//LOG(__func__);
	displayType(type1);
}

int Square::getType2()
{
	//LOG(__func__);
	return type2;
}

void Square::setType2(int t2)
{
	//LOG(__func__);
	changed = true;
	type2 = t2;
}

void Square::displayType2()
{
	//LOG(__func__);
	displayType(type2);
}

bool Square::isChanged()
{
	//LOG(__func__);
	return changed;
}

void Square::resetChanged()
{
	//LOG(__func__);
	changed = false;
}

void Square::toString()
{
	LOG(__func__);
	cout << "TYPES = " << type1 << "\t" << type2 << endl;
	cout << "Changed = " << changed << endl;
}


void Square::displayType(int type)
{
	//LOG(__func__);
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
//	cout<<' '; //a space to look neat!		-- The Cause of a BUG!  I'll give you 100 bugs for finding this BUG :-)
}
#endif
