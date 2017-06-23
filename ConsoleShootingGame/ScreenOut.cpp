#include"ScreenOut.h"
#include"Item.h"
#include"enemy.h"
#include"Stage.h"

extern int CurStage;

void Bar()
{
	MoveCursor(0,31);
	SKY;
	printf("����������������������������������������������������������������������������������������������������");
}

void DrawScore()
{
	WHITE;
	MoveCursor(1, 32);
	printf("����:'Z'");
	MoveCursor(1, 33);
	printf("������ ����:'x'");
	SKY;
	MoveCursor(1, 34);
	printf("����: %d    ", Player.Score);

	WHITE;
	MoveCursor(62, 32);
	printf("   ��  ");
	MoveCursor(62, 33);
	printf("��    ��");
	MoveCursor(62, 34);
	printf("   ��   ");
}

void DrawLifeStat()
{
	int i;
	RED;
	MoveCursor(WIDTH-24, 33);
	printf("HP: ");
	for(i=0; i<Player.MaxHP; i++)
	{
		MoveCursor(WIDTH-20+(i*3), 33);
		printf("�� ");
	}
	for(i=0 ;i<Player.HP ; i++)
	{
		MoveCursor(WIDTH-20+(i*3), 33);
		printf("�� ");
	}
}
void ScreenOutInfo()
{
	int i;
	SKY;
	MoveCursor(20, 33);
	printf("[�̿��� �Ѿ�: %d]", Player.ItemShotNum);
	MoveCursor(43, 33);
	printf("[���̺� ź.: %d]", Player.WaveShotNum);
	if(Player.ItemOn == 0)
	{
		MoveCursor(17, 32);
		printf("��");
	}
	else if(Player.ItemOn==1)
	{
		MoveCursor(17, 33);
		printf("��");
	}
	else if(Player.ItemOn==2)
	{
		MoveCursor(40, 33);
		printf("��");
	}
	MoveCursor(20, 32);
	printf("[�Ϲ� �Ѿ�]");
	MoveCursor(20, 34);
	printf("������: %d ", Player.Gage);
	for(i=0; i<10; i++)
	{
		MoveCursor(32+(i*2), 34);
		printf("��");
	}
	for(i=0; i< Player.Gage/10; i++)
	{
		MoveCursor(32+(i*2), 34);
		printf("��");
	}
	if(CurStage == StageB)
	{
		RED;
		MoveCursor(3, 0);
		for(i=0; i<1; i++)
			printf("BOSS HP: %d ",Enemy[i].HP);
		MoveCursor(16, 0);
		for(i=0; i< 40; i++)
			printf("��");
		MoveCursor(16, 0);
		for(i=0; i<1;i++)
			for(int j=0; j<Enemy[i].HP/20; j++)
				printf("��");
	}

}
void ScreenOut()
{
	Bar();
	DrawScore();
	ScreenOutInfo();
	DrawLifeStat();
}
