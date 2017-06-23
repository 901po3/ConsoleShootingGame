#pragma once
#include"console.h"
#include<stdio.h>

#define MAX_LINE		16
extern char SideWallShape; //= 'l';

struct WallInfo{
	int x, y;
	int LiveFlag;
};
extern struct WallInfo SideWall[MAX_LINE];

void InitialSideWall();

void WallAction();

void DrawWall();