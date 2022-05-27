#include "ChessBoard.h"
/*********************************************
***   该文件包含了记录四副棋谱的函数           ***
**********************************************/

// 红方棋子
static ChessType redChess[] = { 俥, 马, 相, 仕, 帥, 炮, 兵 };
// 黑方棋子
static ChessType blackChess[] = { 車, 馬, 象, 士, 将, 砲, 卒 };

void DrawManual(int *mode)
{
	// 遍历地图
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j].id = SPACE; // 棋子初始化为无
			map[i][j].type = NONE;
		}
	}
	
	// 初始化七星聚会的棋局
	if (*mode == 1) 
	{
		// 红棋
		map[0][4].id = redChess[4];
		map[0][6].id = map[0][7].id = redChess[0];
		map[2][7].id = redChess[5];
		map[7][5].id = map[8][3].id = map[4][8].id = redChess[6];
		map[0][4].type = map[0][6].type = map[0][7].type = map[2][7].type = \
			map[7][5].type = map[8][3].type = map[4][8].type = RED;

		// 黑棋
		map[1][3].id = map[1][5].id = map[2][1].id = map[2][4].id = blackChess[6];
		map[7][4].id = blackChess[2];
		map[9][4].id = blackChess[0];
		map[9][5].id = blackChess[4];
	}

	// 蚯蚓降龙棋谱
	else if (*mode == 2)
	{
		// 红棋
		map[0][5].id = redChess[4];
		map[4][5].id = map[0][8].id = redChess[0];
		map[4][8].id = redChess[6];
		map[0][5].type = map[4][5].type = map[0][8].type = map[4][8].type = RED;
		
		// 黑棋
		map[1][4].id = map[1][6].id = map[5][2].id = blackChess[6];
		map[7][4].id = blackChess[2];
		map[8][4].id = map[9][3].id = blackChess[3];
		map[9][4].id = blackChess[4];
	}

	// 野马操田棋谱
	else if (*mode == 3)
	{
		// 红棋
		map[0][3].id = redChess[4];
		map[2][4].id = map[4][2].id = redChess[2];
		map[3][2].id = map[3][4].id = redChess[6];
		map[5][6].id = redChess[1];
		map[5][7].id = map[5][8].id = redChess[0];
		map[0][3].type = map[2][4].type = map[4][2].type = map[3][2].type = \
			map[3][4].type = map[5][6].type = map[5][7].type = map[5][8].type = RED;
		
		// 黑棋
		map[1][4].id = map[2][3].id = blackChess[6];
		map[3][1].id = blackChess[0];
		map[7][4].id = map[9][2].id = blackChess[2];
		map[8][4].id = map[9][3].id = blackChess[3];
		map[9][4].id = blackChess[4];
	}

	// 千里独行棋谱
	else if (*mode == 4)
	{
		// 红棋
		map[0][4].id = redChess[4];
		map[2][4].id = redChess[0];
		map[3][2].id = map[7][4].id = redChess[6];
		map[0][4].type = map[2][4].type = map[3][2].type = map[7][4].type = RED;

		// 黑棋
		map[1][3].id = map[1][5].id = map[3][6].id = map[6][0].id = blackChess[6];
		map[7][3].id = blackChess[3];
		map[7][8].id = blackChess[2];
		map[9][4].id = blackChess[4];
		map[4][6].id = blackChess[1];
	}
}










\