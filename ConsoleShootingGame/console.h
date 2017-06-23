#pragma once
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include<Windows.h>

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute( col,0x000c ) //������ 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008) //�Ķ��� 
#define HIGH SetConsoleTextAttribute( col,0x00a) // ����
#define WHITE SetConsoleTextAttribute( col,0x000f) // ���
#define SKY SetConsoleTextAttribute( col, 0x000b) //�ϴû�
#define YELLOW SetConsoleTextAttribute( col, 0x000e) //�����
#define HIG SetConsoleTextAttribute( col, 0x000d) //����
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c) //����

#define WIDTH			101
#define HEIGHT		34

void Initial();
void MoveCursor(int x, int y);
void ClearScreen();



#endif