#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include "tetris.h"

int		curBlock;
int		curDir;
Point	current;
int		baseMap[SIZE_H][SIZE_W];
int		displayMap[SIZE_H][SIZE_W];
int		prevMap[SIZE_H][SIZE_W];


int main()
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	//system("mode con: cols=50 lines=25");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

	Point cur = { 0,0 };
	int dir = 0;
	int key;
	current.row = 0;
	current.column = 4;
	curBlock = 0;
	curDir = 0;
	init();
	copyTodisplayMap();
	drawMap();

	
	while (1)
	{
		cur = current;
		dir = curDir;
		if (checkTimer(1000) == TIME_OVER)
		{
			cur.row += 1;
		}
		else
		{
			key = getKey();
			if (key != 0)
			{
				checkChangeBlock(key, &cur, &dir);
			}
		}
		if (cur.row != current.row || cur.column != current.column || dir != curDir)
		{
			if (changeBlock(cur, dir) == MOVE_ON)
			{
				copyTodisplayMap();
				drawMap();
				if (moveCheck() == MOVE_NOT)
				{
					copyMap(displayMap, baseMap);
					removeLine();
					newBlock();
					//checkFinish();
					copyTodisplayMap();
					drawMap();
				}
			}
			
		}
	}

	return 0;
}