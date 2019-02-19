#include "DLLmain.h"

ExRectangle::ExRectangle(int X, int Y, int Width, int Height, int Color, int TransLvl) : ExControl(X, Y, Width, Height, 0)
{
	aColor = Color;
	aTransLvl = TransLvl;
}

void ExRectangle::Draw()
{
	if (cState != INVISIBLE) D2GFX_DrawRectangle(cX, cY, cX + cWidth, cY + cHeight, aColor, aTransLvl);
}

ExRectangle::~ExRectangle(){}
