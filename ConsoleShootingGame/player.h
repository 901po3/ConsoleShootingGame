#pragma once

#include"console.h"
#include"bullet.h"
#include<Windows.h>

#define PLAYER_SIZE					5
#define MAX_GAGE						100
#define NORMAL_SHOT_ITEM_ON			0
#define TWO_SHOT_ITEM_ON				1
#define WAVE_SHOT_ITEM_ON				2
#define GUIDED_SHOT_ITEM_ON			3

extern char PlayerUnit[PLAYER_SIZE+1];

struct PlayerInfo{
	int x, y;
	int LiveFlag;
	int HP;
	int MaxHP;
	int ItemOn;
	int ItemShotNum;
	int MegaShot;
	int Gage;
	int WaveShotNum;
	int Score;
};
extern struct PlayerInfo Player;

void InitialPlayer();
void ContinuePlayer(int PlayerX, int PlayerY);
void DrawPlayer();
void PlayerAction();
void SpecialMove();