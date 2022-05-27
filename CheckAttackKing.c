#include "ChessBoard.h"

/****************************************************************************************
***   �˺������ڽ�����⣬���û�ȡ����λ�ã�������������ɽ����ĶԷ������Ƿ��ڿ�����         ***
***   �ɽ�����λ���ϡ�                                                                 ***
***                                                                                   ***
*****************************************************************************************/

// �����ӱ������ı�־�ͺ��屻�����ı�־
#define RedFlag 1
#define BlackFlag 2

typedef struct position
{
	int row;
	int col;
} KingPosition;

// �жϵ�ͼ����������ֱ�߷�������û���ϰ���
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
	// �����ͬһ�л�ͬһ�����м�û���ϰ���
	return FALSE;
}

// �жϵ�ͼ����������ֱ�߷������Ƿ�����ֻ��һ���ϰ���
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

	// ��ͬһ�У�����Ƿ�ֻ��һ���ϰ���
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
	
	// ��ȡ˫������λ�� 
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
				// ��ȡ�ڷ�����λ��
				BlackKing.row = i;
				BlackKing.col = j;
				//printf("BlackKing location %d %d %d\n", BlackKing.row, BlackKing.col, map[i][j].id);
				continue;
			}
		}
	}
	

	// ���췽˧����ֱ��������û�б� �ڳ� ����
	for (row = 0; row < ROW; row++)
	{
		// �����˧�ͺڳ���ͬһ�в���֮��û���ϰ������˧������
		if (map[row][RedKing.col].id == 0 && !HasBlock(row, RedKing.col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}
	// ����˧����ˮƽ��������û�б� �ڳ� ����
	for (col = 0; col < COL; col++)
	{
		// �����˧�ͺڳ���ͬһ�в���֮��û���ϰ������˧������
		if (map[RedKing.row][col].id == 0 && !HasBlock(RedKing.row, col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}

	// ����˧��û�б�б�Ϸ� ���� ����
	if (map[RedKing.row + 2][RedKing.col + 1].id == 1 || map[RedKing.row + 2][RedKing.col - 1].id == 1)
	{
		// �ж��Ƿ񱻱����
		if (map[RedKing.row + 1][RedKing.col].id == SPACE)
		{
			return RedFlag;
		}
	}

	// ����˧��û�б�б�·� ���� ����
	if (map[RedKing.row - 2][RedKing.col + 1].id == 1 || map[RedKing.row - 2][RedKing.col - 1].id == 1)
	{
		// �ж��Ƿ񱻱����
		if (map[RedKing.row - 1][RedKing.col].id == SPACE)
		{
			return RedFlag;
		}
	}
			
	// ����˧��û�б���� ���� ����
	if (map[RedKing.row + 1][RedKing.col - 2].id == 1 || map[RedKing.row - 1][RedKing.col - 2].id == 1)
	{
		// �ж��Ƿ񱻱����
		if (map[RedKing.row][RedKing.col - 1].id == SPACE)
		{
			return RedFlag;
		}
	}

	// ����˧��û�б��Ҳ� ���� ����
	if (map[RedKing.row + 1][RedKing.col + 2].id == 1 || map[RedKing.row - 1][RedKing.col + 2].id == 1)
	{
		// �ж��Ƿ񱻱����
		if (map[RedKing.row][RedKing.col + 1].id == SPACE)
		{
			return RedFlag;
		}
	}

	// ����˧��û�б� �ڱ� ����
	// ����������ĸ�����
	if (map[RedKing.row + 1][RedKing.col].id == 6 ||
		map[RedKing.row][RedKing.col + 1].id == 6 ||
		map[RedKing.row][RedKing.col - 1].id == 6)
	{
		return RedFlag;
	}

	// ����˧��û�б� ���� ���� 
	// �������·���
	for (row = 0; row < ROW; row++)
	{
		if (map[row][RedKing.col].id == 5 && HasOneBlock(row, RedKing.col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}

	// �������ҷ���
	for (col = 0; col < COL; col++)
	{
		if (map[RedKing.row][col].id == 5 && HasOneBlock(RedKing.row, col, RedKing.row, RedKing.col))
		{
			return RedFlag;
		}
	}	
	
	
	// �ڽ����쳵����
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
	

	// ��˧��������
	if (map[BlackKing.row + 2][BlackKing.col + 1].id == 8 || map[BlackKing.row + 2][BlackKing.col - 1].id == 8)
	{
		// �ж��Ƿ񱻱����
		if (map[BlackKing.row + 1][BlackKing.col].id == SPACE)
		{
			return BlackFlag;
		}
	}

	if (map[BlackKing.row - 2][BlackKing.col + 1].id == 8 || map[BlackKing.row - 2][BlackKing.col - 1].id == 8)
	{
		// �ж��Ƿ񱻱����
		if (map[BlackKing.row - 1][BlackKing.col].id == SPACE)
		{
			return BlackFlag;
		}
	}

	if (map[BlackKing.row + 1][BlackKing.col - 2].id == 8 || map[BlackKing.row - 1][BlackKing.col - 2].id == 8)
	{
		// �ж��Ƿ񱻱����
		if (map[BlackKing.row][BlackKing.col - 1].id == SPACE)
		{
			return BlackFlag;
		}
	}

	// ����˧��û�б��Ҳ� ���� ����
	if (map[BlackKing.row + 1][BlackKing.col + 2].id == 8 || map[BlackKing.row - 1][BlackKing.col + 2].id == 8)
	{
		// �ж��Ƿ񱻱����
		if (map[BlackKing.row][BlackKing.col + 1].id == SPACE)
		{
			return BlackFlag;
		}
	}

	// ����������ĸ�����
	if (map[BlackKing.row - 1][BlackKing.col].id == 13 ||
		map[BlackKing.row][BlackKing.col + 1].id == 13 ||
		map[BlackKing.row][BlackKing.col - 1].id == 13)
	{
		return BlackFlag;
	}

	// ����˧��û�б� ���� ���� 
	// �������·���
	for (row = 0; row < ROW; row++)
	{
		if (map[row][BlackKing.col].id == 12 && HasOneBlock(row, BlackKing.col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}

	// �������ҷ���
	for (col = 0; col < COL; col++)
	{
		if (map[BlackKing.row][col].id == 12 && HasOneBlock(BlackKing.row, col, BlackKing.row, BlackKing.col))
		{
			return BlackFlag;
		}
	}

	return FALSE;	
}
