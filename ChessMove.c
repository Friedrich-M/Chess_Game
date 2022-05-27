#include "ChessBoard.h"
#include <time.h>
/*********************************************************
***   ���ļ���������ʵ�����ӵ��ƶ������塢ʤ���ж��ȹ���     ***
**********************************************************/

extern const char* ChessTypeName[2];
extern int restart_the_game;
extern bool CountTimeflag;
int Repent_the_move = 0;
int Winner = NONE;
bool canDrawStart = TRUE;

// ��ʼ��״̬
State  state = { -1, -1, -1, -1, BEGIN };

// ��ʼ����ʼ�ƶ�����������
Chess startChess = { -1, -1, -1, -1, FALSE };

// ��������˧�ͺ��彫�Ķ�ջ
Chess redKingStack[MAXSTEP] = {11, 1, 0, 4, 0};
step redKingTop = 0;
Chess blackKingStack[MAXSTEP] = {4, 0, 9, 4, 0};
step blackKingTop = 0;


// ������ջ��¼�����߹���·
StackObj chessStack[MAXSTEP][2];
step top = 0;
// ������ջ��¼��������ʱ��˫��������Ϣ
ChessEaten eatStack[MAXSTEP][2] = {-1};
step eatTop = 0;

// ��¼ʤ�ֵ������ͷָ���βָ��
winC *head = NULL, *tail = NULL;

// ����������򣬺������ߣ�����round��ʼ��ΪredRoubd
int round = redRound;

// �����Ϣ�ص�����
void MouseEventProcess(int x, int y, int button, int event) 
{
	uiGetMouse(x, y, button, event); // GUI��ȡ���
	
	double mx, my;
	mx = ScaleXInches(x); /*pixels --> inches*/
	my = ScaleYInches(y);

	//printf("%f %f\n", mx, my);
	switch (event) { // ����¼�
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON && start_game_end == 1) {
			// ͨ���������õ������������±�
			int col, row;
			col = (mx - INTERVAL) / GRID_SIZE;
			if (my > INTERVAL + 4 * GRID_SIZE + RiverWidth / 2)
				row = (my - INTERVAL - RiverWidth) / GRID_SIZE + 1;
			else
				row = (my - INTERVAL) / GRID_SIZE;

			//printf("%f %f\n", mx, my);

			// �±�У׼
			if (mx > map[row][col].x + GRID_SIZE / 2 && my < map[row][col].y + GRID_SIZE / 2)
				col++;
			if (mx < map[row][col].x + GRID_SIZE / 2 && my > map[row][col].y + GRID_SIZE / 2)
				row++;
			if (mx > map[row][col].x + GRID_SIZE / 2 && my > map[row][col].y + GRID_SIZE / 2)
			{
				row++;
				col++;
			}

			//printf("%d %d\n", row, col);

			canDrawStart = TRUE;
			
			// ����ǵ�һ�ε�������¼��һ���������������
			startChess.x = row;
			startChess.y = col;
			startChess.id = map[row][col].id;
			startChess.type = map[row][col].type;

			if (state.state == BEGIN && map[row][col].type == round)
			{
				state.begr = row;
				state.begc = col;
				//if (!((state.begc == state.endr) && (state.endr == state.endr)))
				//	// ֻ�е�ǰ�����ε���Ĳ���ͬһ������ʱ���Ż�仯state
				state.state = END;
			}
			else if (state.state == END && (map[row][col].id == SPACE || map[row][col].type == !round))
			{
				state.endr = row;
				state.endc = col;
				state.state = BEGIN;
			}
			if (pause_or_continue == 0)
				// �����״̬������ͣ״̬���������ƶ�
				chessMove();
		}
	}
	if (state.state == BEGIN)
		state.begc = state.begr = state.endc = state.endr = -1;
	display();
}

// �ж���ʼ����յ�֮���Ƿ����ϰ���
int hasBlock(pState state)
{
	int flag = 0;
	if (state->begr != state->endr)
	{
		// �ҳ�begr��endr����Сֵ�����ֵ
		int minr = state->begr < state->endr ? state->begr : state->endr;
		int maxr = state->begr > state->endr ? state->begr : state->endr;
		for (int i = minr + 1; i < maxr; i++)
		{
			if (map[i][state->begc].id != SPACE)
			{
				flag = 1;
				return flag;
			}
		}
	}
	else if (state->begc != state->endc)
	{
		int minc = state->begc < state->endc ? state->begc : state->endc;
		int maxc = state->begc > state->endc ? state->begc : state->endc;
		for (int i = minc + 1; i < maxc; i++)
		{
			if (map[state->begr][i].id != SPACE)
			{
				flag = 1;
				return flag;
			}
		}
	}
	return flag;
}


