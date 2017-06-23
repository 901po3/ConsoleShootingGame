#include"Stage.h"
#include"Item.h"
#include<stdio.h>
extern int CurStage;
//extern int AddPattern;

Select* SelectFunc()
{
	Select s;
	int enter=0;
	s.x = WIDTH/2-7 -3;
	s.y = HEIGHT/2+1;

	MoveCursor(s.x, s.y);
	fputs("☞",stdout);
	while(1)
	{
		if(GetAsyncKeyState(VK_UP) & 0x8000)
		{
			MoveCursor(s.x, HEIGHT/2+1);
			fputs("☞",stdout);
			MoveCursor(s.x, HEIGHT/2+2);
			fputs("  ",stdout);
			s.y =HEIGHT/2+1;
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			MoveCursor(s.x, HEIGHT/2+2);
			fputs("☞",stdout);
			MoveCursor(s.x, HEIGHT/2+1);
			fputs("  ",stdout);
			s.y =HEIGHT/2+2;
		}
		if(GetAsyncKeyState(VK_RETURN) &(0x8000))
			return &s;
	}
}

int WhenLost()
{
	int select = 0;
	MoveCursor(WIDTH/2-7, HEIGHT/2);
	printf("YOU LOST...");
	MoveCursor(WIDTH/2-7, HEIGHT/2+1);
	printf("1) CONTINUE ［5000 Score］");
	MoveCursor(WIDTH/2-7, HEIGHT/2+2);
	printf("2) LEAVE");
	
	Select *s = SelectFunc();
	
	if(s->y==HEIGHT/2+1) //계속하기
	{
		if(Player.Score<5000)
		{
			MoveCursor(WIDTH/2-7, HEIGHT/2+4);
			printf("Not enough score");
			getchar();
			return 0;
		}
		Sleep(500);
		Player.LiveFlag=3;
		Initial();
		if(CurStage == 0)
			InitialObject1();
		else if(CurStage == 1)
			void InitialObject2();
		Player.Score-=5000;
		return 1;
	}
	else if(s->y==HEIGHT/2+2) //나가기
	{
		Sleep(500);
		return 0;
	}
	return 0;
}

int CheckFinish()
{
	int i;
	int num = 0;
	for(i=0; i<ENEMY_MAX; i++)
	{
		if(!Enemy[i].LiveFlag)
			num++;
	}
	return num==ENEMY_MAX ? 1 : 0;
}

void StageToStage(int PlayerX,int PlayerY)
{
	int Count=0;
	int LoopNum= 100;
	EraseGageBar();
	ContinuePlayer(PlayerX, PlayerY);
	InitialSideWall();
	while(Count++!=LoopNum)
	{
		switch(CurStage)
		{
		case Stage1:
			if(Count<LoopNum/2)
				HIGH;
			else
				YELLOW;
			MoveCursor(42, 15);
			printf("To Stage Two");
			break;
		case Stage2://Stage3
			if(Count<LoopNum/2)
				YELLOW;
			else
				BLUE;
			MoveCursor(42, 15);
			printf("To Stage Three");
			break;
		case Stage3: //stageBoss
			if(Count<LoopNum/2)
				BLUE;
			else
				VIO;
			MoveCursor(42, 15);
			printf("To Boss Stage");
			break;
		}
		//좌표설정
		PlayerAction();
		WallAction();
		Sleep(GameSpeed);
		//그리기
		EraseScreen();
		DrawWall();
		DrawPlayer();
		PrintScreen();
	}
	ClearSetting();
	switch(CurStage)
	{
	case Stage1:
		CurStage = Stage2;
		break;
	case Stage2: 
		CurStage = Stage3;
		break;
	case Stage3:
		CurStage = StageB;
		break;
	}
}


int StageOne()
{
	InitialObject1();
	while(1)
	{	
		HIGH;
		SpecialMove();//필살기
		ActionFuncs1();
		CheckCursh();
		ConsumeItemOn();
		Draw();
		ScreenOut();
		if(CheckFinish() || Player.LiveFlag==0)
		{
			EnemyRespawnOnce(Enemy, ENEMY_MAX);
			if(CheckFinish())//이겼을때
			{	
				ClearSetting();
				StageToStage(Player.x,Player.y);
				return 1;
			}
			else if(Player.LiveFlag == 0)
			{
				if(WhenLost())
				{
					ClearSetting();
					InitialObject1();
				}
				else
					return -1;
			}
		}
		Sleep(GameSpeed);
	}
}


int StageTwo()
{
	InitialObject2();
	CreateWallEnemy();
	while(1)
	{
		SpecialMove();//필살기
		YELLOW;
		CheckCursh();
		ConsumeItemOn();
		Draw();
		ScreenOut();
		WallEnemyAction();
		ActionFuncs2();
		if(CheckFinish() || Player.LiveFlag==0)
		{
			if(CheckFinish())//이겼을때
			{
				ClearSetting();
				StageToStage(Player.x,Player.y);
				return 3;
			}
			else if(Player.LiveFlag == 0)
			{
				if(WhenLost())
				{
					ClearSetting();
					InitialObject2();
					CreateWallEnemy();
				}
				else
					return -1;
			}
		}
		Sleep(GameSpeed);
	}
}

int StageThree()
{
	InitialObject3();
	while(1)
	{
		BLUE;
		SpecialMove();//필살기
		ActionFunc3();
		CheckCursh();
		ConsumeItemOn();
		Draw();
		ScreenOut();
		if(CheckFinish()|| Player.LiveFlag==0)
		{
			if(CheckFinish())//이겼을때
			{
				ClearSetting();
				StageToStage(Player.x,Player.y);
				return 2;
			}
			else if(Player.LiveFlag == 0)
			{
				if(WhenLost())
				{
					ClearSetting();
					InitialObject3();
				}
				else
					return -1;
			}
		}
		Sleep(GameSpeed);
	}
	return -1;
}


int StageBoss()
{
	InitialObjectBoss();
	while(1)
	{
		VIO;
		SpecialMove();//필살기
		ActionFuncsBoss();
		ConsumeItemOn();
		CheckCursh();
		DrawForStageBoss();
		ScreenOut();
		if(CheckFinish()|| Player.LiveFlag==0)
		{
			if(CheckFinish())//이겼을때
			{
				ClearSetting();
				MoveCursor(WIDTH/2-15, HEIGHT/2);
				printf("★☆★GAME CLEAR ★☆★");
				MoveCursor(WIDTH/2-15, HEIGHT/2+2);
				printf("Your Score: %d\n", Player.Score);
				getchar();
				CurStage = 10;
				return -1;
			}
			else if(Player.LiveFlag == 0)
			{
				if(WhenLost())
				{
					ClearSetting();
					InitialObjectBoss();
				}
				else
					return -1;
			}	
		}
		Sleep(GameSpeed);
	}

	return -1;
}