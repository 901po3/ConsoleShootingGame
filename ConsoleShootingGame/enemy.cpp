#include"enemy.h"
#include"Stage.h"

extern char Screen[HEIGHT][WIDTH];
extern int CurStage;
char CopyShape[25];

void InitialEnemyForAction1()
{
	int i;
	int x = 17;
	int y = -8;
	for(i=0; i<ENEMY_MAX; i++)
	{
		//x, y값을 주고
		Enemy[i].x = x;
		Enemy[i].y = y;
		Enemy[i].LiveFlag = 1;
		Enemy[i].MoveFlagY = 1;
		Enemy[i].StartX = x;
		Enemy[i].StartY = y;
		Enemy[i].HP = 2;
		if(i % 10 < 5)
			Enemy[i].MoveFlagX = 0;
		else
			Enemy[i].MoveFlagX = 1;

		//x값에 변경을 주고
		x += (ENEMY_SIZE +2);
		////3+2//최소 4이상을 해야 각 적마다 공간이 벌어짐

		if(i % 10 == 4)
			x += (ENEMY_SIZE +14);
		
		//y값에 변경 주고
		if(i % 10 == 9)//어떤 숫자를 10으로 나눌때 나머지가 9이면
		{
			x = 17;
			y++;
		}//for문 반복
	}
	strcpy(CopyShape, EnemyUnit);
	
}

void InitialEnemyForAction2()
{
	int i;
	int x = 9;
	int y = -8;
	for(i=0; i<ENEMY_NUM_STAGE_TWO; i++)
	{
		Enemy[i].x = x;
		Enemy[i].y = y;
		Enemy[i].LiveFlag = 1;
		Enemy[i].MoveFlagY = 1;
		Enemy[i].StartX = x;
		Enemy[i].StartY = y;
		Enemy[i].HP = 4;
		Enemy[i].MoveFlagX = 1;

		//x값에 변경을 주고
		x += (ENEMY_SIZE +3);
		////3+2//최소 4이상을 해야 각 적마다 공간이 벌어짐
		if(i % 10 == 4)
			x += (ENEMY_SIZE +24);
		//y값에 변경 주고
		if(i % 10 == 9)//어떤 숫자를 10으로 나눌때 나머지가 9이면
		{
			x = 9;
			y+=2;
		}//for문 반복
	}
	strcpy(CopyShape, EnemyUnit2);
}

void InitialEnemyForAction3()
{
	int i;
	int x = 6;
	int y = -10;
	for(i=0; i<Enemy_NUM_STAGE_THREE; i++)
	{
		Enemy[i].x = x;
		Enemy[i].y = y;
		Enemy[i].LiveFlag = 1;
		Enemy[i].MoveFlagY = 1;
		Enemy[i].StartX = x;
		Enemy[i].StartY = y;
		Enemy[i].HP = 8;
		Enemy[i].MoveFlagX = 1;

		x += (ENEMY_SIZE+ 18);

		if(i%10 == 4)
		{
			x = 6;
			y+=5;
		}
	}
	strcpy(CopyShape, EnemyUnit3);
}

void CreateWallEnemy()
{
	WallEnemy.HP = 60;
	WallEnemy.LiveFlag =1;
	WallEnemy.x = WIDTH-WALL_SIZE-42;
	WallEnemy.y = 0;
	WallEnemy.StartY =WallEnemy.y;
	WallEnemy.StartX =WallEnemy.x;
	WallEnemy.MoveFlagX = 1;
	WallEnemy.MoveFlagY = 1;
}

void WallEnemyAction()
{
	static int count = 0;
	if(WallEnemy.LiveFlag==0 || Player.LiveFlag==0)
		count =0;
	if(WallEnemy.LiveFlag == 0)
	{
		CreateWallEnemy();
	}
	if(count>22)
	{
		if(WallEnemy.MoveFlagY) WallEnemy.y+=2;
	}
	count++;
}

void EnemyAction1()
{
	int i;

	for(i=0; i<ENEMY_MAX; i++)
	{
		if(Enemy[i].LiveFlag == 0) continue;

		if(Enemy[i].MoveFlagX == 1) Enemy[i].x++;
		else Enemy[i].x--;

		if(abs(Enemy[i].StartX - Enemy[i].x) >= 10)
		{
			Enemy[i].MoveFlagX = !Enemy[i].MoveFlagX;

			if(abs(Enemy[i].StartY - Enemy[i].y) >= 12
				|| Enemy[i].StartY - Enemy[i].y == 1)
			{
				Enemy[i].MoveFlagY = 0;
			}

			if(Enemy[i].MoveFlagY == 1) Enemy[i].y+=2;
			else Enemy[i].y;
		}
		if(rand() % 300 < 1) CreateBullet(ENEMY_SHOT, Enemy[i].x, Enemy[i].y);
	}
}


