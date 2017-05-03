#include<process.h>
#include<string.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
/*BUGS
some problem in the login with the wrong password point
*/
int a[15][15],temp[15][15],hiscore=0,logflag=0;
/* a is the main array and board.
   temp is a temporary array, explained in nextit()
   hiscore is the highest score achieved during the entire simulation run */
class user
{
	char name[20];
	char pwd[20];
	int score;
	public:
	user()
	{
		strcpy(name,"\0");
		strcpy(pwd,"\0");
	}
	void input()
	{
		cout<<"\nEnter Username::";
		cin>>name;
		cout<<"\nEnter Password::";
		cin>>pwd;
	}
	void reenter()
	{
		cin>>pwd;
	}
	int check( user u )
	{
		if(strcmp(name,u.name)!=0)
			return 0;
		else
			{
			if (strcmp(pwd,u.pwd)!=0)
				return 1;
			else
				return 2;
			}
	}
	void scorein(int s)
		{
		score=s;
		}
	int scoreout()
		{
		return score;
		}
	void show()
		{
		cout<<name<<"\t"<<score;
		}
}player;
// Class user stores name, password and hiscore for a game.
void nextit();
void sim();
void disp()     				//This is the main display function.
{
	int i,j;
	cout<<"\n Legend\n___________\n 0 ------> Dead cell\n X ------> Live cell\n";
	cout<<"\n\n     | a | b | c | d | e | f | g | h | i | j | k | l |";
						//Shows the row and column indications to make it easier for user.
	cout<<"\n\n";
	for(i=1;i<11;++i)
	{
		cout<<'\n';
		cout<<char(i+96)<<"|   ";	//Input (character) converted to corresponding integer.
		for(j=1;j<13;++j)
		{
			if (a[i][j]==0)
				cout<<" 0 |";	// value 0 represents a dead cell
			else if(a[i][j]==1)
				cout<<" X |" ;	// value 1 represents a live cell
			else			// In case something goes wrong.
				cout<<"Error";
		}

	}

}
void init()					//This is the initialization function. Called once before the starting of the simulation.
{
	int i,j;
	for(i=0;i<15;++i)
		for(j=0;j<15;++j)
			a[i][j]=0;
}
void input()					//This function takes the initial values from the user.
{
	int ar1,ar2;
	A:					//Accepts values till it encounters an illegal value.
	cout<<"\n\nEnter block to change : ( Format : Row , Column ) \n ";
	cout<<"********Enter any illegal value to go to simulation*********\n\n";
	cout<<"Input : ";
	ar1=int(getche())-96;			//To convert the input to corresponding integer.
	ar2=int(getche())-96;
	if (ar1>10||ar2>12||ar1<0||ar2<0)	//If illegal value encountered, begin execution.
	{
		clrscr();
		cout<<"Going to Simulation.....";
		delay(1000);
		sim();				//Start Simulation.
		return;
	}
	clrscr();
	a[ar1][ar2]=1;
	disp();
	goto A;
}
void copy(int x[15][15],int y[15][15])		//Copy function for two arrays.
{
	int i,j;
	for(i=0;i<15;++i)
	{
		for(j=0;j<15;++j)
		{
			y[i][j]=x[i][j];
		}
	}
}
int neigh(int c,int d)				//Counts the number of neighbours.
{
	int m,n;
	int z=0;
	for(n=d-1;n<d+2;n++)
		z=z+a[c-1][n];
	for(n=d-1;n<d+2;n++)
		z=z+a[c+1][n];
	z=z+a[c][d-1]+a[c][d+1];
	return z;
}
void nextit()                                   //To execute NEXT ITeration.
{
	int i,j;
	copy(a,temp);
	/* A temporary array is used instead of the original one as
	   the number of neighbours should be counted for the whole
	   board at the same time and then only should the cells be
	   changed. If the same array is used, we go row-by-row
	   and the incorrect result is obtained.
	*/
	int n;
	for(i=1;i<11;++i)
	{
		for(j=1;j<13;++j)
		{
			n=neigh(i,j);
			if(n>3)
				temp[i][j]=0;	//Manipulation is done on temporary array.
			else if(n<2)
				temp[i][j]=0;
			else if(n==3)
				temp[i][j]=1;
		}
	}
	copy(temp,a);				//Temporary array copied to main array.
}
int checkscore()				//Checks score at end of each turn
{      /* Score is the total number of
	  live cells at any iteration.
	  hiscore is the maximum score obatined.
	  The score for the first input is not counted.*/
	hiscore;
	int score=0,i,j;
	for(i=1;i<11;++i)
		for(j=1;j<13;++j)
			score+=a[i][j];
	if(score>hiscore)
		hiscore=score;
	return score;
}
void sim()					//Main simulation function.
{
	int k,s;
	for(k=0;k<100;++k)
	{
		nextit();
		clrscr();
		disp();
		delay(400);
		s=checkscore();
		if(s==0)			//If the board is empty, then exit.
			break;
	}
	clrscr();
	cout<<"Hiscore="<<hiscore;
	player.scorein(hiscore);
}
void about()
{
clrscr();
cout<<"\t\tABOUT";
cout<<"\n\t=====================";
cout<<"\n\nThe Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.";
cout<<"\nThe \'game\' is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves or, for advanced players, by creating patterns with particular properties.";
cout<<"\n\n\tRULES\n======================";
cout<<"\nThe universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead. Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur: ";
cout<<"\n1.Any live cell with fewer than two live neighbours dies, as if caused by under-population.";
cout<<"\n2.Any live cell with two or three live neighbours lives on to the next generation.";
cout<<"\n3.Any live cell with more than three live neighbours dies, as if by overcrowding.";
cout<<"\n4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.";
}
void leader()
{
 //leaderboard goes here
}
void reg()
{
	clrscr();
	cout<<"\t\tREGISTER\n";
	cout<<"=========================";
	user u,v;
	u.input();
	ifstream fin("Users.dat",ios::binary);
	while(fin.read((char*)&v,sizeof(v)))
		{
		if(u.check(v)!=0)
			{
			cout<<"\nUsername already taken..sorry";
			fin.close();
			return;
			}
		}
	fin.close();
	ofstream fout("Users.dat",ios::binary|ios::ate);
	fout.write((char*)&u,sizeof(u));
	fout.close();
	cout<<"\n\nRegistered Successfully!!!";
}
void login()
{
	if(logflag==1)
		{
		cout<<"You are already logged in ....\n";
		cout<<"Please exit the program to login with different user name.";
		}
	int i;
	clrscr();
	cout<<"\t\tLOGIN";
	cout<<"\n\t======================\n";
	user u,v;
	ifstream fin("Users.dat",ios::binary);
	if(!fin)
	{
		cout<<"\nNo login file found!!\n";
		cout<<"Please register !!";
		return;
	}
	u.input();
	while(fin.read((char*)&v,sizeof(v)))
	{
		if(u.check(v)==1)
			{
			cout<<"\nPassword incorrect.\nPlease reenter password!";
			for(i=0;i<3;++i)
				{
				u.reenter();
				if(u.check(v)==2)
					{
						cout<"\nLogin Sucess!!";
						delay(400);
						player=v;
						logflag=1;
						fin.close();
						return;
					}
				}
			cout<<"\nSorry, try again..";
			getch();
			fin.close();
			return;
			}

		else if(u.check(v)==2)
			{
			cout<"\nLogin Sucess!!";
			delay(400);
			player=v;
			logflag=1;
			fin.close();
			return;
			}

	}
	cout<<"\nSorry, user not found. Please register !";
	fin.close();
}
void main()
{
	int ch;
	while(1)			//Menu
	{
		clrscr();
		cout<<"\t\tWelcome To CONWAY'S GAME OF LIFE";
		cout<<"\n\n\t\t\tMENU";
		cout<<"\n\t\t=====================";
		cout<<"\n\n1. About";
		cout<<"\n2. Register";
		cout<<"\n3. Login";
		cout<<"\n4. Leaderboards";
		cout<<"\n5. Start Simulation";
		cout<<"\n6. Exit";
		cout<<"\n\n\n\t Enter your choice :: ";
		cin>>ch;
		switch(ch)
		{
			case 1 :	about();
					break;
			case 2 :	reg();
					break;
			case 3 :	login();
					break;
			case 4 :	leader();
					break;
			case 5 :        if(logflag==0)
						{
						cout<<"Please login....\n";
						break;

						}

					init();
					disp();
					input();
					cout<<"\nSimulation completed.... ";
					break;
			case 6 :	clrscr();
					cout<<"Thank You!";
					cout<<"\nExiting....";
					delay(500);
					exit(0);
			default:	cout<<"Please enter valid choice..";
					delay(200);

		}
		getch();
	}
}
