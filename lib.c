#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include "tetris.h"



extern Point	 blockPattern[2][4][4];
extern int		 curBlock;
extern int		 curDir;
extern Point	 current;
extern int		 baseMap[SIZE_H][SIZE_W];
extern int		 displayMap[SIZE_H][SIZE_W];
extern int		 prevMap[SIZE_H][SIZE_W];





void init()
{
	int i, k;
	for (i = 0; i < SIZE_H; i++)
	{
		for (k = 0; k < SIZE_W; k++)
		{
			baseMap[i][k] = EMPTY;
			displayMap[i][k] = EMPTY;
			prevMap[i][k] = 0xFF;
		}
	}
	for (k = 0; k < SIZE_W; k++)
	{
		baseMap[0][k] = WALL;
		baseMap[SIZE_H - 1][k] = WALL;
	}
	for (i = 1; i < SIZE_H - 1; i++)
	{
		baseMap[i][0] = WALL;
		baseMap[i][SIZE_W - 1] = WALL;
	}
}

void copyTodisplayMap()
{
	int i, row, col;
	copyMap(baseMap, displayMap);

	for (i = 0; i < 4; i++)
	{
		row = current.row + blockPattern[curBlock][curDir][i].row;
		col = current.column + blockPattern[curBlock][curDir][i].column;
		displayMap[row][col] = curBlock;
	}
}


void drawMap()
{
	int i, k;
	for (i = 0; i < SIZE_H; i++)
	{
		for (k = 0; k < SIZE_W; k++)
		{
			if (displayMap[i][k] != prevMap[i][k])
			{
				gotoxy(k * 2, i);
				switch (displayMap[i][k])
				{
				case EMPTY:
					printf("  ");
					break;
				case WALL:
					printf("бр");
					break;
				case BLOCK:
					printf("бс");
					break;
				case BLOCK_2:
					printf("бс");
					break;
				case BLOCK_3:
					printf("бс");
				default:
					break;
				}
			}
		}
	}
}

int getKey()
{
	int key = 0;
	if (kbhit())
	{
		key = getch();
		if (key == 224)
		{
			key = getch();
		}
	}
	return key;
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	COORD c = { x, y };
	if (!h) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleCursorPosition(h, c);
}

int checkTimer(int cTime)
{
	static unsigned long oldTime = 0;
	unsigned long newTime;
	newTime = GetTickCount64();
	if ((newTime - oldTime) > cTime)
	{
		oldTime = newTime;
		return TIME_OVER;
	}
	else
	{
		return TIME_NOT;
	}
}


int copyMap(int(*source)[SIZE_W], int(*target)[SIZE_W])
{
	int i, k;
	for (i = 0; i < SIZE_H; i++)
	{
		for (k = 0; k < SIZE_W; k++)
		{
			target[i][k] = source[i][k];
		}
	}
	return 0;
}