void EnemyAction2()
{
	int i;

	for(i=0; i<ENEMY_NUM_STAGE_TWO; i++)
	{
		if(Enemy[i].LiveFlag == 0) continue;

		if(Enemy[i].MoveFlagX == 1) Enemy[i].x+=2;
		else Enemy[i].x-=2;

		if(abs(Enemy[i].StartX - Enemy[i].x) >= 3)
		{
			Enemy[i].MoveFlagX = !Enemy[i].MoveFlagX;

			if(abs(Enemy[i].StartY - Enemy[i].y) >= 9
				|| Enemy[i].StartY - Enemy[i].y == 1)
			{
				Enemy[i].MoveFlagY = 0;
			}

			if(Enemy[i].MoveFlagY == 1) Enemy[i].y++;
			else Enemy[i].y;
		}
		if(rand() % 100 < 1) {
			/*CreateGuidedShot(ENEMY_SHOT, Enemy[i].x-1, Enemy[i].y);
			CreateGuidedShot(ENEMY_SHOT, Enemy[i].x+1, Enemy[i].y);*/
		}
		if(rand() % 150 < 2)
		{
			CreateBullet(ENEMY_SHOT, Enemy[i].x-1, Enemy[i].y);
			CreateBullet(ENEMY_SHOT, Enemy[i].x+1, Enemy[i].y);
		}
	}
}

void EnemyAction3()
{
	int i,j;
	for(i=0; i<Enemy_NUM_STAGE_THREE; i++)
	{
		if(Enemy[i].LiveFlag ==0) continue;

		if(abs(Enemy[i].StartY - Enemy[i].y) >= 14)
		{
			Enemy[i].MoveFlagY = 0;
		}

		if(Enemy[i].MoveFlagY == 1) Enemy[i].y+=2;
		else Enemy[i].y;

		if(Enemy[i].MoveFlagX == 1) Enemy[i].x++;
		else Enemy[i].x--;
		Enemy[i].MoveFlagX = !Enemy[i].MoveFlagX;
		

		if(GetAsyncKeyState('Z') & 0x8000 || GetAsyncKeyState('X') & 0x8000)
		{

			Enemy[i].MoveFlagX = rand()%2;
			Enemy[i].MoveFlagY = rand()%2;
			if(Enemy[i].x <= 4)
				Enemy[i].MoveFlagX=1;
			else if(Enemy[i].x >=WIDTH-5)
				Enemy[i].MoveFlagX=0;
			if(Enemy[i].y < 2)
			{
				Enemy[i].y = 3;
				Enemy[i].MoveFlagY =1;
			}
			else if(Enemy[i].y > HEIGHT-25)
				Enemy[i].y =0;

			if(Enemy[i].MoveFlagX) Enemy[i].x+=2;
			else Enemy[i].x-=2;

			if(Enemy[i].MoveFlagY) Enemy[i].y++;
			else Enemy[i].y--;;

			if(rand()%100<5)
			{
				CreateGuidedShot(ENEMY_SHOT, Enemy[i].x, Enemy[i].y);
				CreateGuidedShot(ENEMY_SHOT, Enemy[i].x, Enemy[i].y+1);
			}
		}
		else
		{
			if(rand()%100<15)
				CreateBullet(ENEMY_SHOT, Enemy[i].x, Enemy[i].y);
		}
	}
}


void DrawBoss()
{
	int i, j, k;

	for(i=0; i<1; i++)
	{
		if(Enemy[i].LiveFlag == 0) continue;
		if(Enemy[i].y<=0 || Enemy[i].y>HEIGHT-4) continue;;

		for(j=0; j<BOSS_HEIGHT; j++)
		{
			for(k=0; k<BOSS_WIDTH; k++)
			{
				if(Enemy[i].HP >= BOSS_MAX_HP/2)
				{
					if(Enemy[i].x>1 && Enemy[i].x<WIDTH-2)
						Screen[Enemy[i].y+j][Enemy[i].x+k] = Boss[j][k];
				}
				else
					if(Enemy[i].x>1 && Enemy[i].x<WIDTH-2)
						Screen[Enemy[i].y+j][Enemy[i].x+k] = BrokenBoss[j][k];
			}
		}
	}
}
void DrawEnemy()
{
	int i, j;

	for(i=0; i<ENEMY_MAX; i++)
	{
		if(Enemy[i].LiveFlag == 0) continue;
		//죽은 적은 그리지 않겠다.
		if(Enemy[i].y<=0 || Enemy[i].y>HEIGHT-4) continue;;
		//높이 범위를 확인

		for(j=0; j<ENEMY_SIZE; j++)
		{	
			if(Enemy[i].x>1 && Enemy[i].x<WIDTH-2)
				Screen[Enemy[i].y][Enemy[i].x + j] = CopyShape[j];
			// 좌표값에 = 그림을 넣는다.
		}
	}
}

