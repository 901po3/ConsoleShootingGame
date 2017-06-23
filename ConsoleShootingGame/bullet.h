#pragma once

#include"console.h"
#include"player.h"

#define PLAYER_SHOT			0
#define ENEMY_SHOT			1
#define MAX_BULLET			400

struct ShotInfo{
	int x, y;
	int Type;
	int UseFlag;
};
extern struct ShotInfo Shot[MAX_BULLET];
extern struct ShotInfo MultipleShot[MAX_BULLET];
extern struct ShotInfo GuidedShot[MAX_BULLET];

extern char PlayerShot;
extern char PlayerItemShot; 
extern char PlayerMegaShot;
extern char EnemyShot;
extern char EnemyMutipleShotShape;
extern char PlayerMutipleShotShape;
extern char GuidedBullet;

void CreateBullet(int Type, int x, int y);

void DrawBullet();

//stage 1에서 사용하면 될듯
void SimpleBulletAction();//상하로만로 날라가는 총알 정의한 함수
void BulletAction();
///////////////////////////////////////////
void CreateMutipleShot(int Type, int x, int y);
void MutipleShotAction(); //보스 공격 패턴 2
void DrawMutipleShot();//한번에 세번이상 쏘기
////////////////////////////////////
//필살기
void DrawMegaShot();
//////////////////////////////////////
void CreateGuidedShot(int Type, int x, int y);
void DrawGuidedShot();
void GuidedShotAction(int PlayerX, int PlayerY);




