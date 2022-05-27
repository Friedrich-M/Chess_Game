#include "ChessBoard.h"
#include <time.h>
/*********************************************************
***   此文件函数用于实现棋子的移动、悔棋、胜者判定等功能     ***
**********************************************************/

extern const char* ChessTypeName[2];
extern int restart_the_game;
extern bool CountTimeflag;
int Repent_the_move = 0;
int Winner = NONE;
bool canDrawStart = TRUE;

// 初始化状态
State  state = { -1, -1, -1, -1, BEGIN };

// 初始化开始移动的棋子属性
Chess startChess = { -1, -1, -1, -1, FALSE };

// 创建红棋帅和黑棋将的堆栈
Chess redKingStack[MAXSTEP] = {11, 1, 0, 4, 0};
step redKingTop = 0;
Chess blackKingStack[MAXSTEP] = {4, 0, 9, 4, 0};
step blackKingTop = 0;


// 创建堆栈记录棋子走过的路
StackObj chessStack[MAXSTEP][2];
step top = 0;
// 创建堆栈记录发生吃棋时的双方棋子信息
ChessEaten eatStack[MAXSTEP][2] = {-1};
step eatTop = 0;

// 记录胜局的链表的头指针和尾指针
winC *head = NULL, *tail = NULL;

// 根据象棋规则，红棋先走，所以round初始化为redRoubd
int round = redRound;

// 鼠标消息回调函数
void MouseEventProcess(int x, int y, int button, int event) 
{
	uiGetMouse(x, y, button, event); // GUI获取鼠标
	
	double mx, my;
	mx = ScaleXInches(x); /*pixels --> inches*/
	my = ScaleYInches(y);

	//printf("%f %f\n", mx, my);
	switch (event) { // 鼠标事件
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON && start_game_end == 1) {
			// 通过鼠标坐标得到点击的数组的下标
			int col, row;
			col = (mx - INTERVAL) / GRID_SIZE;
			if (my > INTERVAL + 4 * GRID_SIZE + RiverWidth / 2)
				row = (my - INTERVAL - RiverWidth) / GRID_SIZE + 1;
			else
				row = (my - INTERVAL) / GRID_SIZE;

			//printf("%f %f\n", mx, my);

			// 下标校准
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
			
			// 如果是第一次点击，则记录第一个点击的棋子属性
			startChess.x = row;
			startChess.y = col;
			startChess.id = map[row][col].id;
			startChess.type = map[row][col].type;

			if (state.state == BEGIN && map[row][col].type == round)
			{
				state.begr = row;
				state.begc = col;
				//if (!((state.begc == state.endr) && (state.endr == state.endr)))
				//	// 只有当前后两次点击的不是同一个棋子时，才会变化state
				state.state = END;
			}
			else if (state.state == END && (map[row][col].id == SPACE || map[row][col].type == !round))
			{
				state.endr = row;
				state.endc = col;
				state.state = BEGIN;
			}
			if (pause_or_continue == 0)
				// 如果该状态不是暂停状态，则棋子移动
				chessMove();
		}
	}
	if (state.state == BEGIN)
		state.begc = state.begr = state.endc = state.endr = -1;
	display();
}

