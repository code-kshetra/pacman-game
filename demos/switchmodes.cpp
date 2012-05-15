#include "headers.h"
#include<iostream>
using namespace std;

void comeout(int a)
{
	system("stty -raw echo");
	cout<<"Recieved the signal ending :P"<<endl;
	system("banner Good Bye!");
	cout<<"The program will exit now!"<<endl;
	exit(0);


}
int main()
{
	system("clear;banner hello, world!");
	//char command[32] = {'\0'};
	char ch;
	int n;
	// Put the screen to raw mode 
	system("stty raw -echo isig");
	signal(SIGINT, comeout);
	while((n = read(STDIN_FILENO, &ch, sizeof(char)))>0)
	{
		//command[n] = '\0';
		//cout<<"Recieved the command : "<<command<<endl;
		//system(command);
		printf(" %c %d \n",ch, ch);
	}
}

