#include"manager.h"
#include"Item.h"
#include"player.h"
#include"bullet.h"
#include"Stage.h"

extern char Screen[HEIGHT][WIDTH];
extern int CurStage;
//extern int AddPattern;

void InitialObject1()			//stage 1 �ʱ�ȭ
{
	InitialEnemyForAction1();
	InitialPlayer();
	InitialSideWall();
}
void InitialObject2()			//stage 2 �ʱ�ȭ
{
	InitialEnemyForAction2();
	InitialPlayer();
	InitialSideWall();
}
void InitialObject3()
{
	InitialEnemyForAction3();
	InitialPlayer();
	InitialSideWall();
}
void InitialObjectBoss()		
{
	InitialBossAction();
	InitialPlayer();
	InitialSideWall();
}

void ActionFuncs1()				//stage 1 ��ǥ����
{
	GuidedShotAction(Player.x, Player.y);
	SimpleBulletAction();
	MutipleShotAction();
	EnemyAction1();
	PlayerAction();
	GunItemAction(Player.x, Player.y);
	WallAction();
	ItemAction();
}

void ActionFuncs2()				//stage 2 ��ǥ����
{
	GuidedShotAction(Player.x, Player.y);
	SimpleBulletAction();
	MutipleShotAction();
	EnemyAction2();
	PlayerAction();
	GunItemAction(Player.x, Player.y);
	WallAction();
	ItemAction();
}

void ActionFunc3()
{
	GuidedShotAction(Player.x, Player.y);
	SimpleBulletAction();
	MutipleShotAction();
	EnemyAction3();
	PlayerAction();
	GunItemAction(Player.x, Player.y);
	WallAction();
	ItemAction();
}

void ActionFuncsBoss()				//stage 3 ��ǥ����
{
	GuidedShotAction(Player.x, Player.y);
	MutipleShotAction();
	SimpleBulletAction();
	BossAction();
	PlayerAction();
	GunItemAction(Player.x, Player.y);
	WallAction();
	ItemAction();
}


void CheckCursh()
{
	ShotCheckCrush();			//Shot[i]ź�� �ٸ� ��ü�� �浹
	MutipleShotCheckCrush();	//MultipleShot[i]ź�� �ٸ� ��ü�� �浹
	EnemyWallCheckCrush();		//(EnemyWall)���� �÷��̾��浹
	ItemCheckCrush();			//����� �Ա� ���� �Լ�
	EnemyGuidedShotCheckCrush();


	if(HEIGHT-4<Item.y)//�ٴڿ� ���� ������ ó��
		Item.UseFlag=0;
}


//EnemyWall�� �÷��̾��� �浹 ���� �Լ�
void EnemyWallCheckCrush()
{
	int i;
	for(i=0;i<4 ; i++)
	{
		if((WallEnemy.x<=Player.x-PLAYER_SIZE/2 
			&& WallEnemy.x<=Player.x+PLAYER_SIZE/2
			&& WallEnemy.x+WALL_SIZE>=Player.x-PLAYER_SIZE/2
			&& WallEnemy.x+WALL_SIZE>=Player.x+PLAYER_SIZE/2
			&& WallEnemy.y-i == Player.y ))
		{
			if(Player.y <= HEIGHT-1)	Player.y =  WallEnemy.y+2;			//���� �и���
			if (Player.y >= HEIGHT-2)	Player.LiveFlag = 0;	//�ٴڱ��� �и��� �װ�
		}
	}
}

