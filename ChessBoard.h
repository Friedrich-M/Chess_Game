#ifndef ___chessboard___h____
#define ___chessboard___h____

#include "MainFunction.h"
extern int	start_game_end;
extern int  game_record;
extern int  pause_or_continue;
extern int  restart_the_game;

#define ROW  10
#define COL  9 
#define BLACK 0
#define RED 1
#define NONE -1

#define blackRound 0
#define redRound 1

#define ChessCircle 0.2
#define delta_Circle 0.03

#ifndef TIMER_BLINK500
#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#endif // !1

#ifndef TIMER_BLINK1000
#define TIMER_BLINK1000 2     /*1000ms定时器时间标志号*/
#endif

#define GRID_SIZE 0.6
#define RiverWidth 0.6
#define INTERVAL 0.5

#ifndef mseconds500
#define mseconds500 500
#endif

#ifndef mseconds1000 
#define mseconds1000 1000
#endif


#define MAXSTEP 100
typedef int step;

typedef char* string;
typedef enum PIECES ChessType;

enum PIECES //枚举棋子
{
	SPACE = -1,
	車, 馬, 象, 士, 将, 砲, 卒, //红方
	俥, 马, 相, 仕, 帥, 炮, 兵, //黑方
	BEGIN, END
};


// 每一个棋子的属性
typedef struct chess
{
	ChessType id; // 棋子名称
	unsigned int type; // 棋子的类别,红色或者黑色
	double x; // 行坐标
	double y; // 列坐标
	bool overRiver; // 是否过河
} Chess, * pChess;

// 定义一个链表记录每一次胜利的棋子方信息
typedef struct winChess
{
	char nowTime[50]; // 记录对局结束时的当地时间
	char Win[5]; // 记录胜利方
	struct winChess* next;
} winC, *pWinC;

// 定义一个链表存储回放的棋子
typedef struct PlayBackNode
{
	int x0; // 起点的x坐标
	int y0; // 起点的y坐标
	int x1; // 终点的x坐标
	int y1; // 终点的y坐标
	struct PlayBackNode* next;
} PlayBackNode, * pNode;


// 每一个状态的属性
typedef struct mystate
{
	int begr;
	int begc;
	int endr;
	int endc;
	int state;
} State, * pState;


// 每一步棋的属性
typedef struct myStackObj
{
	int x; // 棋子在地图中的横坐标
	int y; // 棋子在地图中的纵坐标
	ChessType id; // 棋子名称
	unsigned int type; // 棋子的类别,红色或者黑色
	bool overRiver; // 是否过河
} StackObj;


// 每一次发生吃棋的状态属性
typedef struct EatChessObj
{
	int chessType;
	int chessId;
} ChessEaten;

// 游戏地图
Chess map[ROW][COL]; //初始化一个结构体数组表示地图， 用来保存每一个棋子的信息

// 触发函数
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

// 绘制函数
void DrawChessBoard();
void DrawChess();
void DrawChessButtons();
void DrawCountDown(double x, double y);
void DrawWhichRound();
void DrawEatenChess();
void DrawChessInMenu(char* chess_type, char* chess_id);
void DrawChessInMenu2(char* chess_type, char* chess_id);
void DrawWinner();
void DrawWhetherRound();
void DrawAttackKing();
void DrawManual(int* mode);
void DrawPlayBackButtons(int* playback_or_exit);
void DrawManualButtons(int* mode, int* manual);

// 初始化函数
void ChessInit();
void InitTime();
void PlayBackStackInit();

// 游戏功能函数
void chessMove();
void StartChessReminderProcess();
void ClearCountDown(double x, double y);
void chosePenColor(char* chess_type);
void judgeWinner();
void OutPutRecord();
void PlayBackStackPrint(int i);

// 判断函数
bool checkAttackKing();
bool HasBlock(int row1, int col1, int row2, int col2);
bool HasOneBlock(int row1, int col1, int row2, int col2);

#endif