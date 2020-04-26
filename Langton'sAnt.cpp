#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAPSIZE 10
int gamemap[MAPSIZE][MAPSIZE];
int antx,anty;
char heading;
void mapinit()
{
	srand(unsigned(time(NULL)));
	antx=rand()%MAPSIZE;
	anty=rand()%MAPSIZE;
	heading=rand()%4;
	for(int i=0;i<MAPSIZE;++i)
		for(int j=0;j<MAPSIZE;++j)
			gamemap[i][j]=rand()%100<20?1:0;
	// black: 0
	// white: 1
	return;
}
void printmap()
{
	for(int y=0;y<MAPSIZE;++y)
	{
		for(int x=0;x<MAPSIZE;++x)
			printf("%c ",gamemap[x][y]? 'O':' ');
		printf("\n");
	}
	return;
}
void simulation()
{
	if(gamemap[antx][anty])
	{
		gamemap[antx][anty]=0;
		heading=(heading+1)%4;
	}
	else
	{
		gamemap[antx][anty]=1;
		heading=(heading+3)%4;
	}
	switch(heading)
	{
		case 0:--antx;break;
		case 1:--anty;break;
		case 2:++antx;break;
		case 3:++anty;break;
	}
	if(antx<0)
		antx=MAPSIZE-1;
	else if(antx>=MAPSIZE)
		antx=0;
	if(anty<0)
		anty=MAPSIZE-1;
	else if(anty>=MAPSIZE)
		anty=0;
	return;
}
void sleep(int n)
{
	for(int i=0;i<n*10000000;)
		++i;
	return;
}
int main()
{
	mapinit();
	while(1)
	{
		simulation();
		printmap();
		sleep(10);
		system("cls");
	}
	return 0;
}
