#ifndef _drawfunction_h
#define _drawfunction_h

#include "MainFunction.h"

void DrawBox(double x, double y, double width, double height);
void DrawTriangle(double x, double y, double base, double height);
void DrawCenteredCircle(double x, double y, double r);
void DrawGrid(double x, double y, double width, double height, int columns, int rows);
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);


#endif