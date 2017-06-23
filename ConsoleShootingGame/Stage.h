#pragma once;

#include"common.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"manager.h"
#include"ScreenOut.h"

#define Stage1			0
#define Stage2			1
#define Stage3			3
#define StageB			2

extern char Screen[HEIGHT][WIDTH];

typedef struct _Select{
	int x, y;
}Select;

int StageOne();
int StageTwo();
int StageThree();
int StageBoss();
void StageToStage(int PlayerX,int PlayerY);
