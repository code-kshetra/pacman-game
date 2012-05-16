#ifndef _GRID_H
#define _GRID_H

#include <iostream>
#include <fstream>
#include <string>

#include "globals.h"
#include "Square.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

/*
 * The gaming screen is made up of a NxN Grid of squares.
 * The Grid class maintains the status of each location in the gaming screen.
 * It also keeps track of Pacman and the Ghosts using their respective objects.
 */
float global_time = 0; // This is beacuse of some problems with the time_count in the Player_Details private class.

void handleAlarmSignal(int);
void handleInterruptSignal(int);

//Extremely bad programming style, but what to do? The guys who invented signal handlers didn't think about class member functions.
class Grid;
Grid *globalGrid;
//GLOBAL VARIABLE ----- BEWARE....DO not use this name anywhere

//A varialbe that holds the count of total no of  . s
static int total_of_dots;
//A variable that holds the current count of the dots.
int present_count_of_dots;


class Grid
{
private:
	//A private class to hold the player details.
	class Player_Details
	{
		float time_count;
		string name;
		int lives;
		int dots_ate;
	public:
		Player_Details();
		void WriteDataToHighScoreFile(); //when the game ends write the data to high scores file.
		inline string  getName();  //read the name
		inline void setTime(float t); //set time_count to t
		inline float getTime(void);  //return time_count
		inline void setDotsAte(int); // set dots ate
		inline int getDotsAte(void); // get dots ate
	};

	Square squares[NUM_ROWS][NUM_COLS];	//Assume that a grid is 32x32

	//Object to hold the details of the Player
	Player_Details player;

	//These 2 variables are used to keep track of the game's characters
	Pacman pacman;
	Ghost ghosts[4];



	void initGrid(ifstream &infile);			//Initializes grid from pacman-screen.txt
	
	/*This set of 3 functions, uses VT100 escape sequences to modify the display of the terminal */
	void clrscr();	
	void setCursor(int x, int y);
	void setCursor(int x, int y, string str);
	
	/*Add/Remove the cursor from terminal*/
	void removeCursor();
	void addCursor();

	/*These two functions are used to change the mode of the terminal to echo or non-echo characters*/
	inline void changeToNonEchoMode(void);
	inline void changeToEchoMode(void);

	/*These are the signal handlers for the SIGINT Interrupt signal and the SIGALRM alarm signal*/
	friend void handleInterruptSignal(int);
	friend void handleAlarmSignal(int);

	/*The function to set the alarm timer as explained in the website*/
	void settimer();

	/*This function takes a character ch read from the stdin and changes the direction  of the pacman*/
	void ProcessUserInput(const int ch);

public:
	//This constructor reads a level map from filename, and calls initGrid() to initialize the squares array. 
	Grid(string filename);

	//This function repositions the cursor at the top left of the screen, and redraws the grid in the terminal.
	void displayGrid();

	//This function does some timer work, signal() work and starts the Game.
	void StartTheGame();

	//Find all modified squares and refresh (for double buffering) ----------- To be filled
	void findModifiedSquares();

	/*This method will be called when a timer goes off, and calls the move() methods of Pacman and all 4 Ghosts
		to update their locations (wherever possible). This function will be used by the signal handlers of Screen.h */
	void modifyGrid();

	/* Using the concept of double buffering, this method minimizes the flicker when the screen is redrawn, by	
	 * 	drawing only the squares that are modified.
 	 */
	void updateVisualGrid();
};


void Grid::Player_Details::WriteDataToHighScoreFile()
{
	FILE *fp;
	fp=fopen("score.txt","a");
	fprintf(fp,"%s %f %d \n", (this->name).c_str(), global_time, total_of_dots - present_count_of_dots);
	fclose(fp);
}	

Grid::Grid(string filename)
{
	LOG(__func__); //Calling VLC here
	system("cvlc Up.mp3 &"); // The absolute path of the file is to be added.
	sleep(1);
	clrscr();

	ifstream infile(filename.c_str());
	total_of_dots = 0;
	initGrid(infile); // after this call the total_of_dots has the count of total .s
	present_count_of_dots = total_of_dots;
	//displayGrid();

	//For the signal handler
	globalGrid = this;		//GLOBAL VARIABLE INIT
}

