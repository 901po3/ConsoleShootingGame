#include"Item.h"
#include"console.h"
#include"player.h"
#include"manager.h"


extern char Screen[HEIGHT][WIDTH];
extern int CurStage;

void CreateItem( int Type, int x, int y)
{
	if(Item.UseFlag == 0)
	{
		Item.UseFlag = 1;
		Item.Type = Type;
		Item.x = x;
		Item.y =y;
		if(CurStage == BOSS_STAGE)//Stage 3의 적기 Y값이 다르기 때문에
			Item.y = y+3;
	}
}

void DrawItem()
{
	if(Item.UseFlag == 0) return;
	
	if(Item.x > 3 && Item.x < WIDTH-4 && Item.y>=0 && Item.y<HEIGHT-3)
	{
		switch(Item.Type)
		{
		case GUN_ITEM:
			Screen[Item.y][Item.x] = ItemShotShape;
			break;
		case HP_ITEM:
			Screen[Item.y][Item.x] = ItemHPShape;
			break;
		case WAVE_SHOT:
			Screen[Item.y][Item.x] = WaveShot;
			break;
		}
	}
}

void ItemAction()
{
	static int count =0;

	if(Item.UseFlag == 0) return;
	
	if(Item.x > 3 && Item.x < WIDTH-4 && Item.y>=0 && Item.y<HEIGHT-3)
	{
		if(Item.y>HEIGHT-3)	
			Item.UseFlag = 0;

		else if(count%2== 0)
		{
			Item.y++;
			count = 0;
		}
		count++;
	}
}

void GunItemAction(int x, int y)//총알개수에 따라 아이탬 이미지 표시
{
	for(int i=0; i<GUNE_SHAPE_SIZE+1 ; i++)
	{
		switch(Player.ItemOn)
		{
		case TWO_SHOT_ITEM_ON:
			if(Player.ItemShotNum == 0)
			{
				MakeShape[i].UseFlag = 0;
				Player.ItemOn = 0;
			}
			if(Player.ItemShotNum>0)
			{
				if(x-1 < 3 || x+1 > WIDTH -3) return;
				MakeShape[i].x = Player.x-4+i;
				MakeShape[i].y = Player.y-1;
			}
			break;
		case WAVE_SHOT_ITEM_ON:
			if(Player.WaveShotNum == 0)
			{
				MakeShape2[i].UseFlag = 0;
				Player.ItemOn = 0;
			}
			if(Player.WaveShotNum>0)
			{
				if(x-1 < 3 || x+1 > WIDTH -3) return;
				MakeShape2[i].x = Player.x-4+i;
				MakeShape2[i].y = Player.y-1;
			}
			break;
		}
	}
}

void DrawGunItemShape()
{
	for(int i=0;i<GUNE_SHAPE_SIZE+1;i++)
	{/////총 모양 추가할 좌표 설정
		if(MakeShape[i].UseFlag == 0) return;

		switch(Player.ItemOn)
		{
		case TWO_SHOT_ITEM_ON: //1
			Screen[MakeShape[i].y][MakeShape[i].x] = GunItemShape[i];
			break;
		case WAVE_SHOT_ITEM_ON://2		
			Screen[MakeShape2[i].y][MakeShape2[i].x] = WaveItemShape[i];
			break;
		}
	}
}

void DropItem(int Percentage, EnemyInfo *Enemy, int loopNum)
{
	if(rand() % 100 < Percentage)
	{
		int Type = rand()%3+1;
		switch(Type)
		{
		case GUN_ITEM: //1
			CreateItem(GUN_ITEM, Enemy[loopNum].x, Enemy[loopNum].y);
			break;
		case HP_ITEM: //2
			CreateItem(HP_ITEM, Enemy[loopNum].x, Enemy[loopNum].y);
			break;
		case WAVE_SHOT-1://4-1
			CreateItem(WAVE_SHOT, Enemy[loopNum].x, Enemy[loopNum].y);
			break;
		}
	}
}

void ConsumeItemOn()
{
	if(Player.ItemOn ==1)
		if(Player.ItemShotNum==0)
				Player.ItemOn = NORMAL_SHOT_ITEM_ON;
	if(Player.ItemOn ==2)
		if(Player.WaveShotNum==0)
				Player.ItemOn = NORMAL_SHOT_ITEM_ON;
}