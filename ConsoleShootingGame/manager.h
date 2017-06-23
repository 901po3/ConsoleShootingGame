#pragma once

#include"bullet.h"
#include"enemy.h"
#include"player.h"
#include"sideWall.h"

#define GameSpeed			25
#define BOSS_STAGE		2
// stage 1,2,3 별 시작 설정
void InitialObject1();
void InitialObject2();
void InitialObject3();
void InitialObjectBoss();

// stage 1,2,3 별 좌표이동 설정
void ActionFuncs1();
void ActionFuncs2();
void ActionFunc3();
void ActionFuncsBoss();

//개채와 개채의 충돌 관리
void CheckCursh();//아래 함수들을 담을 함수
void ShotCheckCrush();
void MutipleShotCheckCrush();
void EnemyWallCheckCrush();
void ItemCheckCrush();
void PlayerGuidedShotCheckCrush();
void EnemyGuidedShotCheckCrush();

// 그림을 알맞은 좌표에 출력 하기
void Draw();//for stage 1,2
void DrawForStageBoss();//for stage 3


//Draw 내부에 사용 될 함수
void EraseScreen();
void PrintScreen();
void EraseGageBar();

//탄 지우기 아이탬 지우기
void ClearSetting();

//
