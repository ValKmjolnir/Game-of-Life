#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<cmath>
#include<thread>
#define MapSize 27

bool GameMap[MapSize][MapSize];
bool TempMap[MapSize][MapSize];

bool CheckMapSimilarity()
{
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
			if(TempMap[i][j]!=GameMap[i][j])
				return false;
	return true;
}

bool CheckLivingCell()
{
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
			if(GameMap[i][j])
				return true;
	return false;
}

void SwapMapData()
{
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
			GameMap[i][j]=TempMap[i][j];
	return;
}

void PrintMap()
{
	Sleep(500);
	system("cls");
	for(int i=0;i<MapSize;++i)
	{
		for(int j=0;j<MapSize;++j)
			std::cout<<(GameMap[i][j]? 'O':' ')<<(j==MapSize-1? '|':' ');
		std::cout<<std::endl;
	}
	return;
}

void GameMapRandomInit()
{
	std::srand(unsigned(std::time(NULL)));
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
		{
			if(std::rand()%100<40)
				GameMap[i][j]=true;
			else
				GameMap[i][j]=false;
		}
	return;
}

void GameMapSet()
{
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
			GameMap[i][j]=false;
	char Command='b';
	int PointX=0;
	int PointY=0;
	while(Command!='$')
	{
		system("cls");
		for(int i=0;i<MapSize;++i)
		{
			for(int j=0;j<MapSize;++j)
			{
				if(i==PointY && j==PointX)
					std::cout<<(GameMap[i][j]? '@':'_')<<(j==MapSize-1? '|':' ');
				else
					std::cout<<(GameMap[i][j]? 'O':' ')<<(j==MapSize-1? '|':' ');
			}
			std::cout<<std::endl;
		}
		Command=getch();
		switch(Command)
		{
			case 'w':
				if(PointY!=0)
					--PointY;
				break;
			case 'a':
				if(PointX!=0)
					--PointX;
				break;
			case 's':
				if(PointY<MapSize-1)
					++PointY;
				break;
			case 'd':
				if(PointX<MapSize-1)
					++PointX;
				break;
			case 'y':
				GameMap[PointY][PointX]=true;
				break;
			case 'n':
				GameMap[PointY][PointX]=false;
				break;
		}
	}
	return;
}

void SimulationProcess()
{
	int LivingCellCnt;
	for(int i=0;i<MapSize;++i)
		for(int j=0;j<MapSize;++j)
		{
			LivingCellCnt=0;
			for(int _i=i-1;_i<i+2;++_i)
				for(int _j=j-1;_j<j+2;++_j)
					if(_i>=0 && _i<MapSize && _j>=0 && _j<MapSize && GameMap[_i][_j])
						++LivingCellCnt;
			if(GameMap[i][j])
				--LivingCellCnt;//sub itself
			if(LivingCellCnt==3)
				TempMap[i][j]=true;
			else if(LivingCellCnt==2)
				TempMap[i][j]=GameMap[i][j];
			else
				TempMap[i][j]=false;
		}
	return;
}

int main()
{
	std::cout<<"Choose a initializing method: "<<std::endl;
	std::cout<<"1: Random"<<std::endl;
	std::cout<<"2: By myself"<<std::endl;
	int choice;
	std::cin>>choice;
	system("cls");
	while(true)
	{
		if(choice==1)
			GameMapRandomInit();
		else
			GameMapSet();
		PrintMap();
		while(CheckLivingCell())
		{
			SimulationProcess();
			if(CheckMapSimilarity())
				break;
			SwapMapData();
			PrintMap();
		}
	}
	return 0;
}
