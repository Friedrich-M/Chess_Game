#include "ChessBoard.h"
/*********************************************
***   此函数用于初始化游戏开始时的棋子信息     ***
**********************************************/

// 红方棋子
ChessType redChess[] = { 俥, 马, 相, 仕, 帥, 炮, 兵 };
// 黑方棋子
ChessType blackChess[] = { 車, 馬, 象, 士, 将, 砲, 卒 };

extern State state;
extern int redKingTop;
extern int blackKingTop;
extern step top;
extern step eatTop;
extern Chess startChess;
extern int  pause_or_continue;
extern double countDownTime;
extern int playBackAccount;
extern int round;

void ChessInit()
{
	// 遍历地图
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j].id = SPACE; // 棋子初始化为无
			map[i][j].type = NONE;
			if (i <= 4) { // 红棋
				// 处理第一行的棋子
				if (i == 0) 
				{ 
					// 0 1 2 3 4 
					if (j <= 4) {
						map[i][j].id = redChess[j];
						map[i][j].type = RED;						
					}
					// 3 2 1 0
					else {
						map[i][j].id = redChess[8-j];
						map[i][j].type = RED;
					}
				}
				// 设置炮
				if (i == 2 && (j == 1 || j == 7))
				{
					map[i][j].id = redChess[5];
					map[i][j].type = RED;
				}
				// 设置兵
				if (i == 3 && (j % 2 == 0))
				{
					map[i][j].id = redChess[6];
					map[i][j].type = RED;
				}
				map[i][j].x = j * GRID_SIZE + INTERVAL;
				map[i][j].y = i * GRID_SIZE + INTERVAL;				
			}
			else { // 黑棋
				// 处理第一行的棋子
				if (i == 9)
				{
					// 0 1 2 3 4 
					if (j <= 4) {
						map[i][j].id = blackChess[j];
						map[i][j].type = BLACK;
					}
					// 3 2 1 0
					else {
						map[i][j].id = blackChess[8 - j];
						map[i][j].type = BLACK;
					}
				}
				// 设置炮
				if (i == 7 && (j == 1 || j == 7))
				{
					map[i][j].id = blackChess[5];
					map[i][j].type = BLACK;
				}
				// 设置兵
				if (i == 6 && (j % 2 == 0))
				{
					map[i][j].id = blackChess[6];
					map[i][j].type = BLACK;
				}
				map[i][j].x = j * GRID_SIZE + INTERVAL;
				map[i][j].y = (i-1) * GRID_SIZE + INTERVAL + RiverWidth;
			}
			map[i][j].overRiver = FALSE; // 初始化为都未过河
		}	
	}
	
	// 初始化条件下红方先开始
	round = redRound;

	// 初始化state
	state.begc = -1;
	state.endc = -1;
	state.begr = -1;
	state.endr = -1;
	state.state = BEGIN;

	startChess.x = -1;
	startChess.y = -1;
	startChess.id = -1;
	startChess.type = NONE;
	startChess.overRiver = FALSE;

	// 初始化暂停状态
	pause_or_continue = 0;
		
	// 将栈顶指针初始化为0
	redKingTop = 0;
	blackKingTop = 0;
	step top = 0;
	step eatTop = 0;

	// 倒计时重置
	countDownTime = 30;

	// 播放次数初始化
	playBackAccount = 0;

}

// 此函数用于在控制台上打印棋盘的id
void show()
{
	// 打印map
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%2d ", map[i][j].id);
		}
		printf("\n");
	}
}

