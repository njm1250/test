#ifndef _TETRIS_H
#define _TETRIS_H

#define LEFT			75 
#define RIGHT			77  
#define UP				72 
#define DOWN			80 

#define AMOUNT_BLOCK	3
#define EMPTY			20
#define WALL			21
#define BLOCK			0
#define BLOCK_2			1
#define BLOCK_3			2
#define BLOCK_4         3
#define BLOCK_5         4
#define BLOCK_6         5

#define SIZE_W			10
#define SIZE_H			20

#define TIME_NOT		0
#define TIME_OVER		1
#define MOVE_NOT		0
#define MOVE_ON			1

typedef struct _Point
{
	int row;
	int column;
} Point;

void	gotoxy(int x, int y);
void	drawMap();
int		getKey();
void	init();
int		checkTimer();
int		copyMap();
void	copyTodisplayMap();
void	checkChangeBlock(int key, Point* cur, int* dir);
int		changeBlock(Point cur, int dir);
void	newBlock();
int		moveCheck();
void    checkLine();
void	removeLine();
void	downLine(int x);



#endif