// 判断起始点和终点之间是否有障碍物
int hasBlock(pState state)
{
	int flag = 0;
	if (state->begr != state->endr)
	{
		// 找出begr和endr的最小值和最大值
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


// 移动棋子
void chessMove()
{
	printf("start(%d %d) end(%d %d)\n", state.begr, state.begc, state.endr, state.endc);
	bool canMove = FALSE;
	
	// 什么情况下能移动棋子
	if (!(state.begr == state.endr && state.begc == state.endc) && //点击的不是同一个棋子
		state.endr != -1 && state.begr != -1 && // 下标必须合法
		map[state.begr][state.begc].id != SPACE && // 没有棋子不能移动
		map[state.begr][state.begc].id != map[state.endr][state.endc].id //不能自己吃自己家的棋子
		 && round == map[state.begr][state.begc].type) // 当前轮到自己的round
	{
		//printf("%d", map[state.begr][state.begc].id);
		switch (map[state.begr][state.begc].id)
		{
		case 車:
		case 俥:
			if ((state.begr == state.endr || state.begc == state.endc) &&
				map[state.begr][state.begc].type != map[state.endr][state.endc].type) // 车只能走直线并且吃的棋子不能是己方的
			{
				if (!hasBlock(&state))
					// 起始点和结束点之间没有棋子阻碍 
				{
					canMove = TRUE;
					break;
				}
			}
			break;
		case 馬:
		case 马:
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
		case 象:
		case 相:
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
		case 士:
		case 仕:
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
		case 将:
		case 帥:
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
		case 砲:
		case 炮:
			if (map[state.endr][state.endc].type == NONE)
			{
				if (state.begr == state.endr || state.begc == state.endc) // 沿着行列方向走
				{
					// 路径上没有棋子
					if (!hasBlock(&state))
						// 起始点和结束点之间没有棋子阻碍 
					{
						canMove = TRUE;
						break;
					}
				}
			}
			else if (map[state.endr][state.endc].type == !round) { // 炮终点必须是对面的棋子
				// 炮只能沿直线打
				if (state.begc == state.endc || state.begr == state.endr) {
					int count = 0; // 路径上有且仅有一个棋子作为跳板
					// 炮沿水平直线打
					if (state.begr == state.endr) {
						// 炮向左打
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
							// 炮向右打
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
					// 炮沿垂直直线打
					else {
						// 炮向上打
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
							// 炮向下打
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
		case 卒:
		case 兵:
			if (map[state.begr][state.begc].type == RED)
			{
				if (map[state.begr][state.begc].overRiver == FALSE &&
					state.endr - state.begr == 1 && state.endc == state.begc)
				{ // 如果兵没有过河 兵只能向上走
					canMove = TRUE;
					break;
				}
				else if (map[state.begr][state.begc].overRiver == TRUE &&
						((state.endr == state.begr && abs(state.endc - state.begc) == 1) ||
						(state.endr - state.begr == 1 && state.endc == state.begc)))
				{ // 如果兵已经过河 兵可以向左右两个方向移动的
					canMove = TRUE;
					break;
				}
			}
			else if (map[state.begr][state.begc].type == BLACK)
			{
				if (map[state.begr][state.begc].overRiver == FALSE &&
					state.begr - state.endr == 1 && state.endc == state.begc)
				{  // 如果兵没有过河 兵只能向下走
					canMove = TRUE;
					break;
				}
				else if (map[state.begr][state.begc].overRiver == TRUE &&
					((state.endr == state.begr && abs(state.endc - state.begc) == 1) ||
						(state.begr - state.endr == 1 && state.endc == state.begc)))
				{ // 如果已经过河 兵可以向下左右三个方向移动的
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

			/*	如果该步移动的是红方的帅或者是黑方的将，
				在更新之前记录下移动前的棋子信息和移动后的棋子信息，
				后续可以分析棋局，也可以作为输赢的依据 */
			if (map[state.begr][state.begc].type == 1 && 
					map[state.begr][state.begc].id == 11) { // 如果是红方帅

				redKingTop++;
				
				redKingStack[redKingTop].x = state.endr;
				redKingStack[redKingTop].y = state.endc;
				redKingStack[redKingTop].id = map[state.endr][state.endc].id;
				redKingStack[redKingTop].type = map[state.endr][state.endc].type;
				
			}
			else if (map[state.begr][state.begc].type == 0 && 
				map[state.begr][state.begc].id == 4) { // 如果是黑方将
				
				blackKingTop++;

				blackKingStack[blackKingTop].x = state.endr;
				blackKingStack[blackKingTop].y = state.endc;
				blackKingStack[blackKingTop].id = map[state.endr][state.endc].id;
				blackKingStack[blackKingTop].type = map[state.endr][state.endc].type;
				
			}
			
			printf("%d %d %d %d\n", state.begr, state.begc, state.endr, state.endc);

			// 将要移动的棋子压入堆栈
			chessStack[top][0].x = state.begr;
			chessStack[top][0].y = state.begc;
			chessStack[top][0].id = map[state.begr][state.begc].id;
			chessStack[top][0].type = map[state.begr][state.begc].type;
			chessStack[top][0].overRiver = map[state.begr][state.begc].overRiver;
			
			// 将棋子移动后的位置元素压入堆栈
			chessStack[top][1].x = state.endr;
			chessStack[top][1].y = state.endc;
			chessStack[top][1].id = map[state.endr][state.endc].id;
			chessStack[top][1].type = map[state.endr][state.endc].type;
			chessStack[top][1].overRiver = map[state.endr][state.endc].overRiver;
			
			top++; // 堆栈指针加1
			
			// 只会出现红吃黑或者黑吃红
			if ((map[state.begr][state.begc].type == RED && map[state.endr][state.endc].type == BLACK) || 
					(map[state.begr][state.begc].type == BLACK &&  map[state.endr][state.endc].type == RED))
			{
				eatStack[eatTop][0].chessId = map[state.begr][state.begc].id;
				eatStack[eatTop][0].chessType = map[state.begr][state.begc].type;
				eatStack[eatTop][1].chessId = map[state.endr][state.endc].id;
				eatStack[eatTop][1].chessType = map[state.endr][state.endc].type;

				eatTop++; // 堆栈指针加1
			}
			

			// 如果吃掉了棋子，则更新棋子的类型
			map[state.endr][state.endc].id = map[state.begr][state.begc].id;
			map[state.endr][state.endc].type = map[state.begr][state.begc].type;

			// 如果可以移动，则原来棋子的位置设为空
			map[state.begr][state.begc].id = SPACE;
			map[state.begr][state.begc].type = NONE;

			// 更新是否过河
			if (map[state.endr][state.endc].type == RED)
			{
				if (state.endr >= 5) // 过河
					map[state.endr][state.endc].overRiver = TRUE;
				else // 加这一步是为了防止从河对岸回来
					map[state.endr][state.endc].overRiver = FALSE;
			}
			else if (map[state.endr][state.endc].type == BLACK)
			{
				if (state.endr <= 4) // 过河
					map[state.endr][state.endc].overRiver = TRUE;
				else // 加这一步是为了防止从河对岸回来
					map[state.endr][state.endc].overRiver = FALSE;
			}

			// 不画出点击棋子的特效
			canDrawStart = FALSE;
			// 判断是否输赢已经产生
			judgeWinner();
			// 下一轮
			round = (round + 1) % 2;
			// 通知计时器刷新
			CountTimeflag = TRUE;
		}
	}
}

extern double countDownTime;

// 悔棋操作
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


// 判断哪一方是胜者
void judgeWinner()
{
	static int flag = 0; // 保证暂停一次
	//printf("%d", Winner);
	if (eatTop > 0)
	{
		// 如果被吃掉的是红帅，则黑色胜
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
				p = localtime(&timep); //取得当地时间	
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

				// 以追加模式打开一个txt文件
				FILE* fp = fopen("winRecord.txt", "a+");
				if (fp == NULL)
				{
					printf("open file error!\n");
					return -1;
				}
				// 将节点写入文件
				fprintf(fp, "%-20s %-10s\n", node->nowTime, node->Win);
				fclose(fp);
				
				int result = MessageBox(NULL, "游戏结束，黑方胜，是否重新开始？", "提示", MB_OKCANCEL);
				if (result == 1)
				{
					restart_the_game = 1;
				}
				if (result == 2)
				{
					pause_or_continue = 1; // 游戏暂停
				}
				game_record = 0;
			}
			// 重置
			eatTop = 0;
			blackKingTop = 0;
			redKingTop = 0;
			return;
		}
		// 如果被吃掉的是黑将，则红色胜
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
				p = localtime(&timep); //取得当地时间	
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

				// 以追加模式打开一个txt文件
				FILE* fp = fopen("winRecord.txt", "a+");
				if (fp == NULL)
				{
					printf("open file error!\n");
					return -1;
				}
				// 将节点写入文件
				fprintf(fp, "%-20s %-10s\n", node->nowTime, node->Win);
				fclose(fp);

				int result = MessageBox(NULL, "游戏结束，红方胜，是否重新开始？", "提示", MB_OKCANCEL);
				if (result == 1)
				{
					restart_the_game = 1;
				}
				if (result == 2)
				{
					pause_or_continue = 1; // 游戏暂停
				}
				game_record = 0;  // 停止录制

			}

			eatTop = 0;
			blackKingTop = 0;
			redKingTop = 0;
			return;
		}
	}

	// 如果没有被吃掉，则继续
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
					int result = MessageBox(NULL, "游戏结束，黑方胜，是否重新开始？", "提示", MB_OKCANCEL);
					if (result == 1)
					{
						restart_the_game = 1;
					}
					if (result == 2)
					{
						pause_or_continue = 1; // 游戏暂停
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
					int result = MessageBox(NULL, "游戏结束，红方胜，是否重新开始？", "提示", MB_OKCANCEL);
					if (result == 1)
					{
						restart_the_game = 1;
					}
					if (result == 2)
					{
						pause_or_continue = 1; // 游戏暂停
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