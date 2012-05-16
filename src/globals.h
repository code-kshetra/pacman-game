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
#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "headers.h"
//To define the type of object stored at a certain square
const int TYPE1_DOT = 1;
const int TYPE1_POWERPOINT = 2;
const int TYPE1_WALL = 3;

const int TYPE2_PACMAN = 4;
const int TYPE2_GHOST = 5;

const int TYPE_BLANK = 6;	

//To define the GRID
const int NUM_ROWS = 32;
const int NUM_COLS = NUM_ROWS;

//Direction of movement
const int DIR_LEFT = 1;
const int DIR_RIGHT = 2;
const int DIR_UP = 3;
const int DIR_DOWN = 4;

//Movement Error Flags
const int BLOCKED_BY_WALL_FLAG = -3;
const int GAME_OVER_FLAG = -4;
const int SUCCESS_FLAG = 0;
const int GHOST_MOVEMENT_ILLEGAL_FLAG = -5;

const int PACMAN_INVERSE_RELATIVE_SPEED = 2;
const int GHOST_INVERSE_RELATIVE_SPEED = 2 * PACMAN_INVERSE_RELATIVE_SPEED;

//For Logging messages
#define DEBUG 0
#if DEBUG
#define LOG(s) cout<<s<<endl;
#else
#define LOG(s) /* */
#endif
#endif