void DrawWallEnemy()
{
	int i;
	if(WallEnemy.LiveFlag == 0) return;
	//죽은 적은 그리지 않겠다.
	if(WallEnemy.y <= 0) return;

	if(WallEnemy.y > HEIGHT-4)
	{
		WallEnemy.LiveFlag = 0;
		return;
	}
	//높이 범위를 확인

	for(i=0; i<WALL_SIZE; i++)
	{	
		if(WallEnemy.x>30 && WallEnemy.x<WIDTH-3 && WallEnemy.LiveFlag)
			Screen[WallEnemy.y][WallEnemy.x + i] = WallEnemyShape[i];
		// 좌표값에 = 그림을 넣는다.
	}
}

void BossAction()
{
	static int Delay = 0;
	int i;
	for(i=0; i<1; i++)
	{
		if(Delay) continue;
		if(!Enemy[i].LiveFlag) continue;

		if(Enemy[i].MoveFlagX) Enemy[i].x+=3;
		else Enemy[i].x-=3;

		if(abs(Enemy[i].StartX - Enemy[i].x) >= 28)
		{
			Enemy[i].MoveFlagX = !Enemy[i].MoveFlagX;
			Delay = 1;	
			for(int j=0; j<BOSS_WIDTH/3; j++)//좌우 모서리에서 공격
			{
				CreateBullet(ENEMY_SHOT, Enemy[i].x-ENEMY_SIZE/2+1+(j*3), Enemy[i].y+9);
				CreateBullet(ENEMY_SHOT, Enemy[i].x-ENEMY_SIZE/2+1+(j*3), Enemy[i].y+6);
				CreateBullet(ENEMY_SHOT, Enemy[i].x-ENEMY_SIZE/2+1+(j*3), Enemy[i].y+3);
				CreateBullet(ENEMY_SHOT, Enemy[i].x-ENEMY_SIZE/2+1+(j*3), Enemy[i].y);
			}
		}

		if(Enemy[i].HP>BOSS_MAX_HP/2)
		{
			if(Enemy[i].x>48 && Enemy[i].x<WIDTH-51)//중앙에선 멀티플샷 쏘기
			{
				for(int j=0; j<4; j++)
				{
					CreateMutipleShot(ENEMY_SHOT, Enemy[i].x+6+j, Enemy[i].y+rand()%10+j);
					CreateMutipleShot(ENEMY_SHOT, Enemy[i].x+2+j, Enemy[i].y+2+rand()%6+j);
					CreateMutipleShot(ENEMY_SHOT, Enemy[i].x-6+j, Enemy[i].y+rand()%10+j);
					CreateMutipleShot(ENEMY_SHOT, Enemy[i].x-3+j, Enemy[i].y+1+rand()%6+j);
				}
			}
		}
		if(Enemy[i].HP<=BOSS_MAX_HP/2)
		{
			if(Enemy[i].x>48 && Enemy[i].x<WIDTH-51)//중앙에선 멀티플샷 쏘기
			{
				for(int j=0; j<4; j++)
				{
					CreateGuidedShot(ENEMY_SHOT, Enemy[i].x+6+j, Enemy[i].y+rand()%10+j);
					CreateGuidedShot(ENEMY_SHOT, Enemy[i].x+2+j, Enemy[i].y+2+rand()%6+j);
					CreateGuidedShot(ENEMY_SHOT, Enemy[i].x-6+j, Enemy[i].y+rand()%10+j);
					CreateGuidedShot(ENEMY_SHOT, Enemy[i].x-3+j, Enemy[i].y+1+rand()%6+j);
				}
			}

		}
	}
	if(Delay) 
		Delay++;
	if(Delay%20 == 0)
		Delay =0;
}

void EnemyRespawnOnce(EnemyInfo *Enemy, int EnemyNum)
{
	int check=0;
	static int Once=0;
	if(Once>0) return;
	for(int i=0; i<EnemyNum; i++)
	{
		if(!Enemy[i].LiveFlag) 
			check++;
	}
	if(check==EnemyNum)
	{
		switch(CurStage)
		{
		case Stage1:
			InitialEnemyForAction1();
			break;
		case Stage2:
			InitialEnemyForAction2();
			break;
		case Stage3:
			InitialEnemyForAction3();
			break;
		case StageB:
			InitialBossAction();
			break;
		}
	}
	Once++;
}