/* 
 * File:   Screen.h
 * Author: nsatvik
 *
 * Created on 14 May, 2012, 11:14 PM
 */
#include "Grid.h"
#include<iostream>
using namespace std;
#ifndef SCREEN_H
#define	SCREEN_H
#define SCREEN_SIZE 32 
#define DEBUG 0
#if DEBUG
   #define LOG(s) cout<<s<<endl;
#else
   #define LOG(s) /* */
#endif
//int lives_count;
//int time_count;
class Screen
{
 private:
//Variables
      int option;
 //     char game_area[SCREEN_SIZE][SCREEN_SIZE];
// Other Game Window Helper Functions here
  //    void displayGame_Area();
  //    void initGame_Area();
  //    friend void gameInterruptSignalHandler(int ); //You cannot create a signal handler as a memeber function.
  //    friend void gameAlarmSignalHandler(int ); //You cannot create a signal handler as a memeber function.
      
 public:
      Screen();
      int displayOptionsWindow();
      void displayGameWindow();
      void displayMainWindow();
      void displayHighScoresWindow();
      ~Screen();
};
Screen::Screen()
{
	option = -1;
/*
	lives_count = 4;
	time_count = 0;
	LOG(__func__);
	bzero(game_area,sizeof(game_area));
	initGame_Area();
	displayGame_Area();
*/
}
/*void Screen::initGame_Area()
{
	time_count = 0;
	for(int i=0 ;i<SCREEN_SIZE;i++)
	{
		game_area[0][i] = '#';
		game_area[i][0] = '#';
		game_area[SCREEN_SIZE-1][i] = '#';
		game_area[i][SCREEN_SIZE-1] = '#';
	}
	for(int i=1;i<SCREEN_SIZE-1;i++)
	{
		for(int j=1;j<SCREEN_SIZE-1;j++)
			game_area[i][j] = '.';

	}
	game_area[1][1] = '@'; 
	game_area[SCREEN_SIZE-2][SCREEN_SIZE-2] = '@';
	game_area[23][SCREEN_SIZE-2] = '@';
	game_area[SCREEN_SIZE-2][16] = '@';
	game_area[15][15] = 'C';
}
*/
Screen::~Screen()
{
	LOG(__func__);

}
int Screen::displayOptionsWindow()
{
	LOG(__func__);
	system("clear;banner pacman");
	//system("tput cup 200 200");
	cout<<"Welcome to the Terminal Pacman Game!"<<endl;
	//system("tput cup 200 201");
	cout<<"1 - New Game\n";
//	system("tput cup 200 202");
	cout<<"2 - High Scrores\n";
	//system("tput cup 200 203");
	cout<<"3 - Exit Game\n";

	cout<<"Your Option $ " ;
	cin>>option;
	return option;
}
/*void gameInterruptSignalHandler(int signo)
{
	LOG(__func__);
	int i;
	LOG("//Code to pause the game or hang pacman and the ghosts");
	system("stty -raw echo");
	LOG("The terminal in normal echo mode!");
	cout<<"Interrupt Recieved!\n";
	cout<<"Do you Want to End the game[1-yes, 0-no]\n";
	cin>>i;
	signal(SIGINT,gameInterruptSignalHandler); 
	if(i)
	{
		cout<<"Game Ended!"<<endl;
		cin.get();
		cout<<"There is a problem here see the code in "<<__func__<<endl;
		exit(0);
		//displayMainWindow();
	}
	
	cout<<"Continue the game"<<endl;
	LOG("The terminal entered the non-echo mode");
	system("stty raw -echo isig");

}
void gameAlarmSignalHandler(int signo)
{
	LOG(__func__);
	int i;
	LOG("//Code to update the scores/time see Pacman/demos/clock.cpp");
	time_count++;
	signal(SIGALRM,gameAlarmSignalHandler);
}

void Screen::displayGame_Area()
{
	LOG(__func__);
	system("clear");
	cout<<"Lives: "<<lives_count<<"\t\t\t\t"<<"Time : "<<time_count<<endl;
	for(int i=0; i<SCREEN_SIZE ; ++i)
	{
		for(int j=0; j<SCREEN_SIZE ; ++j)
		{
			cout<<game_area[i][j]<<' ';

		}
		cout<<endl;
	}
	cout<<"Press ^C to Interrupt!"<<endl;

}
*/
void Screen::displayGameWindow()
{
	LOG(__func__);
	// I've to Call the GRID class object here :)
	LOG("// I've to Call the GRID class object here :)");
	LOG("//****** Some member function of the Grid class has to do all the following things.");
	system("./game");
	//Grid grid("simple_level0.txt");
	//grid.StartTheGame();
//	initGame_Area();
//	displayGame_Area();
//	LOG("The terminal entered the non-echo mode");
//	LOG("Press ^C to exit ");
//	system("stty raw -echo isig");
/*	signal(SIGINT, gameInterruptSignalHandler);
	signal(SIGALRM, gameAlarmSignalHandler);
	while(1)
	{
		sleep(1);
		system("stty -raw echo");
		displayGame_Area(); //Need to enter echo mode and re-enter non-echo mode for displaying (See if you can find a better solution!)
		system("stty raw -echo isig");
		alarm(1);
	}
*/
}
void Screen::displayMainWindow()
{
	LOG(__func__);
	while(1)
	{
		displayOptionsWindow();
		switch(option)
		{
			case 1: displayGameWindow();
				break;
			case 2: displayHighScoresWindow();
				break;
			case 3:exit(0);
			default:
			       cout<<"Invalid Option Selected!"<<endl;
			       cin.get();
		}
	}
	

}

void Screen::displayHighScoresWindow()
{
	LOG(__func__);
	system("clear; Pacman ");
	cout<<"High Scores\n"<<endl;
	cout<<"    Name \t\t Time \n";
	FILE *fp;
	char player_name[20];
	float score;
	int dots_eaten;
	fp= fopen("score.txt","r");
	while(!(feof(fp)))
	{
		fscanf(fp,"%s %f %d\n",player_name, &score, &dots_eaten );
		printf("%s\t%f\t%d\n",player_name, score, dots_eaten );
	}
	fclose(fp);
	//cout<<"To be read out of the high score file :D!\n";
	//cout<<" 1  Satvik \t 0 seconds"<<endl;
	cout<<"Press any key to continue...";
	cin.get();
	cin.get();
	cin.get();
}
#endif	/* SCREEN_H */
