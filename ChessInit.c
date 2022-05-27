#include "ChessBoard.h"
/*********************************************
***   �˺������ڳ�ʼ����Ϸ��ʼʱ��������Ϣ     ***
**********************************************/

// �췽����
ChessType redChess[] = { �e, ��, ��, ��, ��, ��, �� };
// �ڷ�����
ChessType blackChess[] = { ܇, �R, ��, ʿ, ��, �h, �� };

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
	// ������ͼ
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j].id = SPACE; // ���ӳ�ʼ��Ϊ��
			map[i][j].type = NONE;
			if (i <= 4) { // ����
				// �����һ�е�����
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
				// ������
				if (i == 2 && (j == 1 || j == 7))
				{
					map[i][j].id = redChess[5];
					map[i][j].type = RED;
				}
				// ���ñ�
				if (i == 3 && (j % 2 == 0))
				{
					map[i][j].id = redChess[6];
					map[i][j].type = RED;
				}
				map[i][j].x = j * GRID_SIZE + INTERVAL;
				map[i][j].y = i * GRID_SIZE + INTERVAL;				
			}
			else { // ����
				// �����һ�е�����
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
				// ������
				if (i == 7 && (j == 1 || j == 7))
				{
					map[i][j].id = blackChess[5];
					map[i][j].type = BLACK;
				}
				// ���ñ�
				if (i == 6 && (j % 2 == 0))
				{
					map[i][j].id = blackChess[6];
					map[i][j].type = BLACK;
				}
				map[i][j].x = j * GRID_SIZE + INTERVAL;
				map[i][j].y = (i-1) * GRID_SIZE + INTERVAL + RiverWidth;
			}
			map[i][j].overRiver = FALSE; // ��ʼ��Ϊ��δ����
		}	
	}
	
	// ��ʼ�������º췽�ȿ�ʼ
	round = redRound;

	// ��ʼ��state
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

	// ��ʼ����ͣ״̬
	pause_or_continue = 0;
		
	// ��ջ��ָ���ʼ��Ϊ0
	redKingTop = 0;
	blackKingTop = 0;
	step top = 0;
	step eatTop = 0;

	// ����ʱ����
	countDownTime = 30;

	// ���Ŵ�����ʼ��
	playBackAccount = 0;

}

// �˺��������ڿ���̨�ϴ�ӡ���̵�id
void show()
{
	// ��ӡmap
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%2d ", map[i][j].id);
		}
		printf("\n");
	}
}