//��� �����ư� �÷��̾��� �浹 ���� �Լ�
void ItemCheckCrush()
{
	if((Item.x >= Player.x-PLAYER_SIZE/2 
		&& Item.x <= Player.x+PLAYER_SIZE/2 
		&& Item.y == Player.y) || (Item.x >= Player.x-PLAYER_SIZE/2 
		&& Item.x <= Player.x+PLAYER_SIZE/2 
		&& Item.y == Player.y-1)|| (Item.x >= Player.x-PLAYER_SIZE/2 
		&& Item.x <= Player.x+PLAYER_SIZE/2 
		&& Item.y == Player.y+1))
	{
		switch(Item.Type)
		{
		case GUN_ITEM: //1
			for(int j=0 ; j<10; j++)
			{
				if(MakeShape[j].UseFlag == 0) 
					MakeShape[j].UseFlag =1;
			}
			if(Player.WaveShotNum>0) Player.WaveShotNum =0;
			Player.ItemOn = TWO_SHOT_ITEM_ON;
			Item.UseFlag = 0;
			Player.ItemShotNum = 80;
			break;
		case HP_ITEM: //2
			if(Item.UseFlag)
				if(Player.HP <=5)
					Player.HP++;
			Item.UseFlag = 0;
			break;
		case WAVE_SHOT: //4
			for(int j=0 ; j<10; j++)
			{
				if(MakeShape2[j].UseFlag == 0) 
					MakeShape2[j].UseFlag =1;
			}
			if(Player.ItemShotNum>0) Player.ItemShotNum =0;
			Item.UseFlag = 0;
			Player.ItemOn = WAVE_SHOT_ITEM_ON;
			Player.WaveShotNum = 80;
			break;
		}
	}
}


// �Ϲ�ź�� �̿���ź�� ��� ��ä�� �浹 ���� �Լ� Shot[i]
void ShotCheckCrush()
{
	int i,j;
	for(i=0; i<MAX_BULLET; i++)
	{
		if(Shot[i].Type == PLAYER_SHOT)//�÷��̾��� �Ѿ���
		{
			for(j=0 ;j<ENEMY_MAX; j++)//�Ѿ˰� ���� ��ǥ ��
			{
				if(Enemy[j].LiveFlag == 0) continue;

				if(CurStage == BOSS_STAGE)//Stage 3������ �� ���� ����
				{
					for(int k=0; k<5; k++)
					{
						if(Shot[i].x >= Enemy[j].x -BOSS_SIZE/2 
							&& Shot[i].x <= Enemy[j].x +BOSS_SIZE/2+19
							&& Shot[i].y == Enemy[j].y+k && Shot[i].UseFlag == 1)
						{  
							Shot[i].UseFlag = 0;
							DropItem(20,Enemy,j);
							Enemy[j].HP--;
							if(Enemy[j].HP==0)
							{
								Enemy[j].LiveFlag = 0;
								Player.Score+=100;
							}
							break;
						}	
					}
				}//Stage 3�� �ƴϸ�
				else if(CurStage !=BOSS_STAGE)
				{
					if(Shot[i].x >= Enemy[j].x -ENEMY_SIZE/2 
						&& Shot[i].x <= Enemy[j].x +ENEMY_SIZE/2
						&& Shot[i].y == Enemy[j].y && Shot[i].UseFlag == 1)
					{
						Shot[i].UseFlag = 0;
						DropItem(80,Enemy,j);//������ ��� ���� �Լ� ȣ��
						Enemy[j].HP--;
						if(Enemy[j].HP==0)
						{
							Player.Score+=100;
							Enemy[j].LiveFlag = 0;
						}
						break;
					}
				}
			}
			/////////////////////////////////�÷��̾� �Ѿ˰� ��
			if(WallEnemy.LiveFlag == 1)
			{
				if((Shot[i].x >= WallEnemy.x 
					&& Shot[i].x <= WallEnemy.x+WALL_SIZE
					&& Shot[i].y == WallEnemy.y) || (Shot[i].x >= WallEnemy.x 
					&& Shot[i].x <= WallEnemy.x+WALL_SIZE
					&& Shot[i].y+1 == WallEnemy.y))
				{
					if(Shot[i].UseFlag ==1)
					{
						if(MultipleShot[i].UseFlag)
							WallEnemy.HP--;
						if(WallEnemy.HP == 0)
						{
							WallEnemy.LiveFlag = 0;
						}
						MultipleShot[i].UseFlag = 0;
					}
					if(MultipleShot[i].UseFlag ==1)
					{
						if(MultipleShot[i].UseFlag)
							WallEnemy.HP--;
						if(WallEnemy.HP == 0)
						{
							WallEnemy.LiveFlag = 0;
						}
						MultipleShot[i].UseFlag = 0;
					}
				}
			}
		}
		else if(Shot[i].Type == ENEMY_SHOT)//���� �� �Ѿ�
		{	///////�Ѿ˰� �÷��̾�� ��ǥ ��
			if(Player.LiveFlag == 0) continue;

			if(Shot[i].x >= Player.x -PLAYER_SIZE/2 
				&& Shot[i].x <= Player.x +PLAYER_SIZE/2
				&& Shot[i].y == Player.y)
			{
				if(Shot[i].UseFlag)
					Player.HP--;
				if(Player.HP == 0 )
					Player.LiveFlag = 0;
				Shot[i].UseFlag = 0;
			}
		}

		if(MultipleShot[i].Type == ENEMY_SHOT)//���� �� �Ѿ�
		{	///////�Ѿ˰� �÷��̾�� ��ǥ ��
			if(Player.LiveFlag == 0) continue;

			if(MultipleShot[i].x >= Player.x -PLAYER_SIZE/2 
				&& MultipleShot[i].x <= Player.x +PLAYER_SIZE/2
				&& MultipleShot[i].y == Player.y)
			{
				if(MultipleShot[i].UseFlag)
					Player.HP--;
				if(Player.HP == 0 )
					Player.LiveFlag = 0;
				MultipleShot[i].UseFlag = 0;
			}
		}
	}
}