// �ƶ�����
void chessMove()
{
	printf("start(%d %d) end(%d %d)\n", state.begr, state.begc, state.endr, state.endc);
	bool canMove = FALSE;
	
	// ʲô��������ƶ�����
	if (!(state.begr == state.endr && state.begc == state.endc) && //����Ĳ���ͬһ������
		state.endr != -1 && state.begr != -1 && // �±����Ϸ�
		map[state.begr][state.begc].id != SPACE && // û�����Ӳ����ƶ�
		map[state.begr][state.begc].id != map[state.endr][state.endc].id //�����Լ����Լ��ҵ�����
		 && round == map[state.begr][state.begc].type) // ��ǰ�ֵ��Լ���round
	{
		//printf("%d", map[state.begr][state.begc].id);
		switch (map[state.begr][state.begc].id)
		{
		case ܇:
		case �e:
			if ((state.begr == state.endr || state.begc == state.endc) &&
				map[state.begr][state.begc].type != map[state.endr][state.endc].type) // ��ֻ����ֱ�߲��ҳԵ����Ӳ����Ǽ�����
			{
				if (!hasBlock(&state))
					// ��ʼ��ͽ�����֮��û�������谭 
				{
					canMove = TRUE;
					break;
				}
			}
			break;
		case �R:
		case ��:
			if (abs(state.begr - state.endr) == 1 && abs(state.begc - state.endc) == 2
				|| abs(state.begr - state.endr) == 2 && abs(state.begc - state.endc) == 1)
			{
				if (abs(state.endr - state.begr) == 1 && (state.endc - state.begc == -2) &&
					map[state.begr][state.begc - 1].type == NONE) {
					printf("1");
					canMove = TRUE;
					break;
				}
				
				if (abs(state.endr - state.begr) == 1 && (state.endc - state.begc == 2) &&
					map[state.begr][state.begc + 1].type == NONE) {
					printf("2");		
					canMove = TRUE;
					break;
				}
				if (abs(state.endc - state.begc) == 1 && (state.endr - state.begr == 2) &&
					map[state.begr + 1][state.begc].type == NONE) {
					printf("3");
					canMove = TRUE;
					break;
				}
				if (abs(state.endc - state.begc) == 1 && (state.endr - state.begr == -2) &&
					map[state.begr - 1][state.begc].type == NONE) {					
					printf("4");
					canMove = TRUE;
					break;
				}
			}
			break;
		case ��:
		case ��:
			if (abs(state.begr - state.endr) == 2 && abs(state.begc - state.endc) == 2 &&
				map[(state.begr + state.endr) / 2][(state.begc + state.endc) / 2].type == NONE &&
				map[state.endr][state.endc].type != round)
			{
				if (map[state.begr][state.begc].type == RED && state.endr <= 4) {
					canMove = TRUE;
					break;
				}
				else if (map[state.begr][state.begc].type == BLACK && state.endr >= 5) {
					canMove = TRUE;
					break;
				}
			}
			break;
		case ʿ:
		case ��:
			if (abs(state.begr - state.endr) == 1 && abs(state.begc - state.endc) == 1)
			{
				if (round == redRound && abs(state.begr - 1) <= 1 && abs(state.endr - 1) <= 1 &&
					abs(state.begc - 4) <= 1 && abs(state.endc - 4) <= 1) {
					canMove = TRUE;
					break;
				}
				else if (round == blackRound && abs(state.begr - 8) <= 1 && abs(state.endr - 8) <= 1 &&
					abs(state.begc - 4) <= 1 && abs(state.endc - 4) <= 1) {
					canMove = TRUE;
					break;
				}
			}
			break;
		case ��:
		case ��:
			if (abs(state.begr - state.endr) == 1 && abs(state.begc - state.endc) == 0
				|| abs(state.begr - state.endr) == 0 && abs(state.begc - state.endc) == 1)
			{
				if (round == redRound) {
					if (abs(state.begr - 1) <= 1 && abs(state.begc - 4) <= 1 &&
						abs(state.endr - 1) <= 1 && abs(state.endc - 4) <= 1) {
						canMove = TRUE;
						break;
					}
					else {
						canMove = FALSE;
						break;
					}
				}
				else
				{
					if (abs(state.begr - 8) <= 1 && abs(state.begc - 4) <= 1 &&
						abs(state.endr - 8) <= 1 && abs(state.endc - 4) <= 1) {
						canMove = TRUE;
						break;
					}
					else {
						canMove = FALSE;
						break;
					}
				}
			}
			break;
		case �h:
		case ��:
			if (map[state.endr][state.endc].type == NONE)
			{
				if (state.begr == state.endr || state.begc == state.endc) // �������з�����
				{
					// ·����û������
					if (!hasBlock(&state))
						// ��ʼ��ͽ�����֮��û�������谭 
					{
						canMove = TRUE;
						break;
					}
				}
			}
			else if (map[state.endr][state.endc].type == !round) { // ���յ�����Ƕ��������
				// ��ֻ����ֱ�ߴ�
				if (state.begc == state.endc || state.begr == state.endr) {
					int count = 0; // ·�������ҽ���һ��������Ϊ����
					// ����ˮƽֱ�ߴ�
					if (state.begr == state.endr) {
						// �������
						if (state.begc < state.endc) {
							for (int i = state.begc + 1; i < state.endc; i++) {
								if (map[state.begr][i].type != NONE) {
									count++;
								}
							}
							if (count == 1) {
								canMove = TRUE;
								break;
							}
						}
						else {
							// �����Ҵ�
							for (int i = state.begc - 1; i > state.endc; i--) {
								if (map[state.begr][i].type != NONE) {
									count++;
								}
							}
							if (count == 1) {
								canMove = TRUE;
								break;
							}
						}
					}
					// ���ش�ֱֱ�ߴ�
					else {
						// �����ϴ�
						if (state.begr < state.endr) {
							for (int i = state.begr + 1; i < state.endr; i++) {
								if (map[i][state.begc].type != NONE) {
									count++;
								}
							}
							if (count == 1) {
								canMove = TRUE;
								break;
							}
						}
						else {
							// �����´�
							for (int i = state.begr - 1; i > state.endr; i--) {
								if (map[i][state.begc].type != NONE) {
									count++;
								}
							}
							if (count == 1) {
								canMove = TRUE;
								break;
							}
						}
					}
				}
			}
			break;
		case ��:
		case ��:
			if (map[state.begr][state.begc].type == RED)
			{
				if (map[state.begr][state.begc].overRiver == FALSE &&
					state.endr - state.begr == 1 && state.endc == state.begc)
				{ // �����û�й��� ��ֻ��������
					canMove = TRUE;
					break;
				}
				else if (map[state.begr][state.begc].overRiver == TRUE &&
						((state.endr == state.begr && abs(state.endc - state.begc) == 1) ||
						(state.endr - state.begr == 1 && state.endc == state.begc)))
				{ // ������Ѿ����� ���������������������ƶ���
					canMove = TRUE;
					break;
				}
			}
			else if (map[state.begr][state.begc].type == BLACK)
			{
				if (map[state.begr][state.begc].overRiver == FALSE &&
					state.begr - state.endr == 1 && state.endc == state.begc)
				{  // �����û�й��� ��ֻ��������
					canMove = TRUE;
					break;
				}
				else if (map[state.begr][state.begc].overRiver == TRUE &&
					((state.endr == state.begr && abs(state.endc - state.begc) == 1) ||
						(state.begr - state.endr == 1 && state.endc == state.begc)))
				{ // ����Ѿ����� �����������������������ƶ���
					canMove = TRUE;
					break;
				}
			}
			break;
		default:
			break;
		}
		if (canMove)
		{
			printf("canMove\n");

			/*	����ò��ƶ����Ǻ췽��˧�����Ǻڷ��Ľ���
				�ڸ���֮ǰ��¼���ƶ�ǰ��������Ϣ���ƶ����������Ϣ��
				�������Է�����֣�Ҳ������Ϊ��Ӯ������ */
			if (map[state.begr][state.begc].type == 1 && 
					map[state.begr][state.begc].id == 11) { // ����Ǻ췽˧

				redKingTop++;
				
				redKingStack[redKingTop].x = state.endr;
				redKingStack[redKingTop].y = state.endc;
				redKingStack[redKingTop].id = map[state.endr][state.endc].id;
				redKingStack[redKingTop].type = map[state.endr][state.endc].type;
				
			}
			else if (map[state.begr][state.begc].type == 0 && 
				map[state.begr][state.begc].id == 4) { // ����Ǻڷ���
				
				blackKingTop++;

				blackKingStack[blackKingTop].x = state.endr;
				blackKingStack[blackKingTop].y = state.endc;
				blackKingStack[blackKingTop].id = map[state.endr][state.endc].id;
				blackKingStack[blackKingTop].type = map[state.endr][state.endc].type;
				
			}
			
			printf("%d %d %d %d\n", state.begr, state.begc, state.endr, state.endc);

			// ��Ҫ�ƶ�������ѹ���ջ
			chessStack[top][0].x = state.begr;
			chessStack[top][0].y = state.begc;
			chessStack[top][0].id = map[state.begr][state.begc].id;
			chessStack[top][0].type = map[state.begr][state.begc].type;
			chessStack[top][0].overRiver = map[state.begr][state.begc].overRiver;
			
			// �������ƶ����λ��Ԫ��ѹ���ջ
			chessStack[top][1].x = state.endr;
			chessStack[top][1].y = state.endc;
			chessStack[top][1].id = map[state.endr][state.endc].id;
			chessStack[top][1].type = map[state.endr][state.endc].type;
			chessStack[top][1].overRiver = map[state.endr][state.endc].overRiver;
			
			top++; // ��ջָ���1
			
			// ֻ����ֺ�Ժڻ��ߺڳԺ�
			if ((map[state.begr][state.begc].type == RED && map[state.endr][state.endc].type == BLACK) || 
					(map[state.begr][state.begc].type == BLACK &&  map[state.endr][state.endc].type == RED))
			{
				eatStack[eatTop][0].chessId = map[state.begr][state.begc].id;
				eatStack[eatTop][0].chessType = map[state.begr][state.begc].type;
				eatStack[eatTop][1].chessId = map[state.endr][state.endc].id;
				eatStack[eatTop][1].chessType = map[state.endr][state.endc].type;

				eatTop++; // ��ջָ���1
			}
			

			// ����Ե������ӣ���������ӵ�����
			map[state.endr][state.endc].id = map[state.begr][state.begc].id;
			map[state.endr][state.endc].type = map[state.begr][state.begc].type;

			// ��������ƶ�����ԭ�����ӵ�λ����Ϊ��
			map[state.begr][state.begc].id = SPACE;
			map[state.begr][state.begc].type = NONE;

			// �����Ƿ����
			if (map[state.endr][state.endc].type == RED)
			{
				if (state.endr >= 5) // ����
					map[state.endr][state.endc].overRiver = TRUE;
				else // ����һ����Ϊ�˷�ֹ�ӺӶ԰�����
					map[state.endr][state.endc].overRiver = FALSE;
			}
			else if (map[state.endr][state.endc].type == BLACK)
			{
				if (state.endr <= 4) // ����
					map[state.endr][state.endc].overRiver = TRUE;
				else // ����һ����Ϊ�˷�ֹ�ӺӶ԰�����
					map[state.endr][state.endc].overRiver = FALSE;
			}

			// ������������ӵ���Ч
			canDrawStart = FALSE;
			// �ж��Ƿ���Ӯ�Ѿ�����
			judgeWinner();
			// ��һ��
			round = (round + 1) % 2;
			// ֪ͨ��ʱ��ˢ��
			CountTimeflag = TRUE;
		}
	}
}

