#include "MainFunction.h"
/*********************************************
***   此文件中的函数用于刷新重绘游戏界面       ***
**********************************************/

extern int start_game_end;
extern bool isBlink;
extern bool canDisplayClear;
extern double countDownTime;
extern int playback_or_exit;
extern int manual;
extern int game_mode;
static int playBackFlag = 0;
static int mode = 1;

void display()
{
	// 清屏
	if (canDisplayClear)
		DisplayClear();
	if (game_record)
		OutPutRecord();
	if (start_game_end == 0) {
		if (playback_or_exit == 0 && manual == 0) {
			playBackFlag = 0;
			isBlink = FALSE;
			ChessInit();
			drawMenu();
			drawMenuResult();
			drawButtons();
		}
		
		// 进入回放模式
		else if (playback_or_exit == 1) {
			if (playBackFlag == 0)
			{
				PlayBackStackInit();
				ChessInit();
				playBackFlag = 1;
			}
			drawMenu();
			DrawChessBoard();
			DrawChess();
			DrawPlayBackButtons(&playback_or_exit);
		}
		
		// 进入经典棋谱模式
		else if (manual == 1)
		{
			ChessInit();
			drawMenu();
			DrawChessBoard();
			DrawManual(&mode);
			DrawManualButtons(&mode, &manual);
			DrawChess();
		}
	}
	// 开始游戏
	else {
		if (restart_the_game == 1)
		{
			restart_the_game = 0;
			ChessInit();
		}
		isBlink = TRUE;
		drawMenu();
		DrawChessBoard();
		ChessRepent();
		DrawWhichRound();
		DrawIfTimeUp();
		DrawEatenChess();
		DrawChess();
		DrawAttackKing();
		DrawWhetherRound();
		StartChessReminderProcess();
		DrawChessButtons();
		DrawWinner();
	}
}