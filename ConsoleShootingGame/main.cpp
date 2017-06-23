#include"common.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"manager.h"
#include"ScreenOut.h"
#include"Stage.h"
#include"Item.h"


#define COMMAND_SIZE 256
//가장 처음 화면을 만들 2차원 배열 생성
char Screen[HEIGHT][WIDTH];

char PlayerUnit[PLAYER_SIZE+1] = "i=o=i";
char EnemyUnit[ENEMY_SIZE+1] = "=!=";
char EnemyUnit2[ENEMY_SIZE+1] = "q=p";
char EnemyUnit3[ENEMY_SIZE+1] = "=A=";
char WallEnemyShape[WALL_SIZE+1] = "  -------------  ";
char PlayerShot = '!';
char PlayerItemShot = '^';
char EnemyMutipleShotShape = 'o';
char PlayerMutipleShotShape = '#';
char PlayerMegaShot = 'A';
char EnemyShot = '*';
char SideWallShape = 'l';
char ItemShotShape = 'S';
char ItemHPShape = 'H';
char WaveShot = 'W';
char GuidedBullet ='O';

char GunItemShape[GUNE_SHAPE_SIZE+1] = " .u. .u.  ";
char WaveItemShape[GUNE_SHAPE_SIZE+1] = " .w. .w.  ";
char Boss[BOSS_HEIGHT][BOSS_WIDTH+1] = {
	"  ┌┘────★────└┐  ",
	"┌┘■■■■■■■■■■■└┐",
	"│  ■■■■보오스■■■■  │",
	"└┐■■■■■■■■■■■┌┘",
	"  └───────────┘  ",};
char BrokenBoss[BOSS_HEIGHT][BOSS_WIDTH+1] = {
	"  ┌  ────☆  ───└    ",
	"┌┘□      □□□□□□  └┐",
	"    □□□심한  손상□□  □│",
	"└┐    □  □□□□□□□┌┘",
	"    ──    ────      ┘  ",};
struct PlayerInfo Player;
struct EnemyInfo Enemy[ENEMY_MAX];
struct ShotInfo Shot[MAX_BULLET];
struct WallInfo SideWall[MAX_LINE];
struct EnemyInfo WallEnemy;
struct ShotInfo MultipleShot[MAX_BULLET];
struct ShotInfo GuidedShot[MAX_BULLET];

struct item Item;
struct item MegaItem;
struct item MakeShape[GUNE_SHAPE_SIZE+1];
struct item MakeShape2[GUNE_SHAPE_SIZE+1];

int CurStage = 0;

void main(int argc, char* argv[])
{
	//콘솔창 크기 자동 설정
	char command[COMMAND_SIZE] = { '\0', };
	int lines = 35;
	int cols = 100;
	sprintf(command, "mode con: lines=%d cols=%d", lines, cols);
	system(command);

	Initial();

	//StageThree();
	//StageBoss();
	//StageTwo();
	int StageNum=0;
	while(StageNum!=-1)
	{
		switch(StageNum)
		{
		case Stage1: 
			StageNum = StageOne(); 
			break;
		case Stage2: 
			StageNum = StageTwo(); 
			break;
		case Stage3:
			StageNum = StageThree();
			break;
		case StageB:
			StageNum = StageBoss();
			break;
		}
	}
}




