#include "MainFunction.h"
/**************************************
***   �˺���Ϊ������                  ***
***************************************/
void Main()
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("Chinese Chess Game");
    InitGraphics();
	SetFont("Times"); 
	SetPointSize(22);

	// ���ʼ��
	ChessInit();
	
	registerMouseEvent(MouseEventProcess);/*ע�������Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	startTimer(TIMER_BLINK500, mseconds500);/*500ms��ʱ������*/
	startTimer(TIMER_BLINK1000, mseconds1000);/*1000ms��ʱ������*/
	
	// ��ʼ���ն˴��ڣ����Ե�ʱ���
	//InitConsole();
	//show();
	
}