void EnemyGuidedShotCheckCrush()
{
	int i;
	for(i=0; i<MAX_BULLET; i++)
	{
	if(GuidedShot[i].Type == ENEMY_SHOT)//���� �� �Ѿ�
		{	///////�Ѿ˰� �÷��̾�� ��ǥ ��
			if(Player.LiveFlag == 0) continue;

			if(GuidedShot[i].x >= Player.x -PLAYER_SIZE/2 
				&& GuidedShot[i].x <= Player.x +PLAYER_SIZE/2
				&& GuidedShot[i].y == Player.y)
			{
				if(GuidedShot[i].UseFlag)
					Player.HP--;
				if(Player.HP == 0 )
					Player.LiveFlag = 0;
				GuidedShot[i].UseFlag = 0;
			}
		}
	}
}
//������� ���������� ź �浿 ���� �Լ� MutipleShot[i]
void MutipleShotCheckCrush()
{
	int i,j;
	for(i=0; i<MAX_BULLET; i++)
	{
		if(MultipleShot[i].Type == PLAYER_SHOT)//�÷��̾��� �Ѿ���
		{
			for(j=0 ;j<ENEMY_MAX; j++)//���̺꼦�� ���� ��ǥ ��
			{
				if(Enemy[j].LiveFlag == 0) continue;

				if(CurStage == BOSS_STAGE)//Stage 3������ �� ���� ����
				{
					for(int k=0; k<5; k++)
					{
						if(MultipleShot[i].x >= Enemy[j].x -BOSS_SIZE/2 
							&& MultipleShot[i].x <= Enemy[j].x +BOSS_SIZE/2+19
							&& MultipleShot[i].y == Enemy[j].y+k && MultipleShot[i].UseFlag == 1)
						{  
							MultipleShot[i].UseFlag = 0;
							DropItem(20,Enemy,j);
							Enemy[j].HP--;
							if(Enemy[j].HP==0)
							{
								Enemy[j].LiveFlag = 0;
								Player.Score+=100;
							}
							break;
						}	
					}
				}//Stage 3�� �ƴϸ�
				else if(CurStage !=BOSS_STAGE)
				{
					if(MultipleShot[i].x >= Enemy[j].x -ENEMY_SIZE/2 
						&& MultipleShot[i].x <= Enemy[j].x +ENEMY_SIZE/2
						&& MultipleShot[i].y == Enemy[j].y && MultipleShot[i].UseFlag == 1)
					{
						
						MultipleShot[i].UseFlag = 0;
						DropItem(80,Enemy,j);//������ ��� ���� �Լ� ȣ��
						Enemy[j].HP--;
						if(Enemy[j].HP==0)
						{
							Enemy[j].LiveFlag = 0;
							Player.Score+=100;
						}
						break;
					}
				}
			}
			//�÷��̾� ���̺� ���� �� �浹
			if(WallEnemy.LiveFlag == 1)
			{
				if((MultipleShot[i].x >= WallEnemy.x 
					&& MultipleShot[i].x <= WallEnemy.x+WALL_SIZE
					&& MultipleShot[i].y == WallEnemy.y) || (MultipleShot[i].x >= WallEnemy.x 
					&& MultipleShot[i].x <= WallEnemy.x+WALL_SIZE
					&& MultipleShot[i].y+1 == WallEnemy.y))
				{
					if(MultipleShot[i].UseFlag ==1)
					{
						if(MultipleShot[i].UseFlag)
							WallEnemy.HP--;
						if(WallEnemy.HP == 0)
						{
							WallEnemy.LiveFlag = 0;
						}
						MultipleShot[i].UseFlag = 0;
					}
				}
			}
		}
	}
}