void Grid::initGrid(ifstream &infile)
{
	LOG(__func__);
	int numGhost = 0;
	int pacRow = 0;
	int pacCol = 0;

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
				total_of_dots += 1;//count only the .s when initializing.
				break;

			case '%':
				squares[row][col] = Square(TYPE1_POWERPOINT);
				break;

			case 'C':
				pacRow = row;
				pacCol = col;
				squares[row][col] = Square(TYPE_BLANK);
				squares[row][col].setType2(TYPE2_PACMAN);
				break;

			case '@':
				ghosts[numGhost++] = Ghost(row, col, DIR_RIGHT);
				squares[row][col] = Square(TYPE_BLANK);
				squares[row][col].setType2(TYPE2_GHOST);
				break;

			default:
				squares[row][col] = Square(TYPE_BLANK);
			}
			
			col++;
			pacman = Pacman(pacRow, pacCol, DIR_LEFT);
		}
		row++;
	}
}

void Grid::displayGrid()
{
	LOG(__func__);
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			setCursor(i, j);
			if(squares[i][j].getType2() != TYPE_BLANK)
			{
				squares[i][j].displayType2();
			}
			else
			{
				squares[i][j].displayType1();
			}
		}
		cout << endl;
	}
	player.setDotsAte(total_of_dots - present_count_of_dots); //This is necessary coz pacman eats variable no of dots
	cout<<"Lives: "<<"\t\t\t\t Time : "<<global_time<<"\t\tScore : "<<(total_of_dots - present_count_of_dots)<<" (a lot of bonus included)"<<endl;
	cout<<"Press ^C to pause the game!"<<endl;
	/*
	pacman.toString();

	for(int i=0; i<4; i++)
	{
		ghosts[i].toString();
	}*/
}

void Grid::updateVisualGrid()
{
	LOG(__func__);
	int count_of_change = 0;
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			if(squares[i][j].isChanged())
			{
				setCursor(i, j);

				if(squares[i][j].getType2() != TYPE_BLANK)
				{
					squares[i][j].displayType2();
				}
				else
				{
					squares[i][j].displayType1();
				}
				squares[i][j].resetChanged();
				++count_of_change; // I need to put this here and count only those . changed to spaces .. Samir find out. I'm confused with these type1,type2 :P
			}
		}
	}
	present_count_of_dots -= count_of_change;
	player.setDotsAte(total_of_dots - present_count_of_dots); //This is necessary coz pacman eats variable no of dots
	setCursor(32, 0);
	cout<<"Lives: "<<"\t\t\t\t Time : "<<global_time<<"\t\tScore : "<<player.getDotsAte()<<endl;
	//cout<<"Lives: "<<"\t\t\t\t Time : "<<global_time<<endl; //Samir figure out a way to update the scores here we need to print these lines
	//cout<<"Press ^C to pause the game!"<<endl;
}

void Grid::findModifiedSquares()
{
	LOG(__func__);
}

void Grid::removeCursor()
{
	cout << "\033[?25l";
}

void Grid::addCursor()
{
	cout << "\033[?25h";
}

void Grid::setCursor(int x, int y)
{
	cout <<	"\033[" << x+1 << ";" << y+1 << "H";
}


void Grid::setCursor(int x, int y, string str)
{
	setCursor(x, y);
        cout << str;
}

void Grid::clrscr()
{
	LOG(__func__);
	cout <<	"\033[2J";
}

void Grid::modifyGrid()
{
	LOG(__func__);
	//Right now, if Pacman is blocked by a wall, it tries out a different direction to move. 
	if(pacman.move(squares) == BLOCKED_BY_WALL_FLAG)
	{
		//pacman.changeDirection((pacman.getDirection() + 1) % 4);
	}
	
	for(int i=0; i<4; i++)
		if(ghosts[i].move(squares, pacman) == GAME_OVER_FLAG)
		{
			//cout << "Ghost " << i << " ate Pacman...NOT Exiting...Continuing";
			//exit(0);		//Handle this properly later..Go back to main menu.
		}	

	//pacman.toString();
}
void Grid::changeToEchoMode(void)
{
	system("stty -raw echo");
	LOG("Terminal changed to echo mode");
}
void Grid::changeToNonEchoMode(void)
{
	LOG("Terminal changed to non-echo mode");
	system("stty raw -echo isig");
}

