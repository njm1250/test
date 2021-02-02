#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include "tetris.h"


extern Point	blockPattern[2][4][4];
extern int		curBlock;
extern int		curDir;
extern Point	current;
extern int		baseMap[SIZE_H][SIZE_W];
extern int		displayMap[SIZE_H][SIZE_W];
extern int		prevMap[SIZE_H][SIZE_W];


void checkChangeBlock(int key, Point* cur, int* dir)
{
	*cur = current;
	*dir = curDir;
	switch (key)
	{
	case UP:
		*dir = (curDir + 1) % 4;
		break;
	case DOWN:
		cur->row += 1;
		break;
	case RIGHT:
		cur->column += 1;
		break;
	case LEFT:
		cur->column -= 1;
		break;
	default:
		break;
	}
}


int _changeBlock(Point cur, int dir)
{
	int i, row, col;
	for (i = 0; i < 4; i++)
	{
		row = cur.row + blockPattern[curBlock][curDir][i].row;
		col = cur.column + blockPattern[curBlock][curDir][i].column;
		if (baseMap[row][col] != EMPTY) return MOVE_NOT;
	}
	return MOVE_ON;
}



int changeBlock(Point cur, int dir)
{
	int result;
	result = _changeBlock(cur, dir);
	if (result == MOVE_ON)
	{
		current = cur;
		curDir = dir;
	}
	return MOVE_ON;
}


void newBlock()
{
	srand(time(NULL));
	
	current.row = 1;
	current.column = 5;
	curBlock = rand() % AMOUNT_BLOCK;
	curDir = rand() % 4;
	
}


int moveCheck()
{
	int i, result;
	Point cur;
	int dir;
	checkChangeBlock(DOWN, &cur, &dir);
	result = _changeBlock(cur, dir);
	if (result == MOVE_ON) return MOVE_ON;
	return MOVE_NOT;
}


void downLine(int x)
{
	int row, col;
	for (row = x; row > 1; row--)
	{
		for (col = 1; col < SIZE_W - 1; col++)
		{ 
			baseMap[row][col] = baseMap[row - 1][col];
		}
		
	}
}

void delay(int limit)
{
	while (checkTimer(limit) != TIME_OVER){
		;
	}
}

void removeLine()
{
	int row, col;
	
	for (row = SIZE_H - 2; row > 0; row--)
	{
		for (col = 1; col < SIZE_W - 1; col++)
		{
			if (baseMap[row][col] == EMPTY) break;
		}
		if (col == SIZE_W - 1)
		{
			downLine(row);
			copyTodisplayMap();
			drawMap();
			delay(500);
			row++;
		}
	}
}
