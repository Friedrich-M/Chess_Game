#include "ChessBoard.h"
#include <time.h>
/*********************************************
***   此函数用于实现计时器的触发和绘制         ***
**********************************************/

#define MAXTIME 30
double countDownTime = MAXTIME;
extern int pause_or_continue;
extern int	start_game_end;

time_t t; //记录时间
static bool isDisplayCountDown = TRUE;
bool isBlink = FALSE;
bool canDisplayClear = TRUE;

bool CountTimeflag = FALSE;


// 计时器触发函数
void TimerEventProcess(int timerID)
{
	static int flag = 0;
	// 每次重开时间重置
	if (flag != start_game_end)
	{
		flag = start_game_end;
		countDownTime = 30;
	}
	switch (timerID)
	{	
	case TIMER_BLINK1000: /*1000ms光标闪烁定时器*/ 
		 // 进入下一轮执棋方执棋，倒计时重置
		if (CountTimeflag) 
			countDownTime = MAXTIME;
		CountTimeflag = FALSE; // 重新初始化为FALSE
		if (!isBlink || countDownTime < 0.5 || pause_or_continue)  // 倒计时暂停或结束
		{
			return;
		}
		//erasemode = GetEraseMode();
		//SetEraseMode(isDisplayCountDown);
		canDisplayClear = FALSE;
		double w = GetWindowWidth(), h = GetWindowHeight();
		double x = w / 1.3, y = h / 1.15;		
		if (isDisplayCountDown)
			DrawCountDown(x, y);
		else
		{
			ClearCountDown(x, y);
		}			
		countDownTime -= 0.5;
		//SetEraseMode(erasemode);
		isDisplayCountDown = !isDisplayCountDown;
		canDisplayClear = TRUE;
		break;

	default:
		break;
	}
}

// 绘制计时器
void DrawCountDown(double x, double	y)
{
	SetPenSize(2);
	if (countDownTime > 10)
		SetPenColor("Blue");
	else 
		SetPenColor("Red");
	char buff[10] = { -1 };
	itoa(countDownTime, buff, 10);//将a以10进制的形式写入buff中
	if (countDownTime > 0) {
		DrawCenteredCircle(x, y, 0.3);
		MovePen(x - TextStringWidth(buff) / 2, y - GetFontAscent() / 2);
		DrawTextString(buff);
	}
}

// 清除计时器
void ClearCountDown(double x, double y)
{
	SetPenColor("White");
	StartFilledRegion(0.);
	DrawCenteredCircle(x, y, 0.31);
	EndFilledRegion();
}
