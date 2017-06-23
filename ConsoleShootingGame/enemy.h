#pragma once

#include"bullet.h"
#include"common.h"

//개체마다 알맞은 크기의 변수생성및 그림 초기화 하기;
#define ENEMY_SIZE			3
#define BOSS_SIZE				15
#define ENEMY_MAX				80
#define WALL_SIZE				17
#define BOSS_WIDTH			30
#define BOSS_HEIGHT			5
#define ENEMY_NUM_STAGE_TWO	50
#define Enemy_NUM_STAGE_THREE	10
#define BOSS_MAX_HP			800

extern char EnemyUnit[ENEMY_SIZE+1];
extern char EnemyUnit2[ENEMY_SIZE+1];
extern char EnemyUnit3[ENEMY_SIZE+1];
extern char WallEnemyShape[WALL_SIZE+1];
//보스 텍스쳐 크기 가로 15+(NULL값 1) 세로 5칸
extern char Boss[BOSS_HEIGHT][BOSS_WIDTH+1];
extern char BrokenBoss[BOSS_HEIGHT][BOSS_WIDTH+1];

struct EnemyInfo{
	int x, y;
	int LiveFlag;
	int MoveFlagX;
	int MoveFlagY;
	int StartX;
	int StartY;
	int HP;
};
extern struct EnemyInfo Enemy[ENEMY_MAX];  
extern struct EnemyInfo WallEnemy;

void InitialEnemyForAction1();//규칙적인 적 움직임
void InitialEnemyForAction2();
void InitialEnemyForAction3();
void CreateWallEnemy();
void EnemyAction1();
void EnemyAction2();
void EnemyAction3();
void WallEnemyAction();
void DrawEnemy();
void DrawWallEnemy();

void InitialBossAction();
void DrawBoss();

void BossAction();

void EnemyRespawnOnce(EnemyInfo *Enemy, int EnemyNum);