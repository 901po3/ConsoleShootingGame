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

//stage 1���� ����ϸ� �ɵ�
void SimpleBulletAction();//���Ϸθ��� ���󰡴� �Ѿ� ������ �Լ�
void BulletAction();
///////////////////////////////////////////
void CreateMutipleShot(int Type, int x, int y);
void MutipleShotAction(); //���� ���� ���� 2
void DrawMutipleShot();//�ѹ��� �����̻� ���
////////////////////////////////////
//�ʻ��
void DrawMegaShot();
//////////////////////////////////////
void CreateGuidedShot(int Type, int x, int y);
void DrawGuidedShot();
void GuidedShotAction(int PlayerX, int PlayerY);




