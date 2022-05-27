#include "ChessBoard.h"
#include <time.h>
/*********************************************
***   �˺�������ʵ�ּ�ʱ���Ĵ����ͻ���         ***
**********************************************/

#define MAXTIME 30
double countDownTime = MAXTIME;
extern int pause_or_continue;
extern int	start_game_end;

time_t t; //��¼ʱ��
static bool isDisplayCountDown = TRUE;
bool isBlink = FALSE;
bool canDisplayClear = TRUE;

bool CountTimeflag = FALSE;


// ��ʱ����������
void TimerEventProcess(int timerID)
{
	static int flag = 0;
	// ÿ���ؿ�ʱ������
	if (flag != start_game_end)
	{
		flag = start_game_end;
		countDownTime = 30;
	}
	switch (timerID)
	{	
	case TIMER_BLINK1000: /*1000ms�����˸��ʱ��*/ 
		 // ������һ��ִ�巽ִ�壬����ʱ����
		if (CountTimeflag) 
			countDownTime = MAXTIME;
		CountTimeflag = FALSE; // ���³�ʼ��ΪFALSE
		if (!isBlink || countDownTime < 0.5 || pause_or_continue)  // ����ʱ��ͣ�����
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

// ���Ƽ�ʱ��
void DrawCountDown(double x, double	y)
{
	SetPenSize(2);
	if (countDownTime > 10)
		SetPenColor("Blue");
	else 
		SetPenColor("Red");
	char buff[10] = { -1 };
	itoa(countDownTime, buff, 10);//��a��10���Ƶ���ʽд��buff��
	if (countDownTime > 0) {
		DrawCenteredCircle(x, y, 0.3);
		MovePen(x - TextStringWidth(buff) / 2, y - GetFontAscent() / 2);
		DrawTextString(buff);
	}
}

// �����ʱ��
void ClearCountDown(double x, double y)
{
	SetPenColor("White");
	StartFilledRegion(0.);
	DrawCenteredCircle(x, y, 0.31);
	EndFilledRegion();
}
