#include"sideWall.h"

extern char Screen[HEIGHT][WIDTH];
extern int CurStage;
void InitialSideWall()
{
	int i;
	int y = 0;
	for(i=0; i<MAX_LINE; i++)
	{
		SideWall[i].y = y;
		SideWall[i].LiveFlag = 1;
		y+=2;
	}
}

void WallAction()
{
	int i;

	for(i=0; i<MAX_LINE; i++)
	{
		if(SideWall[i].y > HEIGHT-3)//������ �ʰ��ϸ�
		{
			InitialSideWall();
		}
		//�� for������ i�� ��� �ٷ� ���������� Ŀ��
		//�ƴϸ� ��if�����ΰ��� �ٽ� ����
		SideWall[i].y++;
	}
}

void DrawWall()
{
	int i;
	for(i=0; i<MAX_LINE; i++)
	{
		if(SideWall[i].y > HEIGHT-3)
		{
			SideWall[i].LiveFlag = 0;
		}
		if(SideWall[i].LiveFlag == 0) continue;


		Screen[SideWall[i].y][0] = SideWallShape;
		Screen[SideWall[i].y][1] = SideWallShape;

		Screen[SideWall[i].y][SideWall[i].x+WIDTH-2] = SideWallShape;
		Screen[SideWall[i].y][SideWall[i].x+WIDTH-3] = SideWallShape;

	}
}