void handleInterruptSignal(int signo)
{
	LOG(__func__);
	signal(SIGALRM, SIG_IGN);
	int i;
	LOG("//Code to pause the game or hang pacman and the ghosts");
	system("stty -raw echo");
	LOG("The terminal in normal echo mode!");
	cout<<"Lives: "<<"\t\t\t\t Time : "<<global_time<<"\t\tScore : "<<(total_of_dots - present_count_of_dots)<<" (a lot of bonus included)"<<endl;
	cout<<"Interrupt Recieved!\n";
	cout<<"Do you Want to End the game[1-yes, 0-no]\n";
	cin>>i;
	signal(SIGINT,handleInterruptSignal); 
	if(i)
	{
		cout<<"Game Ended!"<<endl;
		cin.get();
		system("pkill vlc");
		exit(0);
		//displayMainWindow();
	}
	cout<<"Continue the game\n"<<"You Score is  "<<(total_of_dots-present_count_of_dots)<<"\n"<<        //supposed to call player.getDotsAte() :-( Not possible
	       	"Press any key to continue... "<<endl;
	cin.get();
	cin.get();
	signal(SIGALRM, handleAlarmSignal);
	LOG("The terminal entered the non-echo mode");
	system("stty raw -echo isig");

}
void handleAlarmSignal(int signo)
{
	LOG(__func__);
	int i;
	LOG(" ");
	global_time += 0.04;

	globalGrid->modifyGrid();
	globalGrid->updateVisualGrid();

	signal(SIGALRM,handleAlarmSignal);
}
void Grid::ProcessUserInput(const int pressed_key)
{
	switch(pressed_key)
	{
		case 'J':
		case 'j':   
		 	    if(pacman.isValidDirection(squares, DIR_LEFT))
				pacman.changeDirection(DIR_LEFT);
			    break;
		case 'I':
		case 'i':   
			    if(pacman.isValidDirection(squares, DIR_UP))	
				pacman.changeDirection(DIR_UP);
			    break;
		case 'L':
		case 'l': 
			    if(pacman.isValidDirection(squares, DIR_RIGHT))
				pacman.changeDirection(DIR_RIGHT);
			  break;
		case 'K':
		case 'k': 
			    if(pacman.isValidDirection(squares, DIR_DOWN))
				pacman.changeDirection(DIR_DOWN);
			  break;
		default: LOG("Invalid Key pressed!");
			 break;
	}
	//modifyGrid();
	

}
void Grid::StartTheGame()
{
	LOG(__func__);
	char key_pressed;
	signal(SIGINT, handleInterruptSignal);
	signal(SIGALRM, handleAlarmSignal);
	settimer();

	displayGrid();
	
	while(1)
	{
		removeCursor();
		changeToEchoMode();
		//clrscr();
		//modifyGrid();
		//updateVisualGrid(); //We need to call this inside the handleAlarmSignal() [Video camera issue]
		//displayGrid();
		//cin.get();
		changeToNonEchoMode();
		if(read(STDIN_FILENO, &key_pressed , sizeof(char))>0)
		{
			cout<<endl;//We need this otherwise the characters don't move.
			//cout<<"key_pressed  =" <<key_pressed<<endl;
			//cout<<' '; //See here 
			ProcessUserInput(key_pressed);
		}
		else
		{
			//  check for EINTR and continue the loop

		}

		addCursor();
	
	}
}

void Grid::settimer()
{
	LOG(__func__);
     /* for time measurements, delay between shape movements */
     struct itimerval h;

     /* define the first timer to set off after 40,000 micro seconds.  */
     h.it_value.tv_sec = 0;
     h.it_value.tv_usec = 40000;
     /* define the interval between each two timer set-offs ('clicks') */
     /* to be 40,000 micro seconds as well.                            */
     h.it_interval.tv_sec = 0;
     h.it_interval.tv_usec = 40000;

     /* finally, start off the timer */
     setitimer(ITIMER_REAL,&h,0);

}

Grid::Player_Details::Player_Details()
{
	LOG(__func__);
	cout<<"Enter the player name: ";
	cin>>name;
	global_time = time_count = 0;
	lives = 1;
	cout<<"Press any key to start the game!"<<endl;
	cin.get();
	cin.get();
}
string Grid::Player_Details::getName()
{
	LOG(__func__);
	return name;
}
void Grid::Player_Details::setTime(float t)
{
	LOG(__func__);
	time_count = t;
}
float  Grid::Player_Details::getTime(void)
{
	LOG(__func__);
	return time_count;
}
void Grid::Player_Details::setDotsAte(int dt)
{
	dots_ate = dt;
}
int Grid::Player_Details::getDotsAte(void)
{
	return dots_ate;
}
#endif
