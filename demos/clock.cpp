#include "headers.h"
#include<iostream>
using namespace std;
void counter(int a)
{
	static int count = 0;
	system("clear");
	cout<<"Counter = "<<count<<endl;
	++count;
	signal(SIGALRM, counter);
}
int main()
{
	signal(SIGALRM, counter);
	while(1)
	{
		alarm(1);
		sleep(1);
	   //cout<<"Loading ..."<<endl;
	}
}


