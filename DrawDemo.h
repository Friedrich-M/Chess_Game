#ifndef ___drawdemo___h____
#define ___drawdemo___h____

#include "MainFunction.h"
typedef char* string;

// 绘制和处理菜单
void drawMenu();
// 显示菜单处理结果
void drawMenuResult();
// 按钮程序
void drawButtons();
// 清屏函数，provided in libgraphics
void DisplayClear(void);
// 计时器启动函数，provided in libgraphics
void startTimer(int id, int timeinterval);


#endif