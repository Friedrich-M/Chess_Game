#include "ChessBoard.h"
/*********************************************
***   此文件中的三个函数用于绘制游戏界面按钮    ***
**********************************************/

static int playBackMyFlag = 0; // 判别到达栈顶
static double winwidth, winheight;   // 窗口尺寸
extern int   Repent_the_move;  // 是否重新走棋
int   playBackAccount = 0;  // 回放棋谱计数
extern int playBackTop; // 棋盘回放记录的栈顶元素


// 程序游戏界面的按钮程序
void DrawChessButtons()
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth / 1.5;
	double y = winheight - h/1.5;
	double w = winwidth / 5; // 控件宽度

	// 游戏开始按钮
	if (button(GenUIID(0), x, y - 3 * h, w, h, start_game_end ? "End the Game" : "Start the Game"))
		start_game_end = start_game_end ? 0 : 1;
	// 游戏暂停按钮
	if (button(GenUIID(0), x, y - 5 * h, w, h, pause_or_continue ? "Continue" : "Pause"))
		pause_or_continue = !pause_or_continue;
	// 悔棋按钮
	if (button(GenUIID(0), x, y - 7 * h, w, h, "Repent"))
		Repent_the_move = 1;
	// 游戏录制按钮
	if (button(GenUIID(0), x, y - 9 * h, w, h, game_record ? "End Record" : "Start Record"))
		game_record = !game_record;
	// 程序退出按钮
	if (button(GenUIID(0), x, y - 11 * h, w, h, "Click to Quit"))
	{
		int result = MessageBox(NULL, "您确定要退出游戏吗?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			exit(0);
		}
	}
}

// 回放时的按钮程序
void DrawPlayBackButtons(int * playback_or_exit)
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth / 1.5;
	double y = winheight - h / 1.5;
	double w = winwidth / 5; // 控件宽度

	
	// 下一步
	if (button(GenUIID(0), x, y - 4 * h, w, h, playBackMyFlag ? "PlayBack End" : "Next"))
	{
		if (playBackAccount < playBackTop)
		{
			printf("%d %d\n", playBackAccount, playBackTop);
			PlayBackStackPrint(playBackAccount);
			playBackAccount++;
		}
		else
		{
			int result = MessageBox(NULL, "对局回放已经结束", "Tips", MB_OKCANCEL);
			playBackMyFlag = 1;
		}
	}
	// 退出对局回放按钮
	if (button(GenUIID(0), x, y - 6 * h, w, h, "End PlayBack"))
	{
	
		int result = MessageBox(NULL, "您确定要退出对局回放吗?", "Tips", MB_OKCANCEL);
		// 按下确定键，对局回放才会退出
		if (result == 1)
		{
			// 退出对局回放并将重置flag
			*playback_or_exit = 0;
			playBackMyFlag = 0;
		}
	}
	// 程序退出按钮
	if (button(GenUIID(0), x, y - 8 * h, w, h, "Click to Quit"))
	{ 
		int result = MessageBox(NULL, "您确定要退出游戏吗?", "Tips", MB_OKCANCEL);
		// 只有按下确定键，程序才会结束
		if (result == 1)
		{
			exit(0);
		}
	}
}


// 棋谱展示时的按钮程序
void DrawManualButtons(int *mode, int *manual)
{
	usePredefinedColors(3);
	SetPointSize(22);
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth / 1.5;
	double y = winheight - h / 1.5;
	double w = winwidth / 5; // 控件宽度


	// 七星聚会棋谱
	if (button(GenUIID(0), x, y - 2 * h, w, h, "七星聚会"))
	{
		int result = MessageBox(NULL, "七星聚会”是清代起广泛流传于民间的四大江湖名局之一。清代出版的著名棋谱几乎都刊有此局，只是局名略有差异：其中《竹香斋象戏谱里》改名为“七星拱斗”，《心武残编》中题之为“七星同庆”，《渊深海阔》中起名为“七星曜彩”。由于此局图势中红黑双方各有七枚棋子，故局名形象地以“七星”喻之。本局构思精巧，陷阱四伏。乍一看，红方似有胜机，棋摊前的“初生牛犊”常因求胜心切，误中设局人的圈套，故江湖艺人多以此局为谋生的法宝。", "棋局介绍", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 1;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// 蚯蚓降龙棋谱
	if (button(GenUIID(0), x, y - 4 * h, w, h, "蚯蚓降龙"))
	{
		int result = MessageBox(NULL, "“蚯蚓降龙”是三卒单缺象对双车一兵的残局，原谱作者把双车比拟为大海中的蛟龙，而把三个小卒形容为行动缓慢、力量弱小的蚯蚓。由于特定的局势，双车被两外小卒牵制，不得随意活动，黑方得以巧运另一小卒和灵活地变换士象的位置，苦战成和，这是弱子战和强子一个典型残局。蚯蚓降服蛟龙，多么形象的比喻！《竹香斋象戏谱》有“尺蚓降龙”，与本局乃同局异名。", "棋局介绍", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 2;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// 野马操田棋谱
	if (button(GenUIID(0), x, y - 6 * h, w, h, "野马操田"))
	{
		int result = MessageBox(NULL, "“野马操田”是大型的著名古局之一，与“七星聚会”、“蚯蚓降龙”、“千里独行”局齐名，并称为四大江湖排局，其变化十分复杂和深奥。由于它是双车马对双车卒的典型残局，实用价值很大，因此研究此局的棋手很多。原谱为红先和，但经研究，认为此局无论如何变化，只要黑方走出官着，结论应是红先黑胜。", "棋局介绍", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 3;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// 千里独行棋谱
	if (button(GenUIID(0), x, y - 8 * h, w, h, "千里独行"))
	{
		int result = MessageBox(NULL, "“千里独行”其结尾棋势是一车大战三兵。《心武残篇》以其单车进退纵横，题为“单枪赵云”。此局的另一特点是：双方交锋过程中，车、马、兵（卒）和将（帅）士（仕）、象（相），都能各尽所能，充分发挥各自的攻防战斗力，即所谓“将、士、象柔中有刚，车、马、兵攻不忘守”。它是研究残局中的解着、停着（等着）的好材料。", "棋局介绍", MB_OKCANCEL);
		if (result == 1)
		{
			*mode = 4;
		}
		else if (result == 2)
		{
			return;
		}
	}
	// 退出对局回放按钮
	if (button(GenUIID(0), x, y - 10 * h, w, h, "退出棋谱欣赏"))
	{
		int result = MessageBox(NULL, "您确定要退出经典棋谱欣赏吗?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			*manual = 0;
		}
		else if (result == 2)
		{
			return;
		}
	}
		
}
