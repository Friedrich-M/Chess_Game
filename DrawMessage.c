#include "ChessBoard.h"
/*********************************************
***   该文件实现所有提醒功能函数的绘制和记录   ***
**********************************************/

#define ChessCircle 0.2
#define delta 0.03

extern int round;
const char* ChessTypeName[2] = { "BLACK", "RED" };
const char* RoundType[2] = { "BLACK ROUND", "RED ROUND" };
extern const char* chessName[];
extern ChessEaten eatStack[MAXSTEP][2];
extern step eatTop;
extern double countDownTime;
extern int Winner;
extern Chess startChess;

// 绘制这是哪一方在下棋
void DrawWhichRound()
{
	double w = GetWindowWidth(), h = GetWindowHeight();
	double x = w / 1.55, y = h / 1.15;
	SetPointSize(20);
	MovePen(x - TextStringWidth(RoundType[round]) / 2, y - GetFontAscent() / 2);
	if (round == RED) {
		SetPenColor("Red");
		DrawTextString(RoundType[round]);
	}
	else if (round == BLACK) {
		SetPenColor("Black");
		DrawTextString(RoundType[round]);
	}
}


// 绘制时间是否耗尽
void DrawIfTimeUp()
{
	double x = 4 * GRID_SIZE + INTERVAL;
	double y = GetWindowHeight() / 1.1;
	SetPenColor("Red");
	char *s = (countDownTime < 1) ? "TIME UP!!" : "";
	MovePen(x - TextStringWidth(s) / 2, y - GetFontAscent() / 2);
	DrawTextString(s);
}


// 绘制吃棋子的提示
void DrawEatenChess()
{
	if (eatTop == 0) return;
	int Top = eatTop - 1;
	double w = GetWindowWidth(), h = GetWindowHeight();
	double x = w / 1.2, y = h / 1.15;
	SetPointSize(20);
	// 棋子id
	char *chess1_id = chessName[eatStack[Top][0].chessId];
	char *chess2_id = chessName[eatStack[Top][1].chessId];
	// 棋子种类
	char *chess1_type = ChessTypeName[eatStack[Top][0].chessType];
	char *chess2_type = ChessTypeName[eatStack[Top][1].chessType];
	// 异常检测
	if (chess1_type == chess2_type || chess1_id == chess2_id) return ;
	//MovePen(x - TextStringWidth(chess1_type) / 2, y - GetFontAscent() / 2);
	// 绘制
	MovePen(x, y);
	DrawChessInMenu(chess1_type, chess1_id);
	chosePenColor("eat");
	DrawTextString("  eat  ");
	DrawChessInMenu2(chess2_type, chess2_id);
	
}

// 根据下棋方选择画笔颜色
void chosePenColor(char *chess_type)
{
	if (strcmp(chess_type, "RED") == 0)
		SetPenColor("Red");
	else if (strcmp(chess_type, "BLACK") == 0)
		SetPenColor("Black");
	else
		SetPenColor("Blue");
}

void DrawChessInMenu(char* chess_type, char *chess_id)
{
	double x, y;
	chosePenColor(chess_type);
	x = GetCurrentX(), y = GetCurrentY();
	StartFilledRegion(0.);
	DrawCenteredCircle(x, y, ChessCircle);
	EndFilledRegion();
	SetFont("楷体");
	SetPointSize(20);
	DrawCenteredCircle(x, y, ChessCircle - delta);
	MovePen(x - TextStringWidth(chess_id) / 2, y - GetFontAscent() / 2);
	DrawTextString(chess_id);
}

void DrawChessInMenu2(char* chess_type, char* chess_id)
{
	double x, y;
	chosePenColor(chess_type);
	x = GetCurrentX(), y = GetCurrentY();
	StartFilledRegion(0.);
	DrawCenteredCircle(x + TextStringWidth(chess_id) / 2, y + GetFontAscent() / 2, ChessCircle);
	EndFilledRegion();
	SetFont("楷体");
	SetPointSize(20);
	DrawCenteredCircle(x + TextStringWidth(chess_id) / 2, y + GetFontAscent() / 2, ChessCircle - delta);
	MovePen(x, y);
	DrawTextString(chess_id);
}

// 画胜利一方
void DrawWinner()
{
	double x = 4 * GRID_SIZE + INTERVAL;
	double y = GetWindowHeight() / 1.1;
	if (Winner == RED) {
		SetPenColor("Red");
		MovePen(x - TextStringWidth("RED WIN!!!") / 2, y - GetFontAscent() / 2);
		DrawTextString("RED WIN!!");
	}
	else if (Winner == BLACK) {
		SetPenColor("Black");
		MovePen(x - TextStringWidth("BLACK WIN!!!") / 2, y - GetFontAscent() / 2);
		DrawTextString("BLACK WIN!!");
	}
	else {
		SetPenColor("White");
		DrawBox(x - TextStringWidth("           ") / 2, y - GetFontAscent() / 2,
			TextStringWidth("        "), GetFontAscent());
	}
}


// 当没有轮到自己在下棋时，输出提醒
void DrawWhetherRound()
{
	double x = 4 * GRID_SIZE + INTERVAL;
	double y = GetWindowHeight() / 1.1;
	SetPenColor("Orange");
	if (startChess.type == RED && round == BLACK ||
		startChess.type == BLACK && round == RED) 
	{
		MovePen(x - TextStringWidth("Not Your Round") / 2, y - GetFontAscent() / 2);
		DrawTextString("Not Your Round");
	}
}


// 画将军标志
void DrawAttackKing()
{
	double w = GetWindowWidth(), h = GetWindowHeight();
	double x = w / 5, y = h / 1.1;
	SetPointSize(20);
	char* Message = "将军";
	MovePen(x - TextStringWidth(RoundType[round]) / 2, y - GetFontAscent() / 2);
	if (checkAttackKing() == 1) { // 红棋被将军
		SetPenColor("Red");
		DrawTextString(Message);
	}
	else if (checkAttackKing() == 2) { //黑棋被将军
		SetPenColor("Black");
		DrawTextString(Message);
	}
}

// 如果不是自己下棋的回合，绘制提醒
extern Chess startChess;
extern bool canDrawStart;
void StartChessReminderProcess()
{
	if (startChess.id == -1 || canDrawStart == FALSE)
		return;
	chosePenColor(ChessTypeName[startChess.type]);
	SetPenSize(3);
	int row = startChess.x;
	int col = startChess.y;
	DrawCenteredCircle(map[row][col].x, map[row][col].y, ChessCircle - 0.01);
}
