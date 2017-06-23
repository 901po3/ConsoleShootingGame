#include"bullet.h"
#include"Item.h"
#include<stdio.h>
#include"Stage.h"

extern char Screen[HEIGHT][WIDTH];
extern int CurStage;

void CreateBullet(int Type, int x, int y)
{
	int i;
	for(i=0; i<MAX_BULLET; i++)
	{ 
		if(Shot[i].UseFlag == 0)
		{
			Shot[i].UseFlag = 1;
			Shot[i].Type = Type;
			Shot[i].x = x;
			Shot[i].y = y;
			return;
		}
	}
}
void CreateMutipleShot(int Type, int x, int y)
{
	int i;
	for(i=0; i<MAX_BULLET; i++)
	{ 
		if(MultipleShot[i].UseFlag == 0)
		{
			MultipleShot[i].UseFlag = 1;
			MultipleShot[i].Type = Type;
			MultipleShot[i].x = x;
			MultipleShot[i].y = y;
			return;
		}
	}
}

void CreateGuidedShot(int Type, int x, int y)
{
	int i;
	for(i=0; i<MAX_BULLET; i++)
	{ 
		if(GuidedShot[i].UseFlag == 0)
		{
			GuidedShot[i].UseFlag = 1;
			GuidedShot[i].Type = Type;
			GuidedShot[i].x = x;
			GuidedShot[i].y = y-2;
			return;
		}
	}
}

void DrawBullet()
{
	int i;
	int x, y;
	
	for(i=0; i<MAX_BULLET; i++)
	{
		if(!Shot[i].UseFlag) continue;
		if(Shot[i].y<0 || Shot[i].y>HEIGHT-3) continue;
		if(Shot[i].x<3 || Shot[i].x>WIDTH-3) continue;

		x = Shot[i].x;
		y = Shot[i].y;
		switch(Shot[i].Type) //1이면 enemy
		{
		case ENEMY_SHOT:
			Screen[y][x] = EnemyShot;
			break;
		case PLAYER_SHOT:
			switch(Player.ItemOn)
			{
			case NORMAL_SHOT_ITEM_ON:
				Screen[y][x] = PlayerShot;
				break;
			case TWO_SHOT_ITEM_ON:
				Screen[y][x] = PlayerItemShot;
				break;
			}
			break;
		}
	}
}


void DrawMutipleShot()
{

	int i;
	int x, y;

	for(i=0; i<MAX_BULLET; i++)
	{
		if(!MultipleShot[i].UseFlag) continue;
		if(MultipleShot[i].y<0 || MultipleShot[i].y>HEIGHT-3) continue;
		if(MultipleShot[i].x<3 || MultipleShot[i].x>WIDTH-3) continue;

		x = MultipleShot[i].x;
		y = MultipleShot[i].y;
		switch(MultipleShot[i].Type)
		{
		case ENEMY_SHOT:
			Screen[y][x] = EnemyMutipleShotShape;
			break;
		case PLAYER_SHOT:
			Screen[y][x] = PlayerMutipleShotShape;
			break;
		}
	}
}

void DrawGuidedShot()
{

	int i;
	int x, y;

	for(i=0; i<MAX_BULLET; i++)
	{
		if(!GuidedShot[i].UseFlag) continue;
		if(GuidedShot[i].y<0 || GuidedShot[i].y>HEIGHT-3) continue;
		if(GuidedShot[i].x<3 || GuidedShot[i].x>WIDTH-3) continue;

		x = GuidedShot[i].x;
		y = GuidedShot[i].y;
		switch(MultipleShot[i].Type)
		{
		case ENEMY_SHOT:
			Screen[y][x] = GuidedBullet;
			break;
		case PLAYER_SHOT:
			Screen[y][x] = GuidedBullet;
			break;
		}
	}
}

void MutipleShotAction()
{
	int i;
	static int count =1;
	for(i=0; i<MAX_BULLET; i++)
	{
		if(MultipleShot[i].UseFlag == 0) continue;

		if(!MultipleShot[i].Type && MultipleShot[i].y>0
			&& MultipleShot[i].y < HEIGHT) //플레이어
		{
			if(MultipleShot[i].y<2)
				MultipleShot[i].UseFlag = 0;
			else
			{
				MultipleShot[i].y--;
				//웨이브 샷
				switch(rand()%10)
				{
				case 0:
					MultipleShot[i].x++;
					break;
				case 1:
					MultipleShot[i].x--;
					break;
				case 2:
					MultipleShot[i].x+=2;
					break;
				case 3:
					MultipleShot[i].x-=2;
					break;
				case 4:
					MultipleShot[i].x+=3;
					break;
				case 5:
					MultipleShot[i].x-=3;
				}
			}
		}
		else if(MultipleShot[i].Type && MultipleShot[i].y>=0
			&& MultipleShot[i].y < HEIGHT-1) //적
		{
			if(MultipleShot[i].y>HEIGHT-4)
				MultipleShot[i].UseFlag = 0;
			else
			{
				//멀티플샷 
				MultipleShot[i].y++;
				for(int j=0; j<400; j+=2)
				{
					count++;
					if(count%2==0)
						MultipleShot[i%(2+j)].x++;
					if(count%2==1)
						MultipleShot[i%(3+j)].x--;
				}
			}
		}
	}
}

void GuidedShotAction(int PlayerX, int PlayerY)
{
	int i;
	static int count =1;
	for(i=0; i<MAX_BULLET; i++)
	{
		if(GuidedShot[i].UseFlag == 0) continue;

		if(!GuidedShot[i].Type && GuidedShot[i].y>0
			&& GuidedShot[i].y < HEIGHT) //플레이어
		{
			if(GuidedShot[i].y<2)
				GuidedShot[i].UseFlag = 0;
			else
			{

			}
		}
		else if(GuidedShot[i].Type && GuidedShot[i].y>=0
			&& GuidedShot[i].y < HEIGHT-1) //적
		{
			if(GuidedShot[i].y>HEIGHT-4)
				GuidedShot[i].UseFlag = 0;
			else
			{	//유도탄
				if(GuidedShot[i].x< PlayerX)
					GuidedShot[i].x++;
				if(GuidedShot[i].x> PlayerX)
					GuidedShot[i].x--;
				/*if(GuidedShot[i].y >PlayerY)
					GuidedShot[i].y--;*/
				GuidedShot[i].y++;
			}
		}
	}
}


void SimpleBulletAction()//상하전용
{
	int i;
	
	for(i=0; i<MAX_BULLET; i++)
	{
		if(Shot[i].UseFlag == 0) continue;

		if(!Shot[i].Type && Shot[i].y>0 && Shot[i].y < HEIGHT) //플레이어
		{
			if(Shot[i].y<2)
				Shot[i].UseFlag = 0;
			else
				Shot[i].y--;
		}
		else if(Shot[i].Type && Shot[i].y>=0 && Shot[i].y < HEIGHT-1) //적
		{
			if(Shot[i].y>HEIGHT-4)
				Shot[i].UseFlag = 0;
			else
				Shot[i].y++;
		}
	}
}
