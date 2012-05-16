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
