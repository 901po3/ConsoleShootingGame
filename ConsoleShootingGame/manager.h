#pragma once

#include"bullet.h"
#include"enemy.h"
#include"player.h"
#include"sideWall.h"

#define GameSpeed			25
#define BOSS_STAGE		2
// stage 1,2,3 �� ���� ����
void InitialObject1();
void InitialObject2();
void InitialObject3();
void InitialObjectBoss();

// stage 1,2,3 �� ��ǥ�̵� ����
void ActionFuncs1();
void ActionFuncs2();
void ActionFunc3();
void ActionFuncsBoss();

//��ä�� ��ä�� �浹 ����
void CheckCursh();//�Ʒ� �Լ����� ���� �Լ�
void ShotCheckCrush();
void MutipleShotCheckCrush();
void EnemyWallCheckCrush();
void ItemCheckCrush();
void PlayerGuidedShotCheckCrush();
void EnemyGuidedShotCheckCrush();

// �׸��� �˸��� ��ǥ�� ��� �ϱ�
void Draw();//for stage 1,2
void DrawForStageBoss();//for stage 3


//Draw ���ο� ��� �� �Լ�
void EraseScreen();
void PrintScreen();
void EraseGageBar();

//ź ����� ������ �����
void ClearSetting();

//
