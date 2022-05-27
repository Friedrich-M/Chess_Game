#include "ChessBoard.h"

/****************************************************************************************
***   此函数用于将军检测，采用获取将的位置，并搜索可以造成将军的对方棋子是否在可以造         ***
***   成将军的位置上。                                                                 ***
***                                                                                   ***
*****************************************************************************************/

// 红棋子被将军的标志和黑棋被将军的标志
#define RedFlag 1
#define BlackFlag 2

typedef struct position
{
	int row;
	int col;
} KingPosition;

// 判断地图上两个点在直线方向上有没有障碍物
bool HasBlock(int row1, int col1, int row2, int col2)
{
	int i;
	if (row1 != row2) {
		int minr = row1 < row2 ? row1 : row2;
		int maxr = row1 > row2 ? row1 : row2;		
		
		for (i = minr + 1; i < maxr; i++)
		{
			if (map[i][col1].id != SPACE)
				return TRUE;
		}
	}
	
	else if (col1 != col2) {
		int minc = col1 < col2 ? col1 : col2;
		int maxc = col1 > col2 ? col1 : col2;
		for (i = minc + 1; i < maxc; i++)
		{
			if (map[row1][i].id != SPACE)
				return TRUE;
		}
	}
	// 如果在同一行或同一列且中间没有障碍物
	return FALSE;
}

