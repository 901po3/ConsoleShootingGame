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
void ConsumeItemOn();//�Ѿ� ������ �� ���� �Ϲ� ������

void GunItemAction(int x, int y);
void DrawGunItemShape();

		  // ������ Ȯ��   ����ϴ� ���� ����    ���� ��ȣ	
void DropItem(int Percentage, EnemyInfo *Enemy, int loopNum);