void InitialBossAction()
{
	int i;
	int x,y;
	x =19;
	y =2;
	for(i=0; i<1;i++)
	{

		Enemy[i].HP = BOSS_MAX_HP;
		Enemy[i].LiveFlag=1;
		Enemy[i].MoveFlagX =1;
		Enemy[i].MoveFlagY =1;
		Enemy[i].StartX = x+BOSS_WIDTH/2;
		Enemy[i].StartY = y; //+3
		Enemy[i].x = x+BOSS_WIDTH/2;
		Enemy[i].y = y;
	}
}

void Draw()
{
	//�����
	EraseScreen();
	//��ǥ �����ϰ�
	DrawBullet();
	DrawGuidedShot();
	DrawMutipleShot();
	DrawItem();
	DrawEnemy();
	DrawWall();
	DrawWallEnemy();
	DrawPlayer();
	DrawGunItemShape();
	//�׸���
	PrintScreen();
}



void DrawForStageBoss()
{
	//�����
	EraseScreen();
	//��ǥ �����ϰ�
	DrawBullet();
	DrawMutipleShot();
	DrawGuidedShot();
	DrawWall();
	DrawItem();
	DrawGunItemShape();
	DrawBoss();
	DrawPlayer();
	//�׸���
	PrintScreen();
}

void EraseScreen()
{
	for(int i=0; i<HEIGHT; i++)
	{
		memset(Screen[i], ' ', WIDTH);
		Screen[i][WIDTH-1] = NULL;
	}
}
void EraseGageBar()
{
	MoveCursor(20, 34);
	printf("                                                        ");
}

void PrintScreen()
{
	for(int i=1; i<HEIGHT; i++)
	{
		MoveCursor(0, i);
		printf(Screen[i]);
	}
}

void ClearSetting()
{
	int i;
	if(Item.UseFlag == 1)
		Item.UseFlag =0;

	if(WallEnemy.LiveFlag == 1) 
		WallEnemy.LiveFlag = 0;

	for(i=0; i<MAX_BULLET; i++)
	{
		MultipleShot[i].UseFlag = 0;
		Shot[i].UseFlag = 0;
		GuidedShot[i].UseFlag = 0;
	}

	if(Player.LiveFlag == 0)
		switch(CurStage)
	{
		case Stage1:
			InitialObject1();
			break;
		case Stage2:
			InitialObject2();
			break;
		case Stage3:
			InitialObject3();
			break;
		case StageB:
			InitialObjectBoss();
			break;
	}
}



