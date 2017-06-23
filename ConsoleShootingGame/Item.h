#pragma once
#include"enemy.h"

#define NORMAL_SHOT		0
#define GUN_ITEM			1
#define HP_ITEM			2
#define MEGA_GUN			3
#define WAVE_SHOT			4
#define GUIDED_SHOT		5

#define GUNE_SHAPE_SIZE	10
extern char ItemShotShape; 
extern char ItemHPShape;
extern char MegaShotShape;
extern char GunItemShape[GUNE_SHAPE_SIZE+1];
extern char WaveItemShape[GUNE_SHAPE_SIZE+1];
extern char WaveShot;

struct item{
	int x, y;
	int Type;
	int UseFlag;
};
extern struct item Item;
extern struct item MegaItem;
extern struct item MakeShape[GUNE_SHAPE_SIZE+1];
extern struct item MakeShape2[GUNE_SHAPE_SIZE+1];

void ItemAction();

void DrawItem();

void CreateItem( int Type, int x, int y);
void ConsumeItemOn();//총알 아이탬 다 쓰면 일반 총으로

void GunItemAction(int x, int y);
void DrawGunItemShape();

		  // 아이탬 확율   드랍하는 적기 종류    적기 번호	
void DropItem(int Percentage, EnemyInfo *Enemy, int loopNum);
