#include "MainFunction.h"
/**************************************
***   此函数为主函数                  ***
***************************************/
void Main()
{
	// 初始化窗口和图形系统
	SetWindowTitle("Chinese Chess Game");
    InitGraphics();
	SetFont("Times"); 
	SetPointSize(22);

	// 棋初始化
	ChessInit();
	
	registerMouseEvent(MouseEventProcess);/*注册鼠标消息回调函数*/
	registerTimerEvent(TimerEventProcess);/*注册定时器消息回调函数*/
	startTimer(TIMER_BLINK500, mseconds500);/*500ms定时器触发*/
	startTimer(TIMER_BLINK1000, mseconds1000);/*1000ms定时器触发*/
	
	// 初始化终端窗口，调试的时候打开
	//InitConsole();
	//show();
	
}
