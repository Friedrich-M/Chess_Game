#include "ChessBoard.h"
/*********************************************
***   ���ļ������˼�¼�ĸ����׵ĺ���           ***
**********************************************/

// �췽����
static ChessType redChess[] = { �e, ��, ��, ��, ��, ��, �� };
// �ڷ�����
static ChessType blackChess[] = { ܇, �R, ��, ʿ, ��, �h, �� };

void DrawManual(int *mode)
{
	// ������ͼ
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j].id = SPACE; // ���ӳ�ʼ��Ϊ��
			map[i][j].type = NONE;
		}
	}
	
	// ��ʼ�����Ǿۻ�����
	if (*mode == 1) 
	{
		// ����
		map[0][4].id = redChess[4];
		map[0][6].id = map[0][7].id = redChess[0];
		map[2][7].id = redChess[5];
		map[7][5].id = map[8][3].id = map[4][8].id = redChess[6];
		map[0][4].type = map[0][6].type = map[0][7].type = map[2][7].type = \
			map[7][5].type = map[8][3].type = map[4][8].type = RED;

		// ����
		map[1][3].id = map[1][5].id = map[2][1].id = map[2][4].id = blackChess[6];
		map[7][4].id = blackChess[2];
		map[9][4].id = blackChess[0];
		map[9][5].id = blackChess[4];
	}

	// ��򾽵������
	else if (*mode == 2)
	{
		// ����
		map[0][5].id = redChess[4];
		map[4][5].id = map[0][8].id = redChess[0];
		map[4][8].id = redChess[6];
		map[0][5].type = map[4][5].type = map[0][8].type = map[4][8].type = RED;
		
		// ����
		map[1][4].id = map[1][6].id = map[5][2].id = blackChess[6];
		map[7][4].id = blackChess[2];
		map[8][4].id = map[9][3].id = blackChess[3];
		map[9][4].id = blackChess[4];
	}

	// Ұ���������
	else if (*mode == 3)
	{
		// ����
		map[0][3].id = redChess[4];
		map[2][4].id = map[4][2].id = redChess[2];
		map[3][2].id = map[3][4].id = redChess[6];
		map[5][6].id = redChess[1];
		map[5][7].id = map[5][8].id = redChess[0];
		map[0][3].type = map[2][4].type = map[4][2].type = map[3][2].type = \
			map[3][4].type = map[5][6].type = map[5][7].type = map[5][8].type = RED;
		
		// ����
		map[1][4].id = map[2][3].id = blackChess[6];
		map[3][1].id = blackChess[0];
		map[7][4].id = map[9][2].id = blackChess[2];
		map[8][4].id = map[9][3].id = blackChess[3];
		map[9][4].id = blackChess[4];
	}

	// ǧ���������
	else if (*mode == 4)
	{
		// ����
		map[0][4].id = redChess[4];
		map[2][4].id = redChess[0];
		map[3][2].id = map[7][4].id = redChess[6];
		map[0][4].type = map[2][4].type = map[3][2].type = map[7][4].type = RED;

		// ����
		map[1][3].id = map[1][5].id = map[3][6].id = map[6][0].id = blackChess[6];
		map[7][3].id = blackChess[3];
		map[7][8].id = blackChess[2];
		map[9][4].id = blackChess[4];
		map[4][6].id = blackChess[1];
	}
}










\