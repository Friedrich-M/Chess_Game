#include "DrawFunction.h"
/*********************************************
***   该文件包含了所有可能用到的画图函数       ***
**********************************************/

// 画矩形
void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

// 画三角形
void DrawTriangle(double x, double y, double base, double height)
{
    MovePen(x, y);
    DrawLine(base, 0);
    DrawLine(-base / 2, height);
    DrawLine(-base / 2, -height);
}

// 以（x,y）为圆心，r为半径画圆
void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360);
}

// 画格子
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