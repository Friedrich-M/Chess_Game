#include "ChessBoard.h"
#pragma warning(disable:6031)
/*********************************************
***   该文件包含了实现对局记录和对局回放的函数  ***
**********************************************/


StackObj PlayBackStack[MAXSTEP][2] = { -1 };
int playBackTop = 0;
extern StackObj chessStack[MAXSTEP][2];
extern step top;
int recordTop;
extern const char* chessName[];

void OutPutRecord()
{
	if (game_record == 1)
	{
		FILE* fp;
		FILE* fp1;
		if ((fp = fopen("Record.txt", "w+")) == NULL) /* 打开文件 */ 
		{	
			printf("File open error!\n"); 
			exit(0); 
		}

		if ((fp1 = fopen("PlayBack.txt", "w+")) == NULL) /* 回放记录文件 */
		{
			printf("File open error!\n");
			exit(0);
		}

		if (restart_the_game == 1)
		{
			fprintf(fp, "Game restart!\n");
			fclose(fp);
			return ;
		}
		recordTop = top;
		// 将chessStack中的内容按行输出到fp中
		for (int i = 0; i < top; i++)
		{
			if(chessStack[i][1].id == SPACE && chessStack[i][0].type == RED)
				fprintf(fp, "red %s moves from (%d,%d) to (%d,%d)\n", chessName[chessStack[i][0].id], 
					chessStack[i][0].y+1, chessStack[i][0].x+1, chessStack[i][1].y+1, chessStack[i][1].x+1);
			else if (chessStack[i][1].id == SPACE && chessStack[i][0].type == BLACK)
			{
				fprintf(fp, "black %s moves from (%d,%d) to (%d,%d)\n", chessName[chessStack[i][0].id],
					chessStack[i][0].y+1, chessStack[i][0].x+1, chessStack[i][1].y+1, chessStack[i][1].x+1);
			}
			else if (chessStack[i][0].id != SPACE && chessStack[i][0].type == RED)
			{
				fprintf(fp, "red %s eats black %s which moves from (%d,%d) to (%d,%d)\n", chessName[chessStack[i][0].id], chessName[chessStack[i][1].id],
					chessStack[i][0].y + 1, chessStack[i][0].x + 1, chessStack[i][1].y + 1, chessStack[i][1].x + 1);
			}
			else if (chessStack[i][0].id != SPACE && chessStack[i][0].type == BLACK)
			{
				fprintf(fp, "black %s eats red %s which moves from (%d,%d) to (%d,%d)\n", chessName[chessStack[i][0].id], chessName[chessStack[i][1].id],
					chessStack[i][0].y + 1, chessStack[i][0].x + 1, chessStack[i][1].y + 1, chessStack[i][1].x + 1);
			}
			fprintf(fp1, "%d %d %d %d\n", chessStack[i][0].x, chessStack[i][0].y, chessStack[i][1].x, chessStack[i][1].y);
		}
		// 关闭文件
		fclose(fp);
		fclose(fp1);
	}
}


void PlayBackStackInit()
{
	// 从PlayBack.txt中逐行读取数据
	FILE* fp = fopen("PlayBack.txt", "r");
	if (fp == NULL)
	{
		printf("PlayBack.txt not found!\n");
		exit(0);
	}

	while (!feof(fp))
	{
		int x0, y0, x1, y1;
		fscanf(fp, "%d %d %d %d\n", &x0, &y0, &x1, &y1);
		if (playBackTop < recordTop) {
			PlayBackStack[playBackTop][0].x = x0;
			PlayBackStack[playBackTop][0].y = y0;
			PlayBackStack[playBackTop][1].x = x1;
			PlayBackStack[playBackTop][1].y = y1;
			playBackTop++;
		}
		else {
			break;
		}

	}
	fclose(fp);
}

void PlayBackStackPrint(int i)
{
	map[PlayBackStack[i][1].x][PlayBackStack[i][1].y].id = map[PlayBackStack[i][0].x][PlayBackStack[i][0].y].id;
	map[PlayBackStack[i][1].x][PlayBackStack[i][1].y].type = map[PlayBackStack[i][0].x][PlayBackStack[i][0].y].type;

	map[PlayBackStack[i][0].x][PlayBackStack[i][0].y].id = SPACE;
	map[PlayBackStack[i][0].x][PlayBackStack[i][0].y].type = NONE;

}
