#ifndef ___drawdemo___h____
#define ___drawdemo___h____

#include "MainFunction.h"
typedef char* string;

// ���ƺʹ���˵�
void drawMenu();
// ��ʾ�˵�������
void drawMenuResult();
// ��ť����
void drawButtons();
// ����������provided in libgraphics
void DisplayClear(void);
// ��ʱ������������provided in libgraphics
void startTimer(int id, int timeinterval);


#endif