#include "DrawFunction.h"
/*********************************************
***   ���ļ����������п����õ��Ļ�ͼ����       ***
**********************************************/

// ������
void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

// ��������
void DrawTriangle(double x, double y, double base, double height)
{
    MovePen(x, y);
    DrawLine(base, 0);
    DrawLine(-base / 2, height);
    DrawLine(-base / 2, -height);
}

// �ԣ�x,y��ΪԲ�ģ�rΪ�뾶��Բ
void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360);
}

// ������
void DrawGrid(double x, double y, double width, double height,
    int columns, int rows)
{
    int i, j;

    for (i = 0; i < columns; i++) {
        for (j = 0; j < rows; j++) {
            DrawBox(x + i * width, y + j * height,
                width, height);
        }
    }
}