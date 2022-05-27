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
#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
#endif // !1

#ifndef TIMER_BLINK1000
#define TIMER_BLINK1000 2     /*1000ms��ʱ��ʱ���־��*/
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

enum PIECES //ö������
{
	SPACE = -1,
	܇, �R, ��, ʿ, ��, �h, ��, //�췽
	�e, ��, ��, ��, ��, ��, ��, //�ڷ�
	BEGIN, END
};


// ÿһ�����ӵ�����
typedef struct chess
{
	ChessType id; // ��������
	unsigned int type; // ���ӵ����,��ɫ���ߺ�ɫ
	double x; // ������
	double y; // ������
	bool overRiver; // �Ƿ����
} Chess, * pChess;

// ����һ�������¼ÿһ��ʤ�������ӷ���Ϣ
typedef struct winChess
{
	char nowTime[50]; // ��¼�Ծֽ���ʱ�ĵ���ʱ��
	char Win[5]; // ��¼ʤ����
	struct winChess* next;
} winC, *pWinC;

// ����һ������洢�طŵ�����
typedef struct PlayBackNode
{
	int x0; // ����x����
	int y0; // ����y����
	int x1; // �յ��x����
	int y1; // �յ��y����
	struct PlayBackNode* next;
} PlayBackNode, * pNode;


// ÿһ��״̬������
typedef struct mystate
{
	int begr;
	int begc;
	int endr;
	int endc;
	int state;
} State, * pState;


// ÿһ���������
typedef struct myStackObj
{
	int x; // �����ڵ�ͼ�еĺ�����
	int y; // �����ڵ�ͼ�е�������
	ChessType id; // ��������
	unsigned int type; // ���ӵ����,��ɫ���ߺ�ɫ
	bool overRiver; // �Ƿ����
} StackObj;


// ÿһ�η��������״̬����
typedef struct EatChessObj
{
	int chessType;
	int chessId;
} ChessEaten;

// ��Ϸ��ͼ
Chess map[ROW][COL]; //��ʼ��һ���ṹ�������ʾ��ͼ�� ��������ÿһ�����ӵ���Ϣ

// ��������
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

// ���ƺ���
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

// ��ʼ������
void ChessInit();
void InitTime();
void PlayBackStackInit();

// ��Ϸ���ܺ���
void chessMove();
void StartChessReminderProcess();
void ClearCountDown(double x, double y);
void chosePenColor(char* chess_type);
void judgeWinner();
void OutPutRecord();
void PlayBackStackPrint(int i);

// �жϺ���
bool checkAttackKing();
bool HasBlock(int row1, int col1, int row2, int col2);
bool HasOneBlock(int row1, int col1, int row2, int col2);

#endif