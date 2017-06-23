#pragma once
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include<Windows.h>

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute( col,0x000c ) //»¡°£»ö 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008) //ÆÄ¶õ»ö 
#define HIGH SetConsoleTextAttribute( col,0x00a) // ¿¬µÎ
#define WHITE SetConsoleTextAttribute( col,0x000f) // Èò»ö
#define SKY SetConsoleTextAttribute( col, 0x000b) //ÇÏ´Ã»ö
#define YELLOW SetConsoleTextAttribute( col, 0x000e) //³ë¶õ»ö
#define HIG SetConsoleTextAttribute( col, 0x000d) //Çü±¤
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c) //º¸¶ó

#define WIDTH			101
#define HEIGHT		34

void Initial();
void MoveCursor(int x, int y);
void ClearScreen();



#endif