extern double countDownTime;

// �������
void ChessRepent()
{
	if (Repent_the_move == 1 && top >= 1)
	{
		top--;
		countDownTime = 30;
		for (int i = 1; i >= 0; i--) {
			int x = chessStack[top][i].x;
			int y = chessStack[top][i].y;
			map[x][y].id = chessStack[top][i].id;
			map[x][y].type = chessStack[top][i].type;
			map[x][y].overRiver = chessStack[top][i].overRiver;
		}
		Repent_the_move = 0;
		round = !round;
	}
}


// �ж���һ����ʤ��
void judgeWinner()
{
	static int flag = 0; // ��֤��ͣһ��
	//printf("%d", Winner);
	if (eatTop > 0)
	{
		// ������Ե����Ǻ�˧�����ɫʤ
		if (eatStack[eatTop - 1][1].chessType == 1 &&
			eatStack[eatTop - 1][1].chessId == 11) {
			Winner = BLACK;
			printf("%s", ChessTypeName[Winner]);
			if (flag == 0) {
				flag++;
				
				pWinC node = (pWinC)malloc(sizeof(winC));
				time_t timep; 
				struct tm* p; 
				time(&timep); 
				p = localtime(&timep); //ȡ�õ���ʱ��	
				sprintf(node->nowTime, "%d-%d-%d %d:%d:%d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
				strcpy(node->Win, "Black");
				
				if (head == NULL)
				{
					head = node;
					head->next = NULL;
				}
				if (tail != NULL)
				{
					tail->next = node;
				}
				tail = node;
				tail->next = NULL;

				// ��׷��ģʽ��һ��txt�ļ�
				FILE* fp = fopen("winRecord.txt", "a+");
				if (fp == NULL)
				{
					printf("open file error!\n");
					return -1;
				}
				// ���ڵ�д���ļ�
				fprintf(fp, "%-20s %-10s\n", node->nowTime, node->Win);
				fclose(fp);
				
				int result = MessageBox(NULL, "��Ϸ�������ڷ�ʤ���Ƿ����¿�ʼ��", "��ʾ", MB_OKCANCEL);
				if (result == 1)
				{
					restart_the_game = 1;
				}
				if (result == 2)
				{
					pause_or_continue = 1; // ��Ϸ��ͣ
				}
				game_record = 0;
			}
			// ����
			eatTop = 0;
			blackKingTop = 0;
			redKingTop = 0;
			return;
		}
		// ������Ե����Ǻڽ������ɫʤ
		else if (eatStack[eatTop - 1][1].chessType == 0 &&
			eatStack[eatTop - 1][1].chessId == 4) {
			Winner = RED;
			printf("%s", ChessTypeName[Winner]);
			if (flag == 0) {
				flag++;

				pWinC node = (pWinC)malloc(sizeof(winC));
				time_t timep;
				struct tm* p;
				time(&timep);
				p = localtime(&timep); //ȡ�õ���ʱ��	
				sprintf(node->nowTime, "%d-%d-%d %d:%d:%d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
				strcpy(node->Win, "Red");

				if (head == NULL)
				{
					head = node;
					head->next = NULL;
				}
				if (tail != NULL)
				{
					tail->next = node;
				}
				tail = node;
				tail->next = NULL;

				// ��׷��ģʽ��һ��txt�ļ�
				FILE* fp = fopen("winRecord.txt", "a+");
				if (fp == NULL)
				{
					printf("open file error!\n");
					return -1;
				}
				// ���ڵ�д���ļ�
				fprintf(fp, "%-20s %-10s\n", node->nowTime, node->Win);
				fclose(fp);

				int result = MessageBox(NULL, "��Ϸ�������췽ʤ���Ƿ����¿�ʼ��", "��ʾ", MB_OKCANCEL);
				if (result == 1)
				{
					restart_the_game = 1;
				}
				if (result == 2)
				{
					pause_or_continue = 1; // ��Ϸ��ͣ
				}
				game_record = 0;  // ֹͣ¼��

			}

			eatTop = 0;
			blackKingTop = 0;
			redKingTop = 0;
			return;
		}
	}

	// ���û�б��Ե��������
	if (redKingStack[redKingTop].y == blackKingStack[blackKingTop].y)
	{
		int hasBlock = 0;
		//printf("Judge HasBlock\n");
		for (int i = redKingStack[redKingTop].x + 1; i <= blackKingStack[blackKingTop].x - 1; i++)
		{
			int x = i;
			int y = redKingStack[redKingTop].y;
			if (map[x][y].id != SPACE)
			{
				hasBlock = 1;
				break;
			}
		}
		//printf("%s", hasBlock ? "HasBlock" : "NoBlock");
		if (!hasBlock)
		{
			if (round == redRound)
			{
				Winner = BLACK;

				if (flag == 0) {
					flag++;
					int result = MessageBox(NULL, "��Ϸ�������ڷ�ʤ���Ƿ����¿�ʼ��", "��ʾ", MB_OKCANCEL);
					if (result == 1)
					{
						restart_the_game = 1;
					}
					if (result == 2)
					{
						pause_or_continue = 1; // ��Ϸ��ͣ
					}
					game_record = 0;
				}

				eatTop = 0;
				blackKingTop = 0;
				redKingTop = 0;
				return;
			}
			else
			{
				Winner = RED;

				if (flag == 0) {
					flag++;
					int result = MessageBox(NULL, "��Ϸ�������췽ʤ���Ƿ����¿�ʼ��", "��ʾ", MB_OKCANCEL);
					if (result == 1)
					{
						restart_the_game = 1;
					}
					if (result == 2)
					{
						pause_or_continue = 1; // ��Ϸ��ͣ
					}
					game_record = 0;
				}

				eatTop = 0;
				blackKingTop = 0;
				redKingTop = 0;
				return;
			}
		}
	}


	if (pause_or_continue == 0)
	{
		flag = 0;
		Winner = NONE;
	}
}