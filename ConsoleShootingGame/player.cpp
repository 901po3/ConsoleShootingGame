#include"player.h"
#include"Item.h"
#include<stdio.h>

extern char Screen[HEIGHT][WIDTH];
extern int CurStage;

void InitialPlayer()
{
	Player.x = 50;
	Player.y = 30;
	Player.LiveFlag = 1;
	Player.HP = 5;
	Player.MaxHP = 5;
	Player.ItemOn = 0;
	Player.ItemShotNum = 0;
	Player.WaveShotNum = 0;
	Player.MegaShot = 0;
	Player.Gage = 0;
}

void ContinuePlayer(int PlayerX, int PlayerY)
{
	Player.x = PlayerX;
	Player.y = PlayerY;
	Player.LiveFlag = 1;
	Player.HP = 5;
	Player.MaxHP = 5;
	Player.ItemOn = 0;
	Player.ItemShotNum = 0;
	Player.WaveShotNum = 0;
	Player.MegaShot = 0;
	Player.Gage = 0;
}

void DrawPlayer()
{
	int i;
	if(!Player.LiveFlag) return;

	int x = Player.x - PLAYER_SIZE / 2;
	int y = Player.y;
		
	if(y<0 || y>HEIGHT-4) return;
	   
	for(i=0; i<PLAYER_SIZE; i++)
	{
		if(x>1 && x<WIDTH-1)
		{
			Screen[y][x] = PlayerUnit[i];
			x++;
		}
	}
}

void PlayerAction()
{
	if(Player.LiveFlag == 0) return;

	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if(Player.y < 2) return;
		Player.y--;
	}
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if(Player.y >= HEIGHT-4)  Player.y = HEIGHT-5;
		Player.y++;
	}
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if(Player.x > (WIDTH - PLAYER_SIZE-1)-3) return;
		Player.x+=2;
	}
	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if(Player.x < (1+PLAYER_SIZE/2)+1+2) return;
		Player.x-=2;
	}

	//플레이어가 쏜 총알 Z키 누르면 함수에 정보 전달
	if(GetAsyncKeyState('Z') & 0x8000)
	{
		switch(Player.ItemOn)
		{
		case NORMAL_SHOT_ITEM_ON:
			CreateBullet(PLAYER_SHOT, Player.x, Player.y);
			break;
		case TWO_SHOT_ITEM_ON:
			GunItemAction(Player.x, Player.y);
			CreateBullet(PLAYER_SHOT, Player.x-PLAYER_SIZE/2, Player.y-2);
			CreateBullet(PLAYER_SHOT, Player.x+PLAYER_SIZE/2, Player.y-2);
			Player.ItemShotNum--;
			break;
		case WAVE_SHOT_ITEM_ON:
			GunItemAction(Player.x, Player.y);
			CreateMutipleShot(PLAYER_SHOT, Player.x, Player.y);
			Player.WaveShotNum--;
			break;
		}
	}
	if(GetAsyncKeyState('X') & 0x8000)
	{
		if(Player.MegaShot)
		{
			for(int i=0; i<10; i+=2)
			{
				for(int j=0; j<16; j++)
				{
					if(Player.ItemOn ==NORMAL_SHOT_ITEM_ON)
						CreateBullet(PLAYER_SHOT, Player.x-8+j, Player.y-i);
					else if(Player.ItemOn ==TWO_SHOT_ITEM_ON)
						CreateBullet(PLAYER_SHOT, Player.x-16+(j*2), Player.y-(i*2));
					else if(Player.ItemOn ==WAVE_SHOT_ITEM_ON)
						CreateMutipleShot(PLAYER_SHOT, Player.x-16+(j*2), Player.y-i);
				}
			}
		}
		if(Player.Gage == 100){
			Player.Gage = 0;
		Player.MegaShot = 0;
		}
	}

}

void SpecialMove()
{
	if(Player.Gage <MAX_GAGE)
		Player.Gage++;
	if(Player.Gage == MAX_GAGE)
	{
		MegaItem.UseFlag =1;
		MegaItem.Type =MEGA_GUN;
		Player.MegaShot =1;
	}
}

