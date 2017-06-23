#include<Windows.h>
#include<stdio.h>
#include"console.h"

HANDLE hConsole;

void Initial()
{
	CONSOLE_CURSOR_INFO Cursor;

	Cursor.bVisible = FALSE;//커서 끄는 기능일듯
	Cursor.dwSize = 1;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &Cursor);
}

void MoveCursor(int x, int y)
{
	COORD Coord;
	Coord.X = x;
	Coord.Y = y;

	SetConsoleCursorPosition(hConsole, Coord);
}

void ClearScreen()
{
	int i, j;
	for(i=0; i< HEIGHT;  i++)
	{
		MoveCursor(0,i);
		for(j=0; j< WIDTH; j++)
		{
			printf("%c",' ');	
		}
	}
}