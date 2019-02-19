#include "DLLmain.h"

ExImage::ExImage(int X, int Y, int Transp, unsigned int Frame, string szFile) : ExControl(X, Y, -1, -1, 0)
{
	try
	{
		aCellFile = new ExCellFile(szFile);
	}
	catch (const CellLoadError&)
	{
		delete aCellFile;
		D2ERROR("Cannot create image because of missing or corrupted DC6 file!")
	}

	Hoover = L"";
	aCellFile->SetFrame(Frame);
	cWidth = aCellFile->GetCF()->cells[Frame]->width;
	cHeight = aCellFile->GetCF()->cells[Frame]->height;
	TransLvl = (Transp > 7) ? 5 : Transp;
	ColorShift = 0;
	MultiFrame = false;
}


void ExImage::SetTransLvl(int aLevel)
{
	TransLvl = aLevel;
}

void ExImage::Relocate() //- Set control align
{
	if (ptParent) {
		if (wAlign == CENTER) cX = ((ptParent->GetX() + ptParent->GetWidth() + ptParent->GetX()) - cWidth) / 2;
		else if (wAlign == RIGHT) cX = (ptParent->GetX() + ptParent->GetWidth() - cWidth);
		if (hAlign == CENTER) cY = ((ptParent->GetY() + ptParent->GetHeight() + ptParent->GetY()) + cHeight) / 2;
		else if (hAlign == RIGHT) cY = ptParent->GetY() + ptParent->GetHeight();
	}
	else {
		if (wAlign == CENTER) cX = (*D2CLIENT_ScreenWidth - cWidth) / 2;
		else if (wAlign == RIGHT) cX = (*D2CLIENT_ScreenWidth - cWidth);
		if (hAlign == CENTER) cY = (*D2CLIENT_ScreenHeight + cHeight) / 2;
		else if (hAlign == RIGHT) cY = *D2CLIENT_ScreenHeight;
	}
}

void ExImage::Draw()
{
	if (cState == INVISIBLE) return;
	if (MultiFrame)
	{
	}
	else
		D2GFX_DrawCellContextEx(aCellFile->Get(), cX, cY, -1, TransLvl, ColorShift);

	if (Hoover.empty() || !bBeingSelected) return;
	D2WIN_DrawFramedText(Hoover.c_str(), cX, cY - cHeight - 10, 0, 0);
}

ExImage::~ExImage(void)
{
	delete aCellFile;
}


bool ExImage::isPressed(unsigned int Sender, WPARAM wParam)
{
	switch (Sender)
	{
	case WM_LBUTTONDOWN:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= cY - cHeight)
		{
			bBeingPressed = true;
			return true;
		}
		break;
	case WM_LBUTTONUP:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY && *D2CLIENT_MouseY >= cY - cHeight)
		{
			if (cState == VISIBLE && event_onClick) event_onClick(this);
			bBeingPressed = false;
			return true;
		}
		break;
	case WM_MOUSEMOVE:
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY >= cY - cHeight && *D2CLIENT_MouseY <= cY)
			bBeingSelected = true;
		else
			bBeingSelected = false;
		if (!(Sender == WM_MOUSEMOVE && wParam & (MK_LBUTTON))) break;
		if (*D2CLIENT_MouseX >= cX && *D2CLIENT_MouseX <= cX + cWidth && *D2CLIENT_MouseY <= cY - cHeight && *D2CLIENT_MouseY >= cY)
			bBeingPressed = true;
		else
			bBeingPressed = false;
		break;
	}
	return false;
}