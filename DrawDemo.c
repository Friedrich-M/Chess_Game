#include "DrawDemo.h"
/*********************************************
***   此文件函数用于绘制主页面的内容           ***
**********************************************/

int	start_game_end = 0;    // 游戏开始或者结束
int restart_the_game = 0;  // 游戏是否重新开始
int game_record = 0;	   // 是否在录制对局
int	pause_or_continue = 0; // 暂停或者继续
int playback_or_exit = 0;  // 对局回放
int manual = 0;

static double winwidth, winheight;   // 窗口尺寸
static int    show_more_buttons = 0; // 显示更多按钮

static char* menuListGame[] = { "Game", // 函数运行菜单栏
	"Start | Ctrl-A",  // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
	"End | Ctrl-Z",
	"Pause | Ctrl-P",
	"Restart | Ctrl-R",
	"Exit | Ctrl-E" };

static char* menuListRecord[] = { "Record", // 对局记录和对局回放菜单栏
	"Begin Record | Ctrl-C",
	"Begin Playback | Ctrl-B" };

static char* menuListHelp[] = { "Help",  // 帮助菜单栏
	"Show More | Ctrl-M",
	"Basic Rules",
	"Rules of Move Chess",
	"About the Program"};

static char* menuListShortcutKeys[] = {"Keys", // 快捷键菜单栏
	"Start | Ctrl-A", 
	"End | Ctrl-Z",
	"Pause | Ctrl-P",
	"Restart | Ctrl-R",
	"Exit | Ctrl-E", 
	"Begin Record | Ctrl-C",
	"End Playback | Ctrl-B", 
};

static char* selectedLabel = NULL;
static double fH, x, y, h, w, wlist, xindent;

// 顶部菜单栏
void drawMenu()
{
	usePredefinedColors(4);
	
	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	fH = GetFontHeight();
	x = 0; 
	y = winheight;
	h = fH * 1.5; // 控件高度
	w = TextStringWidth(menuListRecord[0]) * 1.4; // 控件宽度
	wlist = TextStringWidth(menuListRecord[2]) * 1.3;
	xindent = winheight / 20; // 缩进
	
	int selection;

	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	
	// Game Tool菜单
	menuListGame[3] = pause_or_continue ? "Continue | Ctrl-O" : "Pause | Ctrl-P";
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListGame, sizeof(menuListGame) / sizeof(menuListGame[0]));
	if (selection > 0) selectedLabel = menuListGame[selection];
	if (selection == 1)
		start_game_end = 1;
	if (selection == 2)
		start_game_end = 0;
	if (selection == 3)
		pause_or_continue = !pause_or_continue;
	if (selection == 4)
		restart_the_game = 1;
	if (selection == 5)
		exit(-1); // choose to exit

	// Record Tool菜单
	menuListRecord[1] = game_record ? "End Record | Ctrl-C" : "Begin Record | Ctrl-C";
	menuListRecord[2] = playback_or_exit ? "End Playback | Ctrl-B" : "Begin Playback | Ctrl-B";
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListRecord, sizeof(menuListRecord) / sizeof(menuListRecord[0]));
	if (selection > 0) selectedLabel = menuListRecord[selection];
	if (selection == 1)
		game_record = !game_record;
	if (selection == 2)
		playback_or_exit = !playback_or_exit;

	// Help 菜单
	menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection > 0) selectedLabel = menuListHelp[selection];
	if (selection == 1)
		show_more_buttons = !show_more_buttons;
	if (selection == 2)
		MessageBox(NULL, "基本玩法: 中国象棋的游戏用具由棋盘和棋子组成，对局时，由执红棋的一方先走，双方轮流各走一招，直至分出胜、负、和，对局即终了。轮到走棋的一方，将某个棋子从一个交叉点走到另一个交叉点，或者吃掉对方的棋子而占领其交叉点，都算走了一着。双方各走一着，称为一个回合。\n", "游戏玩法介绍", MB_OK);
	if (selection == 3)
		MessageBox(NULL, "行棋规则: 棋子行棋规则帅/将移动范围：只能在九宫内移动移动规则：每一步只可以水平或垂直移动一点特殊规则：帅和将不准在同一直线上直接对面（中间无棋子），如一方已先占据位置，则另一方必须回避，否则就算输仕/士移动范围：只能在九宫内移动移动规则：每一步只可以沿对角线方向移动一点相/象移动范围：河界的一侧移动规则：每一步只可以沿对角线方向移动两点，可使用汉字中的田字形象地表述：田字格的对角线，俗称相（象）走田字。当相（象）行走路线中，即田字中心有棋子时（无论己方或是对方棋子），则不允许走过去，俗称：塞相（象）眼。馬移动范围：任何位置移动规则：每一步只可以水平或垂直移动一点，再按对角线方面向左或者右移动。可使用汉字中的日字来形容马的行走方式，俗称：马走日字（斜对角线）。当馬行走时，第一步直行或横行处有别的棋子（无论己方或是对方棋子）挡住，则不许走过去，俗称：蹩马腿。車移动范围：任何位置移动规则：可以水平或垂直方向移动任意个无阻碍的点炮/砲移动范围：任何位置移动规则：移动起来和车很相似，但它必须跳过一个棋子来吃掉对方棋子。兵/卒移动范围：任何位置移动规则：过河界前，每步只能向前移动一点。过河界后，增加了向左右移动的能力，兵（卒）不允许向后移动。\n", "行棋规则介绍", MB_OK);
	if (selection == 4)
		MessageBox(NULL, "C大程大作业：象棋游戏\n版本：1.0.4\n作者：牟林湛\n程序功能:\n双人对战、对局回放、经典棋谱鉴赏等\n游戏规则见：\nBasic Rules && Rules of Move Chess", "关于", MB_OK);
			 
	
	// Shortcup_Keys 菜单
	menuListShortcutKeys[6] = game_record ? "End Record | Ctrl-C" : "Begin Record | Ctrl-C";
	menuListShortcutKeys[7] = playback_or_exit ? "End Playback | Ctrl-B" : "Begin Playback | Ctrl-B";
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListShortcutKeys, sizeof(menuListShortcutKeys) / sizeof(menuListShortcutKeys[0]));
	if (selection > 0) selectedLabel = menuListShortcutKeys[selection];
	if (selection == 1)
		start_game_end = 1;
	if (selection == 2)
		start_game_end = 0;
	if (selection == 3)
		pause_or_continue = !pause_or_continue;
	if (selection == 4)
		start_game_end = 1;
	if (selection == 5)
		exit(-1); // choose to exit
	if (selection == 6)
		game_record = !game_record;
	if (selection == 7)
		playback_or_exit = !playback_or_exit;
}

// 菜单结果
void drawMenuResult(){
	SetPointSize(50);
	SetPenColor("Orange");
	drawLabel(0.3, winheight / 1.3, "Chinese Chess Game");
	SetPointSize(22);
	
	// 显示菜单运行结果
	x = winwidth/8;
	y = winheight/8*5.5;
	
	SetPenColor("Black");
	drawLabel(x, y -= h, "Game Progress Status:");
	SetPenColor("Red");
	char status[20];
	if (start_game_end == 0) {
		strcpy(status, "Wait for Start");
	}
	else {
		if (pause_or_continue)
			strcpy(status, "Game on Pause");
		else
			strcpy(status, "Game in Progress");
	}
	drawLabel(x + xindent, y -= h, status);
	
	SetPenColor("Black");
	drawLabel(x, y-=h, "Playback Process Status:");
	SetPenColor("Red");
	drawLabel(x + xindent, y -= h, playback_or_exit ? "Game Being Playbacked" : "Wait for PlayBack");
	
	SetPenColor("Black");
	drawLabel(x,    y-=h, "Control Variable Status");
	SetPenColor("Red");
	drawLabel(x+xindent, y-=h, show_more_buttons ? "More Buttons" : "Less Button");

	SetPenColor("Black");
	drawLabel(x, y -= h, "Most recently selected menu is:");
	SetPenColor("Red");
	drawLabel(x + xindent, y -= h, selectedLabel);
}

// 按钮程序
void drawButtons()
{
	setButtonColors("Dark Gray", "Gray", "Light Gray", "White", 1);
		
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = winwidth / 1.7;
	double y = winheight - h;
	double w = winwidth / 5; // 控件宽度
	
		// 游戏开始按钮
	if (button(GenUIID(0), x, y - 3 * h, w, h, start_game_end ? "结束游戏" : "开始游戏" ))
		start_game_end = start_game_end ? 0: 1;
		// 开始棋谱欣赏的按钮
	if (button(GenUIID(0), x, y - 5 * h, w, h, "经典棋谱"))
		manual = 1;
		// 游戏录制按钮
	if (button(GenUIID(0), x, y - 7 * h, w, h, playback_or_exit ? "退出回放" : "对局回放"))
		playback_or_exit = !playback_or_exit;
		// 程序退出按钮
	if (button(GenUIID(0), x, y - 9 * h, w, h, "退出游戏")) {
		int result = MessageBox(NULL, "您确定要退出游戏吗?", "Tips", MB_OKCANCEL);
		if (result == 1)
		{
			exit(0);
		}
	}

	// 显示英文按键
	if (show_more_buttons)
	{
		if (button(GenUIID(0), x * 1.35, y - 3 * h, w, h, start_game_end ? "End the Game" : "Begin the Game"))
			start_game_end = start_game_end ? 0 : 1;
		// 开始棋谱欣赏的按钮
		if (button(GenUIID(0), x * 1.35, y - 5 * h, w, h, "Manual"))
			manual = 1;
		// 游戏录制按钮
		if (button(GenUIID(0), x * 1.35, y - 7 * h, w, h, playback_or_exit ? "End the Playback" : "PlayBack"))
			playback_or_exit = !playback_or_exit;
		// 程序退出按钮
		if (button(GenUIID(0), x * 1.35, y - 9 * h, w, h, "Click to Exit")) {
			int result = MessageBox(NULL, "您确定要退出游戏吗?", "Tips", MB_OKCANCEL);
			if (result == 1)
			{
				exit(0);
			}
		}
	}
}


