#include "DLLmain.h"

ExBox::ExBox(int X, int Y, int Width, int Height, int Color, int TransLvl) : ExControl(X, Y, Width, Height, 0)
{
	aColor = Color;
	aTransLvl = TransLvl;
}

void ExBox::Draw()
{
	if(cState!=INVISIBLE) 
	{
		D2GFX_DrawRectangle(cX,cY,cX+cWidth,cY+cHeight,aColor,aTransLvl);
		D2CLIENT_DrawGZBox(cX,cY,cX+cWidth,cY+cHeight);
	}
}

ExBox::~ExBox(){}