// 判断地图上两个点在直线方向上是否有且只有一个障碍物
bool HasOneBlock(int row1, int col1, int row2, int col2)
{
	int i;
	int count = 0;

	if (row1 != row2) {
		int minr = row1 < row2 ? row1 : row2;
		int maxr = row1 > row2 ? row1 : row2;

		for (i = minr + 1; i < maxr; i++)
		{
			if (map[i][col1].id != SPACE)
				count++;
		}
		if (count == 1)
			return TRUE;
		else 
			return FALSE;
	}

	// 在同一列，检测是否只有一个障碍物
	else if (col1 != col2) {
		int minc = col1 < col2 ? col1 : col2;
		int maxc = col1 > col2 ? col1 : col2;
		int count = 0;
		for (i = minc + 1; i < maxc; i++)
		{
			if (map[row1][i].id != SPACE)
				count++;
		}
		if (count == 1)
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;

}


bool checkAttackKing()
{
	int i, j;
	int row = -1, col = -1;

	bool AttackKing = FALSE;
	KingPosition RedKing = {-1, -1}, BlackKing = {-1, -1};
	
	// 获取双方将的位置 
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{	
			if (map[i][j].id == 11)
			{
				RedKing.row = i;
				RedKing.col = j;
				//printf("RedKing location %d %d %d\n", RedKing.row, RedKing.col, map[RedKing.row][RedKing.col].id);
				continue;
			}
			else if (map[i][j].id == 4)
			{
				// 获取黑方将的位置
				BlackKing.row = i;
				BlackKing.col = j;
				//printf("BlackKing location %d %d %d\n", BlackKing.row, BlackKing.col, map[i][j].id);
				continue;
			}
		}
	}
	

	// 检测红方帅在竖直方向上有没有被 黑车 将军
	for (row = 0; row < ROW; row++)
	{
		// 如果红帅和黑车在同一列并且之间没有障碍，则红帅被将军
		if (map[row][RedKing.col].id == 0 && !HasBlock(row, RedKing.col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}
	// 检测红帅将在水平方向上有没有被 黑车 将军
	for (col = 0; col < COL; col++)
	{
		// 如果红帅和黑车在同一行并且之间没有障碍，则红帅被将军
		if (map[RedKing.row][col].id == 0 && !HasBlock(RedKing.row, col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}

	// 检测红帅有没有被斜上方 黑马 将军
	if (map[RedKing.row + 2][RedKing.col + 1].id == 1 || map[RedKing.row + 2][RedKing.col - 1].id == 1)
	{
		// 判断是否被别马脚
		if (map[RedKing.row + 1][RedKing.col].id == SPACE)
		{
			return RedFlag;
		}
	}

	// 检测红帅有没有被斜下方 黑马 将军
	if (map[RedKing.row - 2][RedKing.col + 1].id == 1 || map[RedKing.row - 2][RedKing.col - 1].id == 1)
	{
		// 判断是否被别马脚
		if (map[RedKing.row - 1][RedKing.col].id == SPACE)
		{
			return RedFlag;
		}
	}
			
	// 检测红帅有没有被左侧 黑马 将军
	if (map[RedKing.row + 1][RedKing.col - 2].id == 1 || map[RedKing.row - 1][RedKing.col - 2].id == 1)
	{
		// 判断是否被别马脚
		if (map[RedKing.row][RedKing.col - 1].id == SPACE)
		{
			return RedFlag;
		}
	}

	// 检测红帅有没有被右侧 黑马 将军
	if (map[RedKing.row + 1][RedKing.col + 2].id == 1 || map[RedKing.row - 1][RedKing.col + 2].id == 1)
	{
		// 判断是否被别马脚
		if (map[RedKing.row][RedKing.col + 1].id == SPACE)
		{
			return RedFlag;
		}
	}

	// 检测红帅有没有被 黑兵 将军
	// 检查上左右四个方向
	if (map[RedKing.row + 1][RedKing.col].id == 6 ||
		map[RedKing.row][RedKing.col + 1].id == 6 ||
		map[RedKing.row][RedKing.col - 1].id == 6)
	{
		return RedFlag;
	}

	// 检查红帅有没有被 黑炮 将军 
	// 炮在上下方向
	for (row = 0; row < ROW; row++)
	{
		if (map[row][RedKing.col].id == 5 && HasOneBlock(row, RedKing.col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}

	// 炮在左右方向
	for (col = 0; col < COL; col++)
	{
		if (map[RedKing.row][col].id == 5 && HasOneBlock(RedKing.row, col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}	
	
	
	// 黑将被红车将军
	for (row = 0; row < ROW; row++)
	{
		if (map[row][BlackKing.col].id == 7 && !HasBlock(row, BlackKing.col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}
	for (col = 0; col < COL; col++)
	{
		if (map[BlackKing.row][col].id == 7 && !HasBlock(BlackKing.row, col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}
	

	// 黑帅被红马将军
	if (map[BlackKing.row + 2][BlackKing.col + 1].id == 8 || map[BlackKing.row + 2][BlackKing.col - 1].id == 8)
	{
		// 判断是否被别马脚
		if (map[BlackKing.row + 1][BlackKing.col].id == SPACE)
		{
			return BlackFlag;
		}
	}

	if (map[BlackKing.row - 2][BlackKing.col + 1].id == 8 || map[BlackKing.row - 2][BlackKing.col - 1].id == 8)
	{
		// 判断是否被别马脚
		if (map[BlackKing.row - 1][BlackKing.col].id == SPACE)
		{
			return BlackFlag;
		}
	}

	if (map[BlackKing.row + 1][BlackKing.col - 2].id == 8 || map[BlackKing.row - 1][BlackKing.col - 2].id == 8)
	{
		// 判断是否被别马脚
		if (map[BlackKing.row][BlackKing.col - 1].id == SPACE)
		{
			return BlackFlag;
		}
	}

	// 检测红帅有没有被右侧 黑马 将军
	if (map[BlackKing.row + 1][BlackKing.col + 2].id == 8 || map[BlackKing.row - 1][BlackKing.col + 2].id == 8)
	{
		// 判断是否被别马脚
		if (map[BlackKing.row][BlackKing.col + 1].id == SPACE)
		{
			return BlackFlag;
		}
	}

	// 检查下左右四个方向
	if (map[BlackKing.row - 1][BlackKing.col].id == 13 ||
		map[BlackKing.row][BlackKing.col + 1].id == 13 ||
		map[BlackKing.row][BlackKing.col - 1].id == 13)
	{
		return BlackFlag;
	}

	// 检查红帅有没有被 黑炮 将军 
	// 炮在上下方向
	for (row = 0; row < ROW; row++)
	{
		if (map[row][BlackKing.col].id == 12 && HasOneBlock(row, BlackKing.col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}

	// 炮在左右方向
	for (col = 0; col < COL; col++)
	{
		if (map[BlackKing.row][col].id == 12 && HasOneBlock(BlackKing.row, col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}

	return FALSE;	
}
