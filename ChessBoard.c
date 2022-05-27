#include "ChessBoard.h"

#define Corner_x 0.5
#define Corner_y 0.5
#define delta 0.03

// ����ʱ��Ҫת��Ϊ�ַ������ͽ������
const char* chessName[] = { "܇", "�R", "��", "ʿ", "��", "�h", "��",
							"�e", "��", "��", "��", "��", "��", "��" };

/**************************************
***   �˺������ڻ�������              ***
***************************************/
void DrawChessBoard()
{
	double w = GetWindowWidth(), h = GetWindowHeight();
	SetPenSize(2);
	//StartFilledRegion(0.5);
	DrawBox(Corner_x, Corner_y, 8 * GRID_SIZE, RiverWidth + 8 * GRID_SIZE);
	//EndFilledRegion();
	DrawBox(Corner_x - delta, Corner_y - delta, 8 * GRID_SIZE + 2 * delta, RiverWidth + 8 * GRID_SIZE + 2 * delta);
	DrawGrid(Corner_x, Corner_y, GRID_SIZE, GRID_SIZE, 8, 4);
	DrawGrid(Corner_x, Corner_y+RiverWidth+4*GRID_SIZE, GRID_SIZE, GRID_SIZE, 8, 4);
	
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + GRID_SIZE);
	DrawLine(GRID_SIZE, GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + GRID_SIZE);
	DrawLine(-GRID_SIZE, GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + GRID_SIZE);
	DrawLine(GRID_SIZE, -GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + GRID_SIZE);
	DrawLine(-GRID_SIZE, -GRID_SIZE);

	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + 7 * GRID_SIZE + RiverWidth);
	DrawLine(GRID_SIZE, GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + 7 * GRID_SIZE + RiverWidth);
	DrawLine(-GRID_SIZE, GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + 7 * GRID_SIZE + RiverWidth);
	DrawLine(GRID_SIZE, -GRID_SIZE);
	MovePen(Corner_x + 4 * GRID_SIZE, Corner_y + 7 * GRID_SIZE + RiverWidth);
	DrawLine(-GRID_SIZE, -GRID_SIZE);
	
	SetPenColor("Black");
	SetFont("΢���ź�");
	SetPointSize(30);
	char str1[10] = "����";
	char str2[10] = "����";
	drawLabel(Corner_x + 2 * GRID_SIZE - TextStringWidth(str1) / 2, Corner_y + 4 * GRID_SIZE + RiverWidth / 2 - 2 * delta, str1);
	drawLabel(Corner_x + 6 * GRID_SIZE - TextStringWidth(str2) / 2, Corner_y + 4 * GRID_SIZE + RiverWidth / 2 - 2 * delta, str2);
	SetPenSize(1);

}

/**************************************
***   �˺������ڻ�������              ***
***************************************/
void DrawChess()
{
	SetPenSize(1);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j].id == SPACE) //�����ͼ�ϸõ㲻�����ӣ�����������
				continue;
			if (map[i][j].type == RED) { // ����
				SetPenColor("Red");
				StartFilledRegion(0.);
				DrawCenteredCircle(map[i][j].x, map[i][j].y, ChessCircle);
				EndFilledRegion();
				SetFont("����");
				SetPointSize(20);
				DrawCenteredCircle(map[i][j].x, map[i][j].y, ChessCircle - delta);
				MovePen(map[i][j].x - TextStringWidth(chessName [map[i][j].id]) / 2, map[i][j].y - GetFontAscent() / 2);
				DrawTextString(chessName[map[i][j].id]);
			}
			else { // ����
				SetPenColor("Black");
				StartFilledRegion(0.);
				DrawCenteredCircle(map[i][j].x, map[i][j].y, ChessCircle);
				EndFilledRegion();
				DrawCenteredCircle(map[i][j].x, map[i][j].y, ChessCircle - delta);
				DrawCenteredCircle(map[i][j].x, map[i][j].y, ChessCircle - delta);
				MovePen(map[i][j].x - TextStringWidth(chessName[map[i][j].id]) / 2, map[i][j].y - GetFontAscent() / 2);
				DrawTextString(chessName[map[i][j].id]);				
			}
		}
	}
	SetFont("Times");	
